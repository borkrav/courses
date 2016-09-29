;$1 current position in array
;$2 current size of the array
;$3 value of current letter
;$4 4
;$5 -1
;$6 ascii value
;$7 write adress
;$8 64


	bne $2, $0, 1
	jr $31 

	lis $4
	.word 4
	lis $5
	.word -1
	lis $8
	.word 64
	lis $7
	.word 0xFFFF000C

loop:	lw $3, 0($1)
	add $1, $1, $4
	add $2, $2, $5
	
	bne $3, $0, 3
	lis $6
	.word 32
	sw $6, 0($7)

	beq $3, $0, 2
	add $3, $3, $8
	sw $3, 0($7)

	bne $2, $0, loop

	jr $31
