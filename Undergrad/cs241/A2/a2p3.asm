	bne $2, $0, 3		;if $2=0, load -1 into $3
	lis $3
	.word -1
	jr $31

	lis $4
	.word 4
	multu $2, $4
	mflo $5
	sub $5, $5, $4 		;$5 is the offset
	add $6, $1, $5		;$6 is the final adress
	lw $3, 0($6)
	jr $31
