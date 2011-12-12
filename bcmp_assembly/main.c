//#include <stdio.h>
//#include <fcntl.h>

int exit(int);

int open(char *, int, int);
int close(int);

int read(int, char *, int);

void int_to_str(int, char *, int);

int main (int argc, char** argv){

	//FILE *f1, *f2;
	int f1, f2;
	char line1[1];
	char line2[1];
	int should_run;
	long counter;
	int j, k;
	char output_str[1000];

	/* Makes sure we have opened the files correctly, otherwise - there's no point continue running the program, thus the 'exit' command */
	//f1 = fopen(argv[1], "rb");
	// O_RDONLY = 00
	f1 = open(argv[1], 00, 0);
	if (f1 < 0){
		puts("cannot read first file\n");
		exit(1);
	}
	//f2 = fopen(argv[2], "rb");
	f2 = open(argv[2], 00, 0);
	if (f2 < 0){
		puts("cannot read second file\n");
		exit(1);
	}
	
	counter = 1;
	should_run = 1;
	while(should_run){
		/* reading a byte from both files */
		j = read(f1, line1, sizeof(char));
		/* j == 0 if we reached end of file f1 */
		k = read(f2, line2, sizeof(char));
		/* k == 0 if we reached end of file f2 */

		/* finished reading both files - nothing to print */
		if (j==0 && k==0){
			should_run = 0;
		}
		/* in case one file ended before the other - the bytes are different */
		else if (j==0 && k!=0){
			//printf("byte %d -NULL +%d\n", counter, (line2[0] + 256) % 256);
			puts("byte ");
			int_to_str(counter, output_str, 1000);
			puts(output_str);
			puts(" -NULL +");
			int_to_str((line2[0] + 256) % 256, output_str, 1000);
			puts(output_str);
			puts("\n");
			should_run = 0;
		}
		else if (j!=0 && k==0){
			//printf("byte %d -%d +NULL\n", counter, (line1[0] + 256) % 256);
			puts("byte ");
			int_to_str(counter, output_str, 1000);
			puts(output_str);
			puts(" -");
			int_to_str((line1[0] + 256) % 256, output_str, 1000);
			puts(output_str);
			puts(" +NULL\n");
			should_run = 0;
		}
		/* eveything's ok - we'll read bytes as usual */
		else{
			if (line1[0]!=line2[0]){
				//printf("byte %d -%d +%d\n", counter, ((line1[0] + 256) % 256), ((line2[0] + 256) % 256));
				puts("byte ");
				int_to_str(counter, output_str, 1000);
				puts(output_str);
				puts(" -");
				int_to_str((line1[0] + 256) % 256, output_str, 1000);
				puts(output_str);
				puts(" +");
				int_to_str((line2[0] + 256) % 256, output_str, 1000);
				puts(output_str);
				puts("\n");
			}
		}
		counter++;


	}
	
	close(f1);
	close(f2);
	
	return 0;
}

/* Converts an int to a string */
void int_to_str(int num, char *str, int str_len){
	int orig = num;
	int digits = 0;
	int divisor = 10;

	if (num==0){
		str[0] = '0';
		str[1] = 0;
		return;
	}

	/* find number of digits */
	while (num>0){
		num = num / 10;
		digits++;
	}


	/* put the digits into the string */
	num = orig;
	if (digits<str_len){
		str[digits] = 0;
		digits--;
		while (digits>=0){
			str[digits] = '0' + ((num%divisor) / (divisor/10));
			digits--;
			divisor = divisor * 10;
		}
	}

}
