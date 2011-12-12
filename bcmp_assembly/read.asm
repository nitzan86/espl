section .text
global read
read:
	push	ebp
	mov	ebp, esp
	

	mov	ebx, [ebp+8]  ;ebp+8 is the address of the first parameter of the function 
	;ebx contains the file descriptor
	mov	ecx, [ebp+12] ;ebp+12 is the address of the second parameter of the function
;	ecx - the buffer to read to
	mov	edx, [ebp+16]
;	edx - the length of the buffer to read
	mov	eax, 3 ; command to read

	int	0x80	;call kernel

; In eax we have the number of read bytes, if it is 0 we reached the end of the file
; TODO - return the value in eax

	pop	ebp
	ret
