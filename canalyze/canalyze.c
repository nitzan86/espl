#include <stdio.h>
#include <unistd.h>
#include "namelist.h"
#define RES_WORDS_NUM 31

char *reserved_words[RES_WORDS_NUM] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
"extern", "for", "float", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "switch", "typedef", "union",
"unsigned", "void", "volatile", "while"};

void readfile(namelist namesSet, FILE *f);

int namestat_cmp(const void *a, const void *b);

int isresword(char *word);

int main(int argc, char** argv){

	FILE *f;
    int j;

	namelist namesSet;
 
	namesSet = make_namelist();
 
    for (j=1; j<argc; j++){
		f = fopen(argv[j], "r");
		if (f == NULL){
			printf("cannot read file %s", argv[j]);
			exit(1);
		}
		else{
			readfile(namesSet, f);
		}
		fclose(f);
    }
	
	
	qsort(namesSet->names, namesSet->size, sizeof(struct namestat), namestat_cmp);
	
	for(j=0; j<(namesSet->size); j++){
		printf("%s %d \n", namesSet->names[j].name, namesSet->names[j].count);
	}

	return 0;
 }
 
 
 
/* reads each of the files */
void readfile(namelist namesSet, FILE *f){  
    
    int counter, location, i, inword, should_check = 1;
    char word[NAMELEN];
      
    
    counter = 0; //location on the word array
      
    while ((i = fgetc(f))!= EOF){
		//to ignore prints
		if(i=='\"'){
			if(should_check == 1)
				should_check = 0;	//first time " was read
			else
				should_check = 1; //second time " was read
		}
		//checking for words (except from prints)
		if(should_check){
			inword = isalpha(i);
			if(inword){
				word[counter] = (char)i;
				counter++;
			}
		  
			else{
				word[counter]=0; //signs the end of the string
				if(counter!=0 && !isresword(word)){ //that means it's a word, and not a reserved one
					add_name(namesSet, word);
				}
				counter = 0;
			}
		}
	  
    }
}	

/* comprasion function for the qsort */	
int namestat_cmp(const void *a, const void *b){ 
	const struct namestat *ia = (const struct namestat *)a;
    const struct namestat *ib = (const struct namestat *)b;
    return strcmp((*ia).name, (*ib).name);
} 
	
	
/* checks if the given word is one of the C reserved words */ 	
int isresword(char *word){

	int k;
	for(k=0; k<RES_WORDS_NUM; k++){
		if(strcmp(reserved_words[k], word)==0)
			return 1;
	}
	return 0; //false - 'word' isn't a reserved word
} 


