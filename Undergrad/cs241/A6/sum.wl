int wain (int a, int b){
	int temp =0;
	int result = 0;
	if (a > b) {
		temp = a;
		a = b;
	 	b = temp;}

	else {}

	while (a <= b){
		result = result + a;
		a = a + 1;
	}

	return result;
}

	

