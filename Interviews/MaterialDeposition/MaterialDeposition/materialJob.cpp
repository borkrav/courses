#include "materialJob.h"
#include <iostream>
#include <iomanip>

using namespace std;

materialJob::materialJob() {

	takeUserInput(this);

}

materialJob::materialJob(float lrW, float lrL, float urW, float urL, float pH, float dH, float dR, bool dir) {

	urWidth = urW;
	urLength = urL;
	lrWidth = lrW;
	lrLength = lrL;
	partHeight = pH;
	diskHeight = dH;
	diskRadius = dR;
	direction = dir;

}

//Validates floating point values from user input (Only positive values make sense)
bool materialJob::validateFloat(float f) {

	bool condition = (f > 0);

	if (!condition) {
		cerr << "Please enter positive value" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return condition;

}

//Validates Step Up height (Should be divisor of Overall Part Height)
bool materialJob::validateDiskHeight(float f) {

	
	bool condition = (fmod(partHeight, f) < 0.1); //avoids floating point percision errors

	if (!condition) {
		cerr << "Please enter a divisor of Part Height" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return condition;

}

//Validates path direction (Should be 0 or 1)
bool materialJob::validatePathDirection(float f) {

	bool condition = (f == 0 || f == 1);

	if (!condition) {
		cerr << "Please enter 0 or 1" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return condition;

}

//Take in all user input and validate
void materialJob::takeUserInput(materialJob* m) {

	do {
		cout << "Upper Rectangle Width:		|";
		cin >> m->urWidth;
	} while (!validateFloat(m->urWidth));

	do {
		cout << "Upper Rectangle Length:		|";
		cin >> m->urLength;
	} while (!validateFloat(m->urLength));

	do {
		cout << "Lower Rectangle Width:		|";
		cin >> m->lrWidth;
	} while (!validateFloat(m->lrWidth));

	do {
		cout << "Lower Rectangle Length:		|";
		cin >> m->lrLength;
	} while (!validateFloat(m->lrLength));

	do {
		cout << "Part Height:			|";
		cin >> m->partHeight;
	} while (!validateFloat(m->partHeight));

	do {
		cout << "Step Up Height:			|";
		cin >> m->diskHeight;
	} while (!(validateFloat(m->diskHeight) && validateDiskHeight(m->diskHeight)));

	do {
		cout << "Material Radius:		|";
		cin >> m->diskRadius;
	} while (!validateFloat(m->diskRadius));

	float direction;

	do {
		cout << "Path Direction (0 = v, 1 = h):	|";
		cin >> direction;
	} while (!validatePathDirection(direction));

	m->direction = direction;


}

void materialJob::calculatePositions() {


	cout << fixed;
	cout << setprecision(5);


	int layers = partHeight / diskHeight;

	//Segment part into layers
	for (int i = 0; i < layers; i++) {
		
		
		//Calculate dimensions at a given layer
		float widthAtLayer = lrWidth + (urWidth - lrWidth)*i / layers;
		float lengthAtLayer = lrLength + (urLength - lrLength)*i / layers;

		//Number of material depositions at given layer
		int rows = ceil(widthAtLayer / (diskRadius*2));
		int columns = ceil(lengthAtLayer / (diskRadius*2));

		//The "bottom left corner" of the current layer - relative to 0,0,0 reference point
		//Every layer begins from this corner
		float startingX = (lrLength - lengthAtLayer) / 2 + (lengthAtLayer - (columns*diskRadius*2)) / 2;
		float startingY = (lrWidth - widthAtLayer) / 2 + (widthAtLayer - (rows*diskRadius*2)) / 2;

		bool returnPath = 0;

		//Horizontal Path
		if (direction) {

			for (int j = 0; j < columns; j++) {
				for (int k = 0; k < rows; k++) {

					if (!returnPath) {
						cout << "X" << startingX + diskRadius*(1 + 2 * k) << "	Y" << startingY + diskRadius*(1 + 2 * j) << "	Z" << i*diskHeight << endl;
					}

					else {
						cout << "X" << (rows*diskRadius * 2 + startingX) - diskRadius*(1 + 2 * k) << "	Y" << startingY + diskRadius*(1 + 2 * j) << "	Z" << i*diskHeight << endl;
					}

				}

				if (returnPath) returnPath = 0;
				else returnPath = 1;

			}
		}

		//Vertical Path
		else {
			for (int k = 0; k < columns; k++) {
				for (int j = 0; j < rows; j++) {

					if (!returnPath) {
						cout << "X" << startingX + diskRadius*(1 + 2 * k) << "	Y" << startingY + diskRadius*(1 + 2 * j) << "	Z" << i*diskHeight << endl;
					}

					else {
						cout << "X" << startingX + diskRadius*(1 + 2 * k) << "	Y" << (rows*diskRadius * 2 + startingY) - diskRadius*(1 + 2 * j) << "	Z" << i*diskHeight << endl;
					}

				}

				if (returnPath) returnPath = 0;
				else returnPath = 1;

			}
		}


	}






}
