#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "font.h"

void prsym(int idx) {
	int iline;
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline){
	      printf("%s\n", (*symbol)[iline]);

	}
	  
	    
}


int main(int argc, char **argv) {
	int index, i, j, length, iline;
	  //each argument in argv is one word

	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline){
		for (i=1; i<argc; i++){
			length = strlen(argv[i]);
			for (j=0; j<length; j++){
				if(argv[i][j]>=128 && argv[i][j]<=154){
					index = argv[i][j] - 18;
				}
				else{
					index = argv[i][j] - 32;
				}
				char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[index]; //index - the index of a certain character in the vertical array
				printf("%s", (*symbol)[iline]); //prints the suitable line (part of the character)
			}
			char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[0]; //space
			printf("%s", (*symbol)[iline]);
		}
		printf("\n");
	}
	
	  
	//  index = argv[1][1] - 32;
	 // prsym(index);
	  //char *word = argv[1]; //the word which was given as the first argument
	  //accessing the 2nd letter of the first word: word[1]

	return 0;
}
