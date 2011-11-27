#include <stdio.h>

/*int atod (char* number);

int main (int argc, char** argv){
	
	printf(argv[1]);
	
	return 0;
}*/


int atod (char* number){
	
	int ans;
	int i, digit;
	char c;
	
	ans=0;
	i=0;
	while(number[i]!=0){
		ans = ans*10;
		c = number[i];
		digit = c-'0';
		ans = ans + digit;
		i++;
	}
		
	
	return ans;
	
}