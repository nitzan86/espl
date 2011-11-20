#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv){

	FILE *f1, *f2;
	char line1[1];
	char line2[1];
	int should_run;
	long counter;
	int j, k;
	
	/* Makes sure we have opened the files correctly, otherwise - there's no point continue running the program, thus the 'exit' command */
	f1 = fopen(argv[1], "rb");
	if (f1 == NULL){
		printf("cannot read file %s", argv[1]);
		exit(1);
	}

	f2 = fopen(argv[2], "rb");
	if (f2 == NULL){
		printf("cannot read file %s", argv[2]);
		exit(1);
	}
	
	counter = 1;
	should_run = 1;
	while(should_run){
		/* making sure there are still bytes to read before the program actually reads them */
		j = feof(f1);
		k = feof(f2);
		if (j==0){
			fread(line1, sizeof(char), 1, f1);
		}
		if (k==0){
			fread(line2, sizeof(char), 1, f2);
		}
		/* in case one file ended before the other - the bytes are different */
		if (j==0 && k!=0){
			//printf("byte %d -%d +NULL\n", counter, (line1[0] + 256) % 256);
			should_run = 0;
		}
		else if (j!=0 && k==0){
			//printf("byte %d -NULL +%d\n", counter, (line2[0] + 256) % 256);
			should_run = 0;
		}
		/* finished reading both files - nothing to print */
		else if (j!=0 && k!=0){
			should_run = 0;
		}
		/* eveything's ok - we'll read bytes as usual */
		else{
			if (line1[0]!=line2[0]){
				printf("byte %ld -%d +%d\n", counter, ((line1[0] + 256) % 256), ((line2[0] + 256) % 256));
			// 	should_run = 0;
			}
		}
		counter++;
	}
	
	fclose(f1);
	fclose(f2);
	
	return 0;
}