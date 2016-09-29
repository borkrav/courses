class agent;


class master {

public:

	master(int numParticles, int dim, int runs, float(*func)(int dim, float *));
	void finishStep(int numParticles, int dim);
	~master();


private:
	agent **particles;
	int dim;


};