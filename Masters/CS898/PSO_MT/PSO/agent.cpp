#include "stdafx.h"
#include "agent.h"
#include <stdlib.h>
#include <iostream>
#include <mutex>

//for now, search space is between 0 and 1000 in all dimensions
//for now, max velocity is 10
//for now, fitness is sum(pos^2), so optimal is 1000,1000


//first attempt to multithread
//put every agent on a single thread

//if false, minimize


ostream& operator<<(ostream& os, const agent& a) {

	for (int i = 0; i<a.dim; i++){
		os << "dim " << i << ": " << a.pos[i]
			<< " " << a.vel[i] << " pbest: " << a.pbest[i] << endl;
	}

	return os;

}


agent::agent(int dimension, float(*func)(int, float *)){

	dim = dimension;

	pos = new float[dimension];
	vel = new float[dimension];
	pbest = new float[dimension];

	for (int i = 0; i<dimension; i++){
		pos[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1000));
		vel[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
		pbest[i] = pos[i];

	}

	fitness = (*func)(dim, pos);

}



void agent::runStep(float(*func)(int, float *)){

	//for now, max velocity is 100
	float vMax = 100;
	float vMin = -100;


	float c1 = 2;
	float c2 = 2;


	//random float between 0 and 1
	float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));

	
	for (int i = 0; i < dim; i++){

		float gbest = gBest::getInstance().pos[i];


		vel[i] = vel[i] + c1 * r1 * (pbest[i] - pos[i]) + c2 * r2 * (gbest - pos[i]);

		if (vel[i] > vMax) vel[i] = vMax;
		if (vel[i] < vMin) vel[i] = vMin;

		pos[i] = pos[i] + vel[i];

	}


	//calculate current fitness
	float curFitness = (*func)(dim, pos);

	//compare curFitness with myFitness

	if (MAXIMIZE){

		if (curFitness > fitness){

			for (int i = 0; i< dim; i++){
				pbest[i] = pos[i];
			}

			fitness = curFitness;

		}

		//compare curFitness with globalFitness

		if (curFitness > gBest::getInstance().fitness){

			//need mutex here
			lock_guard<mutex> guard(mutex);

			for (int i = 0; i < dim; i++){
				gBest::getInstance().pos[i] = pos[i];
			}

			gBest::getInstance().fitness = curFitness;

		}
	}

	else {
		if (curFitness < fitness){

			for (int i = 0; i< dim; i++){
				pbest[i] = pos[i];
			}

			fitness = curFitness;

		}

		//compare curFitness with globalFitness

		if (curFitness < gBest::getInstance().fitness){

			//need mutex here
			lock_guard<mutex> guard(mutex);

			for (int i = 0; i < dim; i++){
				gBest::getInstance().pos[i] = pos[i];
			}

			gBest::getInstance().fitness = curFitness;

		}
	}


}

agent::~agent(){

	delete[] pos;
	delete[] vel;
	delete[] pbest;

}




void gBest::initArray(int n){

	pos = new float[n];

	for (int i = 0; i < n; i++){
		pos[i] = 0;
	}

	if (MAXIMIZE){
		fitness = FLT_MIN;
	}

	else {
		fitness = FLT_MAX;
	}

}



gBest::~gBest(){
	delete[] pos;
}