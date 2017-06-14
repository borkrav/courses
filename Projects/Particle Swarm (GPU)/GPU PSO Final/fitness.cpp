
#include "fitness.h"
#include "agent.h"
#include "math.h"


//input - agent
//output - fitness calculation

float fitness::testFunction(int dim, float * pos){

	float total = 0;

	for (int i = 0; i<dim; i++){
		total += -0.31* pow((pos[i]), 2) + 20;
	}

	return total;


}