; $1 Current adress inside the array
; $2 size of array
; $3 max
; $4 size constant = 4
; $5 current array element
; $6 -1 for decreasing size of the array
; $7 comparing variable

	lis $4
	.word 4
	lw $3, 0($1)		;sets max to first thing in the array
	lis $6
	.word -1

top: 	add $1, $1, $4
	lw $5, 0($1)		
	slt $7, $3, $5		;$7 = 1, max = $5, otherwise loop

	beq $7, $0, 2	
	add $3, $0, $0
	add $3, $5, $0

	add $2, $2, $6
	bne $2, $0, top

	jr $31
