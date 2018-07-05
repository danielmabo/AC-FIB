.text
	.align 4
	.globl procesar
	.type	procesar, @function
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo

	movl $0, %eax
	movl 16(%ebp), %ecx
	imul %ecx, %ecx
	movl 12(%ebp), %esi
	movl 8(%ebp), %ebx
for: cmpl %ecx, %eax
	jge end
	movdqu (%ebx, %eax), %xmm0
	psllq $4, %xmm0
	movdqu %xmm0, (%esi, %eax)
	addl $16, %eax
	jmp for
end:


# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
