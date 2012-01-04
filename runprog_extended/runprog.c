#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char** argv){

	pid_t child_pid;
	int child_status;
	int i, j, c;
	pid_t wait_pid;
	char in_msg [1000];
	int n_flag = 0, read_bytes, new_line;
	
	// create pipe
	int p[2];
	
	//open pipe
	if(pipe(p) == -1)
	{    perror("pipe call error");
        exit(1);
	}
	
	//now parent and child have the same pipe

	//find out if -n was typed
	if (strcmp(argv[1], "-n") == 0) {
		n_flag = 1;
	}
	
	child_pid = fork();
	
	if (child_pid == 0){ /* this is run by the child, because if we're in the child process than child_pid=0 */
		
		close(p[0]); //close the read end of the pipe, so we won't try to read and write together
		
		//print the command line to the screen
		if (n_flag) {
			i = 2;
		}
		else {
			i = 1;
		}
		for(; i<argc; i++){
			printf("%s ", argv[i]);
		}
		printf("\n");

		/*set global output to p[1] (instead of standard out) - write such that the parent will 
		receieve the output and not the screen (redirect output to parent using the pipe)*/
		
		close(1); // close the standard output
		dup2(p[1], 1); // duplicate the write pipe to the standard out
		
		//executes the program it received 
		if (n_flag) {
			execvp(argv[2], argv+2);
		}
		else {
			execvp(argv[1], argv+1);
		}
		
		/* making sure execvp didn't return */
		printf("error occured");
		child_status = 255;
		exit(255);
	}
	else { /* this is run by the parent - the parent is waiting for the child to die */
		
		close(p[1]); //close the write end of the pipe, so we won't try to read and write together
		
		//read pipe - read the output written by the child
		j = 1;
		new_line = 1;
		read_bytes = read(p[0], in_msg, 1000);
		while (read_bytes > 0) {
			for (i = 0; i < read_bytes; i++) {
				if ((n_flag==1) && (new_line==1)){
					printf("%d: ", j);
					j++;
					new_line = 0;
				}
				printf("%c", in_msg[i]);
				if (in_msg[i] == '\n')
					new_line = 1;
			}
			read_bytes = read(p[0], in_msg, 1000);
		}

		//wait for the child to die
		wait_pid = wait(&child_status);

		//prints the exit status
     	printf("exit status: %d\n", WEXITSTATUS(child_status));
		
		return child_status;
			
	}
	
}