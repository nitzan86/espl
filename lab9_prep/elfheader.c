#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define EI_INDENT 16

//defining weird types:
typedef unsigned short ELF32_Half;
typedef unsigned int ELF32_Addr;
typedef unsigned int ELF32_Off;
typedef unsigned int ELF32_Word;


typedef struct{
	unsigned char	e_ident[EI_INDENT];
	ELF32_Half		e_type;
	ELF32_Half		e_machine;
	ELF32_Word		e_version;
	ELF32_Addr		e_entry;
	ELF32_Off		e_phoff;
	ELF32_Off		e_shoff;
	ELF32_Word		e_flags;
	ELF32_Half		e_ehsize;
	ELF32_Half		e_phentsize;
	ELF32_Half		e_phnum;
	ELF32_Half		e_shentsize;
	ELF32_Half		e_shnum;
	ELF32_Half		e_shstrndx;
} ELF32_Ehdr;

char types[][30] = {"NONE (No file type)", "REL (Relocatable file)", "EXEC (Executable file)", "SHARED (Shared object file)", "CORE (Core file)"};
char machine[][15] = {"No Machine", "AT&T WE 32100", "SPARC", "Intel 80386", "Motorolla 68000", "Motorola 88000", "Intel 80860", "MIPS RS3000"};

int main (int argc, char** argv){
	ELF32_Ehdr elf;
	int fd, i;
	
	//open the given elf file
	fd = open(argv[1], O_RDONLY);
	
	read(fd, &elf, sizeof(elf));
	
	//print magic number
	printf("\nMagic: ");
	for(i=0; i<EI_INDENT; i++){
		printf("%x ", elf.e_ident[i]);
	}
	
	//print class
	printf("\nClass: ");
	
	//print data
	printf("\nData: ");
	
	//print version
	printf("\nVersion: ");
	if(elf.e_version){
		printf("%d (Current version)", elf.e_version);
	}
	else
		printf("%d (Invalid version)", elf.e_version);
		
	//print OS/ABI
	printf("\nOS/ABI: ");
	
	//print ABI Version
	printf("\nABI Version: ");
	
	//print type
	printf("\nType: ");
	if(elf.e_type==0xff00 | elf.e_type==0xffff){
		printf("Processor-specific");
	}
	else
		printf("%s", types[elf.e_type]);
	
	//print machine
	printf("\nMachine: %s", machine[elf.e_machine]);
	
	//print version
	printf("\nVersion: ");
	
	//print entry point address
	printf("\nEntry point address: 0x%x", elf.e_entry);
	
	//print start of program headers
	printf("\nStart of program headers: %d (bytes into file)", elf.e_phoff);
	
	//print start of section headers
	printf("\nStart of section headers: %d (bytes into file)", elf.e_shoff);
	
	//print flags
	printf("\nFlags: 0x0"); //??????????
	
	//print size of this header
	printf("\nSize of this header: %d (bytes)", elf.e_ehsize);
	
	//print size of program headers
	printf("\nSize of program headers: %d (bytes)", elf.e_phentsize);
	
	//print number of program headers
	printf("\nNumber of program headers: %d", elf.e_phnum);
	
	//print size of section headers
	printf("\nSize of section headers: %d (bytes)", elf.e_shentsize);
	
	//print number of section headers
	printf("\nNumber of section headers: %d", elf.e_shnum);
	
	//print section header string table index
	printf("\nSection header string table index: %d\n", elf.e_shstrndx);
	
	close(fd);
	
	return 0;
}
	