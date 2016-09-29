#include "pizzaok.h"

bool pizzaok(char *input, int sizes, int basicSize){

	
	for (int i = (int) basicSize; i < (int) basicSize + sizes; i++) {
		if ((int) *input == i) {
			return 1;
		}
	}
	
	return 0;

}

bool pizzaok(int *input, int sizes, int basicSize){
	
	
	for (int i =  basicSize-48; i < basicSize-48 + sizes; i++) {
		if (*input == i) {
			return 1;
		}
	}
	
	return 0;
	
}