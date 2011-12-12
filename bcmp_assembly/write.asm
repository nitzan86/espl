section .text
global write
write:
	push	ebp
	mov	ebp, esp
	

	mov	ebx, [ebp+8]  ;ebp+8 is the address of the first parameter of the function 
	;ebx contains the file descriptor
	mov	ecx, [ebp+12] ;ebp+12 is the address of the second parameter of the function
;	ecx - the string to print 
	mov	edx, [ebp+16]
;	edx - the length of the string
	mov	eax, 4 ; command to print

	int	0x80	;call kernel

	pop	ebp
	ret
