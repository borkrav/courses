class materialJob {

private:

	float urWidth;
	float urLength;
	float lrWidth;
	float lrLength;
	float partHeight;
	float diskHeight;
	float diskRadius;
	bool direction;


public:

	materialJob();
	materialJob(float urW, float urH, float lrW, float lrH, float pH, float dH, float dR, bool dir);

	void takeUserInput(materialJob* m);

	bool validateFloat(float f);
	bool validateDiskHeight(float f);
	bool validatePathDirection(float f);

	void calculatePositions();

};




