#include <iostream>

using namespace std;

//if false, minimize
#define MAXIMIZE false

class agent {


public:

	agent(){};
	agent(int dimension, float(*func)(int, float *));
	~agent();

	void runStep(float(*func)(int, float *));

	friend ostream& operator<<(ostream& os, const agent& a);

	float *pos;
	float *vel;
	float *pbest;
	int dim;
	float fitness;


};



//gBest singleton class
class gBest {

public:

	static gBest& getInstance(){
		static gBest instance;

		return instance;
	}

	void initArray(int n);
	float fitness;
	float *pos;

private:
	gBest() {};
	gBest(gBest const&) = delete;
	void operator=(gBest const&) = delete;

	~gBest();




};