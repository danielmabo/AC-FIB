 .text
	.align 4
	.globl Ordenar
	.type Ordenar,@function
Ordenar:
        # Aqui viene vuestro codigo
        push %ebp
        movl %esp, %ebp
        subl $8, %esp
        pushl %ebx
        pushl %esi

        movl 8(%ebp), %ebx #@v
        movl $0, %esi #i

fori:   imull $12, %esi, %eax
        cmpl $0x80000000, 4(%ebx, %eax)
        je endfori
        movl $1, %ecx
        addl %esi, %ecx #j

forj:   imull $12, %ecx, %edx
        cmpl $0x80000000, 4(%ebx, %edx)
        je endforj
        
        movl 4(%ebx, %edx), %edx
        cmpl 4(%ebx, %eax), %edx
        jge endif

        pushl %ecx #salvamos j
        
        #paso parametros
        pushl %ecx
        pushl %esi
        pushl %ebx
        call Intercambiar
        addl $12, %esp
        popl %ecx

endif:  incl %ecx
        jmp forj

endforj: incl %esi
        jmp fori

endfori: movl %esi, %eax


        popl %esi
        popl %ebx
        movl %ebp,%esp
        popl %ebp
        ret
