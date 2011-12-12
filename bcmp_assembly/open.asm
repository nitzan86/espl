section .text
global open
open:
	push	ebp
	mov	ebp, esp
	

	mov	ebx, [ebp+8]  ;ebp+8 is the address of the first parameter of the function 
	;ebx contains the file name
	mov	ecx, [ebp+12] ;ebp+12 is the address of the second parameter of the function
;	ecx - the acess bits
	mov	edx, [ebp+16]
;	edx - the file permissions
	mov	eax, 5 ; command to open

	int	0x80	;call kernel


	pop	ebp
	ret
