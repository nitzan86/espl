section .text
global atod
atod:
	push	ebp
	mov	ebp, esp
	mov eax, 0x0
;	mov ecx, 0xA ;0xA = 10

.L5:
	mov	ecx, [ebp+8]  ;ebp+8 is the address of the first parameter of the function 
	mov	ecx, [ecx]	;ecx has now the value of the first cell in the array
	movzx ecx, cl ;first byte of ecx is cl, second byte is ch. First word (2 first bytes) is cx

	cmp ecx, 0x0 ;checks if we're done with the string
	je .L3 ;if so - jump to .L3 (leave)

	mov edx, 0xA ;0xA = '0'
	mul edx ;multiplies eax by 10
	sub ecx, 0x30
	
	add eax, ecx ;adds digit to answer. ans = eax, digit = ecx
	add	DWORD [ebp+8], 1
	jmp	.L5

.L3:
	pop	ebp
	ret
