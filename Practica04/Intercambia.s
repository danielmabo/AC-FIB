 .text
	.align 4
	.globl Intercambiar
	.type Intercambiar,@function
Intercambiar:
        # Aqui viene vuestro codigo

        push %ebp
        movl %esp, %ebp
        subl $12, %esp
        pushl %ebx
        pushl %esi

        movl 12(%ebp), %eax #i
        movl 16(%ebp), %ebx #j
        movl 8(%ebp), %ecx #@v
        imul $12, %esi #12*i
        imul $12, %edx #12*j

        movb (%ecx, %esi), %al
        movb %al, -4(%ebp)
        movb (%ecx, %edx), %al
        movb %al, (%ecx, %esi)
        movb -4(%ebp), %al
        movb %al, (%ecx, %edx)

        movl 4(%ecx, %esi), %eax
        movl %eax, -12(%ebp)
        movl 4(%ecx, %edx), %eax
        movl %eax, 4(%ecx, %esi)
        movl -12(%ebp), %eax
        movl %eax, 4(%ecx, %edx)

        movl 8(%ecx, %esi), %eax
        movl %eax, -8(%ebp)
        movl 8(%ecx, %edx), %eax
        movl %eax, 8(%ecx, %esi)
        movl -8(%ebp), %eax
        movl %eax, 8(%ecx, %edx)

        popl %esi
        popl %ebx
        movl %ebp,%esp
        popl %ebp
        ret
