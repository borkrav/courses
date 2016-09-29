int wain (int a, int b){
	int quotient = 1;
	int remainder = 1;
	int aa = 1;
	int bb = 1;
	int temp = 1;
	int lastRemainder = 1;

	if (a < b) {
		temp = a;
		a = b;
	 	b = temp;}

	else {}

	aa = a;
	bb = b;
	


	while (remainder != 0){
		
	if (bb == 0){
		lastRemainder = 0;
		remainder = 0;}

	else{
	quotient = aa/bb;
	lastRemainder = bb;
	remainder = aa - quotient*bb;

	aa = bb;
	bb = remainder;
	}
		
	}

	

	return lastRemainder;
}
