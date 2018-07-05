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
    leal 12(%ebp), %eax

    test $0x0000000F, %eax
    jne unaligned
    leal 8(%ebp), %eax
    test $0x0000000F, %eax
    jne unaligned

aligned:
    movl $0, %eax
	movl 16(%ebp), %ecx
	imul %ecx, %ecx
	movl 12(%ebp), %esi
	movl 8(%ebp), %ebx
for1: cmpl %ecx, %eax
	jge end
	movdqa (%ebx, %eax), %xmm0
	psllq $4, %xmm0
	movda %xmm0, (%esi, %eax)
	addl $16, %eax
	jmp for1

unaligned:
    movl $0, %eax
	movl 16(%ebp), %ecx
	imul %ecx, %ecx
	movl 12(%ebp), %esi
	movl 8(%ebp), %ebx
for1: cmpl %ecx, %eax
	jge end
	movdqu (%ebx, %eax), %xmm0
	psllq $4, %xmm0
	movdqu %xmm0, (%esi, %eax)
	addl $16, %eax
	jmp for1
end:

# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
