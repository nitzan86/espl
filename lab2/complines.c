#include <stdio.h>

int main (int argc, char** argv){

	FILE *f1, *f2;
	char line1[150];
	char line2[150];
	int compare;
	int counter;
	
	/* Makes sure we have opened the files correctly, otherwise - there's no point continue running the program, thus the 'exit' command */
	f1 = fopen(argv[1], "r");
	if (f1 == NULL){
		printf("cannot read file %s", argv[1]);
		exit();
	}

	f2 = fopen(argv[2], "r");
	if (f2 == NULL){
		printf("cannot read file %s", argv[2]);
		exit();
	}
	
	counter = 1;
	/* We can assume that the files have the same amount of lines, so it's possible to use only f1 as the condition checker */
	while(fgets(line1, sizeof(line1), f1) != NULL){
		fgets(line2, sizeof(line2), f2);
		compare = strcmp(line1, line2);
		if(compare!=0){
			if(line1[strlen(line1)-1]=='\n'){
				printf("-%d: %s", counter, line1);
			}
			else{ /* We use this part if this line is the last one in the file, and there's no new line under this one */
				printf("-%d: %s\n", counter, line1);
			}
			
			/* Smae for the 2nd file... */
			if(line2[strlen(line2)-1]=='\n'){
				printf("-%d: %s", counter, line1);
			}
			else{ /* We use this part if this line is the last one in the file, and there's no new line under this one */
				printf("-%d: %s\n", counter, line2);
			}
			
			printf("\n");
		}
		counter++;
	}
	
	fclose(f1);
	fclose(f2);
	
	return 0;
}
