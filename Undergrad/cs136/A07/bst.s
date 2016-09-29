	.file	"bst.c"
	.text
.globl insertbst
	.type	insertbst, @function
insertbst:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	cmpl	$0, 12(%ebp)
	jne	.L2
	movl	$12, (%esp)
	call	malloc
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-12(%ebp), %eax
	movl	$0, 4(%eax)
	movl	-12(%ebp), %eax
	movl	$0, 8(%eax)
	movl	-12(%ebp), %eax
	jmp	.L3
.L2:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	8(%ebp), %eax
	jle	.L4
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	insertbst
	movl	12(%ebp), %edx
	movl	%eax, 4(%edx)
	movl	12(%ebp), %eax
	jmp	.L3
.L4:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	8(%ebp), %eax
	jge	.L5
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	insertbst
	movl	12(%ebp), %edx
	movl	%eax, 8(%edx)
	movl	12(%ebp), %eax
	jmp	.L3
.L5:
	jmp	.L1
.L3:
.L1:
	leave
	ret
	.size	insertbst, .-insertbst
	.ident	"GCC: (Ubuntu 4.4.1-4ubuntu9) 4.4.1"
	.section	.note.GNU-stack,"",@progbits
