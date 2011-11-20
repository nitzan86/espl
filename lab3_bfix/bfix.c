#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "diff.h"

int main(int argc, char** argv){

	int h_flag = 0;
	int r_flag = 0;
	int m_flag = 0;
	int a;
	FILE *to_fix, *diff;
	char line_fix[500];
	char line_diff[500];
	int found;
	char c1;

	/* opening the files */
	to_fix = fopen(argv[1], "r+");
	if (to_fix == NULL){
		printf("cannot read file %s", argv[1]);
		exit(1);
	}

	  diff = fopen(argv[2], "r");
	  if (diff == NULL){
		printf("cannot read file %s", argv[2]);
		exit(1);      
	  }


	while ((a = getopt (argc, argv, "hrm")) != -1){

		switch(a){
			case 'h':
				h_flag = 1;
				break; 
			case 'r':
				r_flag = 1;
				break;
			case 'm':
				m_flag = 1;
				break;  
			default:
				abort();
		}
	}


	if (h_flag == 1){
		printf("Details of the options for bfix:\nh - help option: prints the options of the program\nr - reverse the differences\nm - print a message each time a change is applied\n");
		exit(1);
	}

	
	while(fgets(line_diff, sizeof(line_diff), diff) != NULL){   //reads the difference file
	    
		struct diff diff;
		parsediff(line_diff, &diff);

		fseek(to_fix, diff.offset-1, SEEK_SET); //moves the pointer to the correct place
		fread(&c1, 1, 1, to_fix); //puts in c1 the char readed from the file which needs to be fixed
		
		if (r_flag == 0){ //usual case (no -r)
			
			if (c1 == diff.old){
				fseek(to_fix, diff.offset-1, SEEK_SET);
				fwrite(&diff.new, 1, 1, to_fix);
			}
			else{
				printf("error1\n"); 
			}
		
		}
		else{ //-r was typed
			if (c1 == diff.new){
				fseek(to_fix, diff.offset-1, SEEK_SET);
				fwrite(&diff.old, 1, 1, to_fix);
			}
			else{
				printf("error2\n"); 
			}

		}

		if (m_flag == 1){ // in case -m was typed, we should have a detailed messge
			printf("change was made on byte %ld\n", diff.offset);
		}

		
	  }


  
  
  
  
}