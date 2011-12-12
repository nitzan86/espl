section .text
global close
close:
	push	ebp
	mov	ebp, esp
	

	mov	ebx, [ebp+8]  ;ebp+8 is the address of the first parameter of the function 
	;ebx contains the file descriptor
	mov	eax, 6 ; command to close

	int	0x80	;call kernel

	pop	ebp
	ret
