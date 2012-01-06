#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 #include <fcntl.h>
#include <sys/stat.h>

#define BUF_LEN 1024
static char command[BUF_LEN+1];
static int argc;
static char *argv[BUF_LEN+1];

/* read command and remove end of line if present */
int read_command() {
  int len;

  if(fgets(command, BUF_LEN, stdin)) {
    len = strlen(command);
    if(len>0 && command[len-1]=='\n')
      command[len-1] = '\0';
    return 1;
  } 
  
  return 0;
}

#define NO_SEP '\0'
#define EOC '\1'

/* split the command line into arguments and fill argv with pointers
   to the arguments */
void split_command() {
  char *s, sep;
  int between;

  between = 1;
  argc = 0;
  sep = NO_SEP;
  for(s = command; *s; ++s) {
    switch(*s) {
    case '\"': case '\'':
      if(sep==NO_SEP) {
        sep = *s;
      } else if(sep==*s) {
        sep = '\0';
      } 
      break;
    case '\\':
      ++s;
      break;
    case ' ':
      if(!sep) {
        between = 1;
        *s = '\0';
        continue;
      }
      break;
    }
    if(between) {
      argv[argc++] = s;
      between = 0;
    }
  }
  argv[argc] = NULL;
}

/* expand arguments, substitute shell variable values etc. */
void expand_args() {
  char **a = argv;
  while(*a) {
    if(**a=='"' || **a=='\'') { /* TODO: quotes can be in any place */
      *a = strdup(*a);
      memmove(*a, *a+1, strlen(*a));
      (*a)[strlen(*a)-1] = 0;
    } else {
      *a = strdup(*a);
    }
    /* TODO: eliminate escapes \ */
    /* TODO: expand environment variables */
    ++a;
  }
}

/* free arguments allocated during expansion */
void free_args() {
  char **a = argv;
  while(*a) {
    free(*a);
    ++a;
  }
}

/* run an external program */
void run_program() { 
  int pid, status ,second_pid = -1;
  static char ststr[8];
  char *sign;

  int big = -1, fd;
  int pipe_flag = 0, i;

  int p[2]; //possible pipe
		
  
  /* TODO: input, output redirection */
  /* TODO: pipelines */
  /* TODO: background commands */

  
  sign = argv[argc-2];
  if (strcmp(sign, ">")==0){
	big = 1;  
  }
  else if(strcmp(sign, "<")==0) {
	big = 0;
  }
  if(big!=-1) { //"cuts" argv
    argv[argc-2] = 0;
  }
  
  
  for(i=0; i<argc; i++){
	if(strcmp(argv[i], "|")==0){	  
	  pipe_flag = 1;
	  break;
	}
  }
  
	if(pipe_flag==1){ 	// create pipe

		//open pipe
		if(pipe(p) == -1)
		{    perror("pipe call error");
			exit(1);
		}
	}
  
  pid = fork();

	//parent
	if(pid>0) {
		if(pipe_flag==1){
			second_pid = fork();
		}			
		if(second_pid==0){ // (possibly) second child - will read from the pipe
			dup2(p[0], 0);
			close(p[1]); //close the writing end
			execvp(argv[i+1], argv+i+1);
			perror(argv[i+1]);
		}
		else if(second_pid>0){ //the sign for pipe was typed | wait for the second child to finish
			close(p[0]);
			close(p[1]);
			waitpid(pid, &status, 0);
			waitpid(second_pid, &status, 0);
			sprintf(ststr, "%d", status);
			setenv("?", ststr, 1);
		}
		else{ //no | was typed, so we need to wait for the first son
			waitpid(pid, &status, 0);
			sprintf(ststr, "%d", status);
			setenv("?", ststr, 1);		
		}
	}
  
  //echo I hate espl | sed s/hate/love/    ----> left process' output is right process input
  
  
  
  //child 1
	else if(pid==0) {

	//we need to write to a file
		if(big==1){
			fd = open(argv[argc-1], O_WRONLY|O_TRUNC|O_CREAT, 0644);
			dup2(fd, 1); //output - writing to a file
		}
		else if(big ==0){
			fd = open(argv[argc-1], O_RDONLY);
			dup2(fd, 0); //input
		}
		if(pipe_flag==1){
			argv[i]=0;
			close(p[0]); //close the reading end
			dup2(p[1], 1); //this child will write to the pipe
		}
			
		execvp(argv[0], argv);
		perror(argv[0]);
  } 
  
  
  
  
  
  
  else {
    perror(getenv("SHELL")); /* problem while forking, not due to a particular program */
  }
  
	if(pipe_flag==1){ 	// close pipe
		close(p[0]);
		close(p[1]);
	}
}

int main(int _argc, char **_argv) {
  /* clear shell variables and  re-assign a minimum set */
  clearenv();
  setenv("PATH", ":/bin:/usr/bin", 1);
  setenv("PROMPT", "$ ", 1);
  setenv("SHELL", _argv[0], 1);

  signal(SIGINT, SIG_IGN); /* ignore ^C */

  while(1) {
    printf("%s", getenv("PROMPT"));
    if(!read_command())
      break;
    split_command(); //fills argv with arguments of command line
    if(!argc)
      continue;
    expand_args();
    /* process builtin commands */
    if(!strcmp(argv[0],"exit")) { //do the command we got
      break;
    } else if(!strcmp(argv[0],"set")) {
      if(argc!=3) {
        fprintf(stderr, "set: two arguments required\n");
        continue;
      }
      setenv(argv[1], argv[2], 1);
    } else if(!strcmp(argv[0], "cd")) { //change directory
      if(argc!=2) {
        fprintf(stderr, "cd: one argument required\n");
        continue;
      }
      if(chdir(argv[1])==-1) {
        perror("cd");
      }
    } else if(!strcmp(argv[0], "pwd")) {
      if(argc!=1) {
        fprintf(stderr, "pwd: no arguments allowed\n");
        continue;
      }
      printf("%s\n", getcwd(command, BUF_LEN));
    } else {
      /* run external command */
      run_program();
    }
    free_args();
  }
  printf("\n");

  return 0;
}
    

    
