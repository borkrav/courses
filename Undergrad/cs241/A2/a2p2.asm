	sltu $4, $1, $2		;if $1 < $2 $4 is 1, else $4 is 0 (unsigned) 
	beq $4, $0, 2
	add $3, $3, $2		;if $1 < $2
	jr $31
	add $3, $3, $1		;if $1 > $2
	jr $31
