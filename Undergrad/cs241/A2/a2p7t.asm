;$10 current position in array
;$2 current size of the array
;$1 value of current letter
;$4 4
;$5 -1
;$7 location of print label

	bne $2, $0, 1	;returns if array is size zero
	jr $31 

	lis $4
	.word 4
	lis $5
	.word -1

	add $10, $1, $0


	sw $31, -4($30)
	lis $31
	.word 4
	sub $30, $30, $31

	lis $7
	.word print

 

	

loop:	lw $1, 0($10)
	add $10, $10, $4		;moves through the array
	add $2, $2, $5
	
	jalr $7

	bne $2, $0, loop

	lis $31
	.word 4
	add $30, $30, $31
	lw $31, -4($30)
	jr $31




print:


; $1 first value in hex
; $2 location of the print function
; $29 stdout register
; $10 10
; $4 1
; $5 -1
; $6 number operating on, quotient
; $7 remainder
; $8 length counter
; $9 45
; $11 48


	sw $2, -4($30)		;pushes registers
	sw $4, -8($30)
	sw $5, -12($30)
	sw $6, -16($30)
	sw $7, -20($30)
	sw $8, -24($30)
	sw $9, -28($30)
	sw $10, -32($30)
	sw $11, -36($30)
	sw $13, -40($30)
	sw $29, -44($30)
	sw $1, -48($30)
	sw $3, -52($30)
	lis $29
	.word 52
	sub $30, $30, $29
	
	lis $29
	.word 0xFFFF000C
	lis $10
	.word 10
	lis $4
	.word 1
	lis $5
	.word -1
	lis $9
	.word 45
	lis $11
	.word 48
	add $6, $0, $0
	add $7, $0, $0
	add $8, $0, $0
	
	;check if the number is negative, invert it
	
	slt $3, $1, $0		;if number is negative, $3 = 1
	beq $3, $4, neg
	add $6, $1, $0	
	beq $0, $0, div

neg:	div $1, $5	
	mflo $6
	sw $9, 0($29)
	beq $0, $0, div	

div:	add $8, $4, $8
	divu $6, $10
	mflo $6
	mfhi $7

	;pushes remainder onto the stack
	sw $7, -4($30)
	lis $7
	.word 4
	sub $30, $30, $7

	bne $6, $0, div	


	beq $0, $0, write

write: 	lis $7
	.word 4
	add $30, $30, $7
	lw $7, -4($30)

	add $7, $7, $11
	sw $7, 0($29)  
	sub $8, $8, $4
	bne $8, $0, write

	lis $13		;newline
	.word 10
	sw $13, 0($29)
	

	lis $29		; pops registers
	.word 52
	add $30, $30, $29	

	lw $2, -4($30)
	lw $4, -8($30)
	lw $5, -12($30)
	lw $6, -16($30)
	lw $7, -20($30)
	lw $8, -24($30)
	lw $9, -28($30)
	lw $10, -32($30)
	lw $11, -36($30)
	lw $13, -40($30)
	lw $29, -44($30)
	lw $1, -48($30)
	lw $3, -52($30)
	jr $31
	
