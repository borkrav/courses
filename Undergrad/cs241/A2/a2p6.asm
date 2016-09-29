; $1 first value in hex
; $2 second value in hex, not used
; $29 stdout register
; $10 10
; $4 1
; $5 -1
; $6 number operating on, quotient
; $7 remainder
; $8 length counter
; $9 45
; $11 48


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


	beq $0, $0, print

print: 	lis $7
	.word 4
	add $30, $30, $7
	lw $7, -4($30)

	add $7, $7, $11
	sw $7, 0($29)  
	sub $8, $8, $4
	bne $8, $0, print

	lis $13
	.word 10
	sw $13, 0($29)

	jr $31
