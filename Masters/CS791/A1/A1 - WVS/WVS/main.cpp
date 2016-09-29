#include <gl/glut.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>

#define DRAWREGIONS false

using namespace std;

int totalRendered = 0;

struct Point
{
	float x;
	float y;
	float m00 = 0;
	float m10 = 0;
	float m01 = 0;
	float ink = 0;
	float size = 0;
	int pixels = 0;
	bool render = true;
};

Point *stipples;
int numStipples;

int width = 0;
int height = 0;


unsigned char *inputImage;

// +z = towards eye
// -z = into screen

//NOTES:
//throwing away stipples that don't get a cone rendered for them (area too small)
//else image does not convege

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLUquadric *quad = gluNewQuadric();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	for (int i = 0; i < numStipples; i++){

		//draws cone
		glPushMatrix();

		glTranslatef(stipples[i].x + 1, stipples[i].y + 1, -10);
		glRotatef(180, 1, 0, 0);
	
		glColor3ub(i % 255, (i >> 8) % 255, (i >> 16) % 255);
		//glColor3ub(rand() % 255, rand() % 255, rand() % 255);


		if (stipples[i].render) gluCylinder(quad, 0, 5000, 500, 3, 3);

		glPopMatrix();

		//draws point
		glPushMatrix();

		glTranslatef(stipples[i].x, stipples[i].y, 0);

		glColor3f(0, 0, 0);
		//glutSolidSphere(3, 5, 5);

		glPopMatrix();

	}



	//Read the frame buffer and run weighting algorithm here
	//could multi-thread here
	
	unsigned char *data = new unsigned char[width * height * 3];


	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)data);

	int x = 0, y = 0;

	for (int i = 0; i < 3*width*height; i+=3){
	
		int stippleIndex = (int)data[i] + ((int)(data[i + 1]) * 255) + ((int)(data[i + 2]) * 65025);

		if (stippleIndex <= numStipples){

			float weight = 1 - (((int)inputImage[(y*width) + x]) / (float)255);

			//cout << weight << endl;

			stipples[stippleIndex].m00 += weight;
			stipples[stippleIndex].m01 += y * weight;
			stipples[stippleIndex].m10 += x * weight;

			stipples[stippleIndex].ink += weight;
			stipples[stippleIndex].pixels += 1;

			x+=1;

			if (x == width) {
				x = 0;
				y+=1;
			}

		}

	}


	for (int i = 0; i < numStipples; i++){

		if (stipples[i].m00 != 0){
			stipples[i].x = stipples[i].m10 / stipples[i].m00 - 0.5;
			stipples[i].y = stipples[i].m01 / stipples[i].m00 - 0.5;
		}

		if (stipples[i].m00 == 0){
			stipples[i].render = false;
		}

		stipples[i].m00 = 0;
		stipples[i].m10 = 0;
		stipples[i].m01 = 0;



	}

	delete[] data;
	

	if (!DRAWREGIONS) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int rendered = 0;

	for (int i = 0; i < numStipples; i++){

		//draws point
		glPushMatrix();

		glTranslatef(stipples[i].x, stipples[i].y, 0);

		glColor3f(0, 0, 0);



		if (stipples[i].render) {

			rendered++;

			float size = stipples[i].ink / stipples[i].pixels;

			stipples[i].size = size;
			totalRendered = rendered;


			//cout << size << endl;

			glutSolidSphere(5 * size, 4, 4);

			stipples[i].ink = 0;
			stipples[i].pixels = 0;

		}

		

		glPopMatrix();

	}

	cout << rendered << endl;


	glutSwapBuffers();




}



void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':

	{
		ofstream outputFile("C:\\Users\\Boris\\Desktop\\output.ps");


		if (outputFile.is_open())
		{
			outputFile << "%!PS" << endl;
			outputFile << "%%PageBoundingBox: 0 0 " << width << " " << height << endl;

			for (int i = 0; i < numStipples; i++){

				if (stipples[i].render) {


					outputFile << stipples[i].x << " " << stipples[i].y << " " << 5 * stipples[i].size << " 0 360 arc closepath" << endl;
					outputFile << "0 setgray fill" << endl;
					outputFile << "stroke" << endl;
				}

			}



			outputFile.close();
		}

		cout << "PRINTING" << endl;
		break;
	}

	case 't':

	{

		ofstream tsFile("C:\\Users\\Boris\\Desktop\\outputNodes");

		if (tsFile.is_open())
		{


			tsFile << totalRendered << " 0" << endl;


			for (int i = 0; i < numStipples; i++){

				if (stipples[i].render) {

					tsFile << stipples[i].x << " " << stipples[i].y << endl;

				}
			}


			tsFile.close();


		}


		ofstream weightFile("C:\\Users\\Boris\\Desktop\\outputWeights");

		if (weightFile.is_open())
		{


			weightFile << totalRendered << " 0" << endl;


			for (int i = 0; i < numStipples; i++){

				if (stipples[i].render) {

					weightFile << stipples[i].size << endl;

				}
			}


			weightFile.close();


		}



		break;


	}

	}
}



int main(int argc, char **argv) {


	string inputLine;

	ifstream inputImageFile("..\\WVS\\tests\\cat.pgm");

	if (inputImageFile.is_open()){

		//skip first two lines
		getline(inputImageFile, inputLine);
		getline(inputImageFile, inputLine);

		//grab resolution
		getline(inputImageFile, inputLine);

		stringstream stream(inputLine);

		while (stream) {
			int n;
			stream >> n;

			if (width == 0){
				width = n;
			}

			else height = n;

		}



		inputImage = new unsigned char[height*width];


		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				getline(inputImageFile, inputLine);

				stringstream stream(inputLine);
				int val;
				stream >> val;


				inputImage[((height-1-i)*width) + j] = val;

			}
		}

		inputImageFile.close();


	}

	/*
	for (int i = 0; i < height*width; i++){

		cout << (int)inputImage[i] << endl;
	}
	*/

	numStipples = 100000;


	stipples = new Point[numStipples];

	srand(time(NULL));


	for (int i = 0; i < numStipples; i++){

		stipples[i].x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (width)));
		stipples[i].y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (height)));

	}



	


	
	
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Weighted Voronoi Stippling");

	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, 0.f, 100.f);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// register callbacks
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);

	// enter GLUT event processing cycle
	glutMainLoop();

	

	getchar();

	return 1;
}



