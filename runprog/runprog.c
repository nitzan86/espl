#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char** argv){

	pid_t child_pid;
	int child_status;
	int i;
	pid_t wait_pid;
	
	child_pid = fork();
	
	if (child_pid == 0){ /* this is run by the child, because if we're in the child process than child_pid=0 */
		
		for(i=1; i<argc; i++){
			printf("%s ", argv[i]);
		}
		
		printf("\n");
		
		execvp(argv[1], argv+1);
		
		/* making sure execvp didn't return */
		printf("error occured");
		child_status = 255;
		exit(255);
	}
	
	else { /* this is run by the parent - the parent is waiting for the child to die */
		
		wait_pid = wait(&child_status);

     		printf("exit status: %d\n", WEXITSTATUS(child_status));
		return child_status;
			
	}
	
}