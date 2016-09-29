// A2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define PI 3.14159265

using namespace std;

default_random_engine gen;
normal_distribution<double> normalDist(0.0, 1.0);


struct point{
	double x;
	double y;
};

struct segment{
	point a;
	point b;
};


point operator+(const point &p1, const point &p2){
	return point { p1.x + p2.x, p1.y + p2.y };
}


point *points;
point *results;


//parameters related to simulation
int width = 1680;
int height = 1050;
int circleSampling = 360; //can vary
int averageDistance;
double delta = 1;
//double closeRadius = 10;
double farRadius = 100;
double sigma =  100; //can vary




point brownianMotion(point input){


	double xOffset = normalDist(gen);
	double yOffset = normalDist(gen);


	double pointx =  0.1*xOffset * averageDistance * delta;
	double pointy = 0.1*yOffset * averageDistance * delta;


	return point{pointx, pointy};
	return point{ 0, 0 };


}

point fairing(point input, point prev, point next){

	double x = 0.1*((delta*next.x + delta*prev.x) / (2 * delta) - input.x);
	double y = 0.1*((delta*next.y + delta*prev.y) / (2 * delta) - input.y);

	return point{x,y};
	return point{ 0, 0 };

}


point getPointOnSegment(point input, segment line){
	double dx = line.b.x - line.a.x;
	double dy = line.b.y - line.a.y;

	float t = ((input.x - line.a.x) * dx + (input.y - line.a.y) * dy) /
		(dx * dx + dy * dy);


	if (t < 1 && t > 0)
	{
		return point{ line.a.x + t * dx, line.a.y + t * dy };
	}

	if (t < 1){
		return point{ line.a.x ,line.a.y };
	}

	if (t > 0){
		return point{ line.b.x, line.b.y };
	}

	//return point{ 0, 0 };

}


point attractionRepulsion(point input, int index){
	
	vector<segment> segments;

	double totalForceX = 0;
	double totalForceY = 0;


	//very inefficient brute force, use KD tree if time permits
	//finds all points within the radius
	for (int i = 0; i < circleSampling; i++){
		
		double distanceA = sqrt(pow((input.x - points[i].x), 2) + pow((input.y - points[i].y), 2));
		double distanceB = sqrt(pow((input.x - points[i+1].x), 2) + pow((input.y - points[i+1].y), 2));

		bool add = true;

		if (index == 0 && i == circleSampling - 1 && i+1 == circleSampling - 1) add = false;
		if (index == circleSampling - 1 && i == 0 && i+1 == 0) add = false;
		if (i == index + 1 || i == index - 1 || i == index) add = false;
		if (i+1 == index + 1 || i+1 == index - 1 || i+1 == index) add = false;


		if (distanceA < farRadius && distanceB < farRadius && add){
			segments.push_back(segment{ points[i], points[i+1] });
		}

	}

	cout << segments.size() << endl;

	
	for (int i = 0; i < segments.size(); i++){

		point closest = getPointOnSegment(input, segments[i]);

		
		double forceX = abs(input.x - closest.x) / (averageDistance*delta);
		forceX = ((input.x - closest.x) / abs(input.x - closest.x)) * (pow((sigma / forceX), 12) - pow((sigma / forceX), 6));

		if (sigma*farRadius <= abs(input.x - closest.x)) forceX = 0;


		if (forceX < -1) forceX = -1;
		else if (forceX > 1) forceX = 1;

		double forceY = abs(input.y - closest.y) / (averageDistance*delta);
		forceY = ((input.y - closest.y) / abs(input.y - closest.y)) * (pow((sigma / forceY), 12) - pow((sigma / forceY), 6));

		if (sigma*farRadius <= abs(input.y - closest.y)) forceY = 0;

		if (forceY < -1) forceY = -1;
		else if (forceY > 1) forceY = 1;

		totalForceX += forceX;
		totalForceY += forceY;
	

	}

	
	return point{totalForceX, totalForceY};
	return point{ 0, 0 };

}



void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLUquadric *quad = gluNewQuadric();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0);


	//draw the curve using lines
	//change this later to a curve

	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < circleSampling; i++){
		glVertex2d(points[i].x, points[i].y);
	}

	glVertex2d(points[0].x, points[0].y);



	//recalculate positons

	//fist point
	results[0] = brownianMotion(points[0]) + fairing(points[0], points[circleSampling - 1], points[1]) + attractionRepulsion(points[0], 0);

	for (int i = 1; i < circleSampling - 1; i++){

		results[i] = brownianMotion(points[i]) + fairing(points[i], points[i - 1], points[i + 1]) + attractionRepulsion(points[i], i);
	}
	//last point
	results[circleSampling - 1] = brownianMotion(points[circleSampling - 1]) + fairing(points[circleSampling - 1], points[circleSampling - 2], points[0]) + attractionRepulsion(points[circleSampling-1], circleSampling-1);


	for (int i = 0; i < circleSampling; i++){
		points[i] = points[i] + results[i];
	}

	glEnd();

	glutSwapBuffers();

	glFlush();

}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 'p':

	{
		ofstream outputFile("..\\A2\\output\\output.ps");


		if (outputFile.is_open())
		{
			outputFile << "%!PS" << endl;
			outputFile << "%%PageBoundingBox: 0 0 " << width << " " << height << endl;

			//outputFile << points[0].x << " " << points[0].y << " moveto" << endl;

			for (int i = 0; i < circleSampling-3; i+=3){

				outputFile << points[i].x << " " << points[i].y << " moveto" << endl;
				outputFile << points[i+1].x << " " << points[i+1].y << endl;
				outputFile << points[i+2].x << " " << points[i+2].y << endl;
				outputFile << points[i+3].x << " " << points[i+3].y << endl;

				outputFile << "curveto" << endl;
				outputFile << "stroke" << endl;
			
			}

			outputFile << points[circleSampling - 3].x << " " << points[circleSampling - 3].y << " moveto" << endl;
			outputFile << points[circleSampling - 2].x << " " << points[circleSampling - 2].y << endl;
			outputFile << points[circleSampling - 1].x << " " << points[circleSampling - 1].y << endl;
			outputFile << points[0].x << " " << points[0].y << endl;

			outputFile << "curveto" << endl;
			outputFile << "stroke" << endl;



			outputFile.close();
		}

		break;
	}

	}
}



int _tmain(int argc, char* argv[])
{

	srand(time(NULL));

	points = new point[circleSampling];
	results = new point[circleSampling];

	//generate some points

	for (int i = 0; i < circleSampling; i++){
		points[i].x = (width / 2) + cos((360.0 /circleSampling) * i * PI / 180) * 100;
		points[i].y = (height / 2) + sin((360.0 / circleSampling) * i * PI / 180) * 100;

	}

	averageDistance = sqrt(pow((points[1].x - points[0].x), 2) + pow((points[1].y - points[0].y), 2));

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("A2");

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

	//point test = getPointOnSegment(point{ 250, 100 }, segment{ point{ 200, 200 }, point{ 100, 200 } });


	delete[] points;
	delete[] results;

	return 0;
}

