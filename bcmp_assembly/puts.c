int length (char *s);

int puts (char *str){
	int len = length(str); 
	return write(1, str, len);
}