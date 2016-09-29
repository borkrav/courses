;$1 pointer to root (does not change)
;$2 size of array
;$3 result
;$4 4
;$5 -1
;$6 current value of array
;$7 temp left
;$8 temp right


	lis $4
	.word 4
	lis $5
	.word -1

exit: 	jr $31

top:	

	;base case
	beq $6, $5, exit	


	go left, store in 7
	








	go right, store in 8


	


	mind max of 7 and 8, store in 3










