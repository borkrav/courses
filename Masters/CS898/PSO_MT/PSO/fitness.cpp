#include "stdafx.h"
#include "fitness.h"
#include "agent.h"
#include "math.h"

//input - agent
//output - fitness calculation

float fitness::testFunction(int dim, float * pos){

	float total = 0;

	//sphere function
	/*
	for (int i = 0; i < dim; i++){

		float val = pos[i];

		total += (pow(val, 2));

	}
	*/


	//Rosenbrock function
	/*
	for (int i = 0; i < dim-1; i++){


		total += 100 * pow((pos[i + 1] - pow(pos[i], 2)), 2) + pow((pos[i] - 1), 2);

	}
	*/

	//Ackley's function


	/*
	float sum1 = 0;

	for (int i = 0; i < dim; i++){
		float val = pos[i]; 

		sum1 += pow(val, 2);
	}

	float sum2 = 0;

	for (int i = 0; i < dim; i++){
		float val = pos[i];

		sum2 += cos(2 *(atan(1) * 4)*val);
	} 

	total = -20 * exp(-0.2*sqrt(1 / dim*sum1)) - exp(1 /dim*sum2) + 20 * exp(1);
	*/


	for (int i = 0; i < dim; i++){

		float val = pos[i];

		total = 2*pow(val,2) * sin(exp(sin(exp(sin(val)))));

	}


	return total;


}