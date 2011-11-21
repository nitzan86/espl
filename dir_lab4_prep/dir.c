#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
	DIR *directory;
	struct dirent *dir_entry;
	int i = 0;
	int h_flag = 0;
	int l_flag = 0;
	struct stat file_stat;
	char path[1000];
	char base_path[1000];
	int size;
	int a;
	int flag = 0; /* states if a directory's name was typed or not */
	char curr_dir[1000];
	int arg = 1;
 
 
    while ((a = getopt (argc, argv, "hl")) != -1){

		switch(a){
			case 'h':
				h_flag = 1;
				break; 
			case 'l':
				l_flag = 1;
				arg = 2;
				break;  
			default:
				exit(1);
		}
	}
	
	if (h_flag == 1){
		printf("Details of the options for dir:\nh - help option: prints the options of the program\nl - prints the files sizes in bytes\n");
		exit(1);
	}
		
	
	if ((argc < 2 && l_flag == 0) || (argc < 3 && l_flag == 1)){ /* the user didn't enter a directory name */
		flag = 1;
	}
	
	
	/* opens the directory */
	if (flag == 1){
		getcwd(curr_dir, 1000); 
		directory = opendir(curr_dir);
	}
	else {
		printf("opening dir: %s\n", argv[arg]);
		directory = opendir(argv[arg]);
	}
	if (directory == NULL){
		printf("couldn't open directory\n");
		exit(1);
	}
	
	if (flag ==0)
		strcpy(base_path, argv[arg]);
	else
		strcpy(base_path, curr_dir);
	strcat(base_path, "/");
	
	//i=0
	while ((dir_entry = readdir(directory)) != NULL){
		if (l_flag==1){
			strcpy(path, base_path);
			strcat(path, dir_entry->d_name);
			//printf("%s\n", path);
			lstat(path, &file_stat);
			size = file_stat.st_size;
			printf("file size: %d file name: %s\n", size, dir_entry->d_name);
		}
		else
			printf("file name: %s\n", dir_entry->d_name);
	}
	
	closedir(directory);
}