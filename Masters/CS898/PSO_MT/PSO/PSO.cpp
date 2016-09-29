// PSO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "master.h"
#include <vector>
#include <time.h>
#include "fitness.h"
#include <chrono>

using namespace std;


//impementation of PSO 
//Original paper, Kennedy and Eberhart

/*overview

initialize particles with random X/Y, velocities
evaluate fitness function = is where I'm at good?
- update pBest or gBest
update velocity and position


no goal, goal is written into fitness function
fitness function eval is what you multithread w/ CUDA
compare runtimes with more complex functions?

*/

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	//the fitness function to evaluate
	float(*func)(int dim, float *pos) = fitness::testFunction;


	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	//particles, dimensions, runs, function

	master m = master(10000, 3, 1000, func);

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cout << "Runtime: " << time_span.count() << " seconds" << endl;


	//simple quadratic function

	//1000 runs, 1000 particles, 50 dimensions 
	//1 = 3.93302s
	//4 = 1.10729s

	//10000 runs, 1000 particles, 50 dimensions
	//1 = 38.9511s
	//4 = 10.5107s
	
	//3.7x speedup 




	return 0;
}

