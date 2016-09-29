class agent;


class master {

public:

	master(int numParticles, int dim, int runs, float(*func)(int dim, float *));
	~master();


private:
	agent **particles;
	int dim;


};