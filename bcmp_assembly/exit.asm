section .text
global exit
exit:
	push	ebp
	mov	ebp, esp
	

	push 0x1	; the exit value
	mov eax, 1	; command to exit
	int 0x80	; call kernel

	; Will not get here (we did an exit)

	pop	ebp
	ret
