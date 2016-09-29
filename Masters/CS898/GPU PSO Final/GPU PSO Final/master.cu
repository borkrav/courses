#include "master.h"
#include "agent.h"
#include "fitness.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> 
#include <iostream>
#include <atomic>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <curand_kernel.h>
#include <math.h>

using namespace std;

const int THREADS = 1;

mutex mtx;
condition_variable cv;
condition_variable cv2;


bool ready[THREADS] = { false };

bool waker = true;
bool done = false;

atomic<int> counter;


using namespace std;


void work(agent** particles, int numParticles, float(*func)(int dim, float *), int id){

	unique_lock<mutex> lck(mtx);

	while (true){

		while (!ready[id]) cv.wait(lck);
		lck.unlock();
		if (done) break;

		for (int j = id; j < numParticles; j += THREADS){
			particles[j]->runStep(func);
		}

		lck.lock();

		ready[id] = false;


		if (++counter == THREADS){
			counter = 0;
			waker = true;
			cv2.notify_all();
		}

	}

}


__global__ void calculateFitness(int *dim, float *pos, float *fitness, int *numParticles){

	int particle = blockIdx.x * blockDim.x + threadIdx.x;

	if (particle < *numParticles){

		float total = 0;

		//sphere function
		/*
		for (int i = 0; i < *dim; i++){

			float val = pos[particle * (*dim) + i];
			
			total += (pow(val, 2));

		}
		*/

		//Rosenbrock function

		/*
		for (int i = 0; i < *dim - 1; i++){


			total += 100 * pow((pos[particle * (*dim) + i + 1] - pow(pos[particle * (*dim) + i], 2)), 2) + pow((pos[particle * (*dim) + i] - 1), 2);

		}
		*/
		/*
		float sum1 = 0;

		for (int i = 0; i < *dim; i++){
			float val = pos[particle * (*dim) + i];

			sum1 += pow(val, 2);
		}

		float sum2 = 0;

		for (int i = 0; i < *dim; i++){
			float val = pos[particle * (*dim) + i];

			sum2 += cos(2 * (atan(1.0) * 4)*val);
		}

		total = -20 * expf(-0.2*sqrt(1 / *dim*sum1)) - expf(1 / *dim*sum2) + 20 * expf(1.0);

		*/



		for (int i = 0; i < *dim; i++){

			float val = pos[particle * (*dim) + i];

			total += 2 * pow(val, 2) * sin(exp(sin(exp(sin(val)))));

		}



		fitness[particle] = total;


	}



}



void master::finishStep(int numParticles, int dim){

	float *dev_pos;
	float *dev_fitness;
	int *dev_dim;
	int *dev_numParticles;

	int cudastatus;

	float *h_pos = new float[numParticles*dim];
	for (int i = 0; i < numParticles; i++){
		for (int j = 0; j < dim; j++){
			h_pos[(i*dim)+j] = particles[i]->pos[j];
		}
	}

	//for (int i = 0; i < numParticles*dim; i++){
	//	cout << h_pos[i] << endl;
	//}

	float *h_fitness = new float[numParticles]{0};

	cudastatus = cudaMalloc((void**)&dev_pos, numParticles * dim * sizeof(float));
	cudastatus = cudaMalloc((void**)&dev_fitness, numParticles * sizeof(float));
	cudastatus = cudaMalloc((void**)&dev_dim, sizeof(int));
	cudastatus = cudaMalloc((void**)&dev_numParticles, sizeof(int));
	
	cudastatus = cudaMemcpy(dev_pos, h_pos, numParticles * dim * sizeof(float), cudaMemcpyHostToDevice);
	cudastatus = cudaMemcpy(dev_fitness, h_fitness, numParticles * sizeof(float), cudaMemcpyHostToDevice);
	cudastatus = cudaMemcpy(dev_dim, &dim, sizeof(int), cudaMemcpyHostToDevice);
	cudastatus = cudaMemcpy(dev_numParticles, &numParticles, sizeof(int), cudaMemcpyHostToDevice);

	if (numParticles > 32){
		calculateFitness << < ceil((float)numParticles / 32), 32 >> >(dev_dim, dev_pos, dev_fitness, dev_numParticles);
	}

	else {
		calculateFitness << < 1, numParticles >> >(dev_dim, dev_pos, dev_fitness, dev_numParticles);
	}

	cudaDeviceSynchronize();

	//run kernel here

	cudaMemcpy(h_fitness, dev_fitness, numParticles * sizeof(float), cudaMemcpyDeviceToHost);

	//for (int i = 0; i < numParticles; i++)
	//	cout << h_fitness[i];

	float gBest = gBest::getInstance().fitness;

	for (int i = 0; i < numParticles; i++){
		if (MAXIMIZE){
			if (h_fitness[i] > gBest){
				gBest::getInstance().fitness = h_fitness[i];

				for (int j = 0; j < dim; j++){
					gBest::getInstance().pos[j] = particles[i]->pos[j];
				}
			}

			if (h_fitness[i] > particles[i]->fitness){
				particles[i]->fitness = h_fitness[i];

				for (int j = 0; j < dim; j++){
					particles[i]->pbest[j] = particles[i]->pos[j];
				}
			}
		}

		else{
			if (h_fitness[i] < gBest){
				gBest::getInstance().fitness = h_fitness[i];
				//cout << gBest::getInstance().fitness << endl;
				for (int j = 0; j < dim; j++){
					gBest::getInstance().pos[j] = particles[i]->pos[j];
				}
			}
			if (h_fitness[i] < particles[i]->fitness){
				particles[i]->fitness = h_fitness[i];

				for (int j = 0; j < dim; j++){
					particles[i]->pbest[j] = particles[i]->pos[j];
				}
			}
		}

	}

	cudaFree(dev_pos);
	cudaFree(dev_dim);
	cudaFree(dev_fitness);
	cudaFree(dev_numParticles);

	delete[] h_pos;
	delete[] h_fitness;



}


master::master(int numParticles, int dim, int runs, float(*func)(int dim, float *)){

	particles = new agent*[numParticles];

	for (int i = 0; i < numParticles; i++){
		particles[i] = new agent(dim, func);
	}


	gBest::getInstance().initArray(dim);


	thread threads[THREADS];

	for (int i = 0; i < THREADS; ++i){
		threads[i] = thread(work, particles, numParticles, func, i);
	}

	unique_lock<mutex> lck(mtx);

	for (int i = 0; i < runs; i++){

		for (int i = 0; i < THREADS; i++) ready[i] = true;

		//finish step
		finishStep(numParticles, dim);

		cv.notify_all();

		waker = false;

		while (!waker) cv2.wait(lck);

	}

	done = true;
	cout << "done" << endl;
	for (int i = 0; i < THREADS; i++) ready[i] = true;
	cv.notify_all();
	lck.unlock();

	for (auto& th : threads) th.join();
	

	//output gbest - optimal solution found
	for (int i = 0; i < dim; i++){
		cout << gBest::getInstance().pos[i] << endl;
	}


}


master::~master(){

	for (int i = 0; i < dim; i++){
		delete particles[i];
	}

	delete[] particles;




}
