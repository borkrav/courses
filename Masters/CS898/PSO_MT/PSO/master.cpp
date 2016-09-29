#include "stdafx.h"
#include "master.h"
#include "agent.h"
#include "fitness.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> 
#include <iostream>
#include <atomic>
#include <iomanip>     


using namespace std;

const int THREADS = 4;

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
	
	cout << fixed;


	//output gbest - optimal solution found
	for (int i = 0; i < dim; i++){
		cout << std::setprecision(9) << gBest::getInstance().pos[i] << endl;
	}


}


master::~master(){

	for (int i = 0; i < dim; i++){
		delete particles[i];
	}

	delete[] particles;




}
