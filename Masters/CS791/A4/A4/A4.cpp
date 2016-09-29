// A4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tile.h"

using namespace std;

bool drawOriginal = 0;
bool drawOne = 0;
bool wireframe = 0;

bool deform = 1;
int period = 7;

int width = 1650;
int height = 1080;
int zoom = 50;

int lowX = -40;
int highX = 40;
int lowY = -100;
int highY = 100;

#define PI 3.14159265358979323846

#define LINECOLOR glColor3f(0, 0, 0);
#define STRIPCOLOR glColor3f(102.0/255.0, 178.0/255.0, 1);
#define BACKGROUNDCOLOR glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
#define PATTERNCOLOR glColor3f(102.0/255, 0, 0);
#define POLYGONCOLOR glColor3f(0, 51.0/255.0, 102.0/255.0);




vector<tiling*> tilings;

//avoid angles that don't find intersection - 45, 30, 60
float angle = 85*(PI/180);



//convinience functions
float getLength(vertex a, vertex b){
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

vertex getMidpoint(vertex a, vertex b){
	return vertex{ (a.x + b.x) / 2, (a.y + b.y) / 2 };
}

bool sortIntersection(intersection c1, intersection c2){
	return c1.distance < c2.distance;
}

vertex getIntersect(line a, line b){

	float x1 = a.midpoint.x;
	float y1 = a.midpoint.y;

	float x2 = a.controlpoint.x;
	float y2 = a.controlpoint.y;

	float x3 = b.midpoint.x;
	float y3 = b.midpoint.y;

	float x4 = b.controlpoint.x;
	float y4 = b.controlpoint.y;
			

	float x = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
	float y = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

	return vertex{ x, y };

}

double getAngle(vertex p1, vertex p2){

	double dtheta, theta1, theta2;

	theta1 = atan2(p1.y, p1.x);
	theta2 = atan2(p2.y, p2.x);
	dtheta = theta2 - theta1;
	while (dtheta > PI)
		dtheta -= 2 * PI;
	while (dtheta < -PI)
		dtheta += 2 * PI;

	return(dtheta);

}

//Apperantly, this is the slowest way to determine if a point is inside a polygon
bool pointInPolygon(vertex point, vector<vertex> polygon){

	double angle = 0;
	vertex p1, p2;


	for (int i = 0; i < polygon.size(); i++){
		p1.x = polygon[i].x - point.x;
		p1.y = polygon[i].y - point.y;
		p2.x = polygon[(i + 1) % polygon.size()].x - point.x;
		p2.y = polygon[(i + 1) % polygon.size()].y - point.y;
		angle += getAngle(p1, p2);
	}

	if (abs(angle) < PI)
		return(FALSE);
	else
		return(TRUE);


}


vector<line>generateLines(vector<vertex> vertices){
	

	vector<line> lines;

	//coordinates relative to -10,10 grid that's being rendered

	if (deform){


		array<GLfloat, 16> modelview;

		glGetFloatv(GL_MODELVIEW_MATRIX, modelview.data());
		float x = vertices[0].x * modelview[0] + vertices[0].y * modelview[4] + modelview[12];
		float y = vertices[0].x * modelview[1] + vertices[0].y * modelview[5] + modelview[13];


		angle = (60 + 25 * sin((x) / period))*PI / 180;
	}
	//range: 35 degrees to 85 degrees

	// x + y = 85
	// x - y = 35
	// x = 35 + y
	//35 + 2y = 85
	//y = 25
	// x = 60


	//cout << "x: " << x << " y: " << y << endl;;


	for (int i = 0; i < vertices.size(); i++){

		vertex mid = getMidpoint(vertices[i % (vertices.size())], vertices[(i + 1) % (vertices.size())]);

		float total = 0;

		float px1 = vertices[i % (vertices.size())].x;
		float py1 = vertices[i % (vertices.size())].y;
		float px2 = vertices[(i + 1) % (vertices.size())].x;
		float py2 = vertices[(i + 1) % (vertices.size())].y;

		if (px2 > px1)
			total = atan((py2 - py1) / (px2 - px1)) + angle;
		else if (px2 == px1)
			if (px1 > 0){
				total = PI / 2 + angle;
			}
			else
				total = PI + PI / 2 + angle;
		else
			total = PI + atan((py2 - py1) / (px2 - px1)) + angle;

		vertex leftControlPoint = { cos(total - angle + PI - angle) + mid.x, sin(total - angle + PI - angle) + mid.y };
		vertex rightControlPoint = { cos(total) + mid.x, sin(total) + mid.y };


		vertex rightOfMid = getMidpoint(mid, vertices[(i + 1) % (vertices.size())]);
		vertex leftOfMid = getMidpoint(vertices[i % (vertices.size())], mid);
		rightOfMid = getMidpoint(mid, rightOfMid);
		leftOfMid = getMidpoint(leftOfMid, mid);
		

		vertex leftOfMidControlPoint = { cos(total - angle + PI - angle) + leftOfMid.x, sin(total - angle + PI - angle) + leftOfMid.y };
		vertex rightOfMidControlPoint = { cos(total) + rightOfMid.x, sin(total) + rightOfMid.y };

		lines.push_back(line{ leftOfMid, leftOfMidControlPoint });

		lines.push_back(line{ mid, leftControlPoint });
		lines.push_back(line{ mid, rightControlPoint });
		lines.push_back(line{ rightOfMid, rightOfMidControlPoint });

		/*
		glBegin(GL_LINES);
		glVertex2d(mid.x,mid.y);
		glVertex2d(p1.x, p1.y);
		glEnd();


		glBegin(GL_LINES);
		glVertex2d(mid.x, mid.y);
		glVertex2d(p2.x, p2.y);
		glEnd();
		*/

	}
	return lines;

}

void drawOriginalTiles(vector<vertex> vertices){

	PATTERNCOLOR

	glBegin(GL_POLYGON);
	for (int i = 0; i < vertices.size(); i++){
		glVertex2d(vertices[i].x, vertices[i].y);
	}
	glEnd();
}

void drawIntersection(intersection intersect){


	STRIPCOLOR

	glBegin(GL_POLYGON);


	glVertex2d(intersect.leftInside.midpoint.x, intersect.leftInside.midpoint.y);
	glVertex2d(intersect.bottomIntersection.x, intersect.bottomIntersection.y);
	glVertex2d(intersect.topIntersection.x, intersect.topIntersection.y);
	glVertex2d(intersect.leftOutside.midpoint.x, intersect.leftOutside.midpoint.y);

	glEnd();


	glBegin(GL_POLYGON);

	glVertex2d(intersect.rightOutside.midpoint.x, intersect.rightOutside.midpoint.y);
	glVertex2d(intersect.topIntersection.x, intersect.topIntersection.y);
	glVertex2d(intersect.bottomIntersection.x, intersect.bottomIntersection.y);
	glVertex2d(intersect.rightInside.midpoint.x, intersect.rightInside.midpoint.y);

	LINECOLOR

	glEnd();

	glBegin(GL_LINE_STRIP);

	glVertex2d(intersect.leftOutside.midpoint.x, intersect.leftOutside.midpoint.y);
	glVertex2d(intersect.topIntersection.x, intersect.topIntersection.y);
	glVertex2d(intersect.rightOutside.midpoint.x, intersect.rightOutside.midpoint.y);

	glEnd();

	glBegin(GL_LINE_STRIP);

	glVertex2d(intersect.leftInside.midpoint.x, intersect.leftInside.midpoint.y);
	glVertex2d(intersect.bottomIntersection.x, intersect.bottomIntersection.y);
	glVertex2d(intersect.rightInside.midpoint.x, intersect.rightInside.midpoint.y);

	glEnd();

}

void drawInternalPolygon(vector<vertex> poly){

	// B T B T B T B T B T 

	//Tessalate ouside rim

	POLYGONCOLOR

	for (int i = 0; i < poly.size(); i+=2){

		glBegin(GL_TRIANGLES);

		glVertex2d(poly[(i + 1) % poly.size()].x, poly[(i + 1) % poly.size()].y);
		glVertex2d(poly[(i + 2) % poly.size()].x, poly[(i + 2) % poly.size()].y);
		glVertex2d(poly[(i + 3) % poly.size()].x, poly[(i + 3) % poly.size()].y);

		glEnd();

	}

	//fill in inside

	glBegin(GL_POLYGON);

	for (int i = 0; i < poly.size(); i += 2){


		glVertex2d(poly[(i + 1) % poly.size()].x, poly[(i + 1) % poly.size()].y);


	}
	glEnd();

}






void drawTiling(tiling *tlng, float x, float y){

	for (int k = 0; k <= tlng->_translations.size(); k++){

		//glPushMatrix();
		//glTranslatef(test->_translations[k].x, test->_translations[k].y, 0);


		for (int i = 0; i < tlng->_tiles.size(); i++){

			for (int j = 0; j < tlng->_tiles[i]->_transforms.size(); j++){

				//glPushMatrix();
				glLoadIdentity();

				transfrm *t = &(tlng->_tiles[i]->_transforms[j]);

				//a b 0 c
				//d e 0 f
				//0 0 1 0
				//0 0 0 1

				float mat[16] = { t->a, t->d, 0, 0, t->b, t->e, 0, 0, 0, 0, 1, 0, t->c+x, t->f+y, 0, 1 };

				//glTranslatef(0, 0, 0);

				if (k != tlng->_translations.size())
					glTranslatef(tlng->_translations[k].x, tlng->_translations[k].y, 0);

				glMultMatrixf(mat);

				//glTranslatef(x, y, 0);

				vector<vertex> vertices;
				vector<line> lines;
				vector<vertex> internalPolygon;


				if (tlng->_tiles[i]->_type == "regular"){

					//generate vertices



					int sides = tlng->_tiles[i]->_sides;

					float radius = 1 / cos(PI / sides);

					vertices.push_back(vertex{ 1, tan(PI / sides)});

					for (int i = 1; i < sides; i++){

						float x = cos(PI / sides + 2 * PI / sides * i) * radius;
						float y = sin(PI / sides + 2 * PI / sides * i) * radius;

						vertices.push_back(vertex{ x, y });

					}

					//draw back tiling

					if (drawOriginal){
						drawOriginalTiles(vertices);
					}
					
					//generate lines
					lines = generateLines(vertices);
					

					// \ \ / / \ \ / /
					// 0 1 2 3 4 5 6 7


					//render strips
					for (int i = 0; i < lines.size(); i+=4){

						intersection intersect = intersection{ 
							lines[(i + 2) % lines.size()],
							lines[(i + 3) % lines.size()],
							lines[(i + 4) % lines.size()],
							lines[(i + 5) % lines.size()],
							getIntersect(lines[(i + 2) % lines.size()], lines[(i + 5) % lines.size()]),
							getIntersect(lines[(i + 3) % lines.size()], lines[(i + 4) % lines.size()]) };

						drawIntersection(intersect);

						internalPolygon.push_back(intersect.leftOutside.midpoint);
						internalPolygon.push_back(intersect.topIntersection);



						
					}

					drawInternalPolygon(internalPolygon);
					
				}


				else if (tlng->_tiles[i]->_type == "polygon"){

					for (int j = 0; j < tlng->_tiles[i]->_vertices.size(); j++){
						vertices.push_back(vertex{ tlng->_tiles[i]->_vertices[j].x, tlng->_tiles[i]->_vertices[j].y });

					}

					// draw back tiling

					if (drawOriginal){
						drawOriginalTiles(vertices);
					}

					//generate lines
					lines = generateLines(vertices);

					glColor3f(1, 0, 0);


					// \ \ / / \ \ / / \ \ / / \ \ / / 
					// 0 1 2 3 4 5 6 7 8 9 
					//	   | + + | | + + |  

					//generate possibilities
					vector<intersection> possibilities;

					for (int i = 0; i < lines.size(); i+=4){

						line leftOusideLine = lines[(i + 2) % lines.size()];
						line leftInsideLine = lines[(i + 3) % lines.size()];
						vertex topIntersection;
						vertex bottomIntersection;
						line rightOutsideLine;
						line rightInsideLine;

						for (int j = 0; j < lines.size(); j += 4){

							rightOutsideLine = lines[(j + 5) % lines.size()];
							rightInsideLine = lines[(j + 4) % lines.size()];


							topIntersection = getIntersect(leftOusideLine, rightOutsideLine);
							bottomIntersection = getIntersect(leftInsideLine, rightInsideLine);


							float totalDistance = getLength(leftOusideLine.midpoint, topIntersection) + getLength(rightOutsideLine.midpoint, topIntersection) + getLength(leftInsideLine.midpoint, bottomIntersection) + getLength(rightInsideLine.midpoint, bottomIntersection);

							if (totalDistance > 0.000001 && pointInPolygon(topIntersection, vertices) && pointInPolygon(bottomIntersection, vertices))
								possibilities.push_back(intersection{leftOusideLine, leftInsideLine, rightInsideLine, rightOutsideLine, topIntersection, bottomIntersection, totalDistance});

						}
					}

					
					std::sort(possibilities.begin(), possibilities.end(), sortIntersection);

					bool newPoly = true;
					line leftOutsideLine;
					line rightOutsideLine;
					intersection intersect;

					while (possibilities.size() != 0){


						if (newPoly){
							leftOutsideLine = possibilities[0].leftOutside;
							rightOutsideLine = possibilities[0].rightOutside;
							intersect = possibilities[0];
							newPoly = false;
						}

						//draw strips
						drawIntersection(intersect);
						internalPolygon.push_back(leftOutsideLine.midpoint);
						internalPolygon.push_back(intersect.topIntersection);


						vector <intersection>::iterator deleteIterator = possibilities.begin();
						while (deleteIterator != possibilities.end()) {
							if (deleteIterator->leftOutside == leftOutsideLine || deleteIterator->rightOutside == leftOutsideLine || deleteIterator->leftOutside == rightOutsideLine || deleteIterator->rightOutside == rightOutsideLine){
								deleteIterator = possibilities.erase(deleteIterator);
							}
							else{
								deleteIterator++;
							}
						}

						bool found = false;
						for (int i = 0; i < possibilities.size(); i++){
							if (possibilities[i].leftOutside.midpoint == rightOutsideLine.midpoint){
								leftOutsideLine = possibilities[i].leftOutside;
								rightOutsideLine = possibilities[i].rightOutside;
								intersect = possibilities[i];
								found = true;
								break;
							}
						}

						if (!found){
							drawInternalPolygon(internalPolygon);
							internalPolygon.clear();
							newPoly = true;
						}




					}



				}

			



			}

		}


	}


}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLUquadric *quad = gluNewQuadric();

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 0, 0);


	tiling *tlng = tilings[11];

	if (drawOne)
		drawTiling(tlng, 0, 0);

	
	//3.12.12 = 6
	//4.6.12 = 8
	//4.8.8 = 9
	//6.6.6 = 10
	//10 RD = 11
	//8 RD = 15
	
	
	if (tlng->_type == "3.12.12" && !drawOne){

		for (float i = lowX; i < highX; i += 2){
			for (float j = lowY; j < highY; j += 3.46){
				drawTiling(tlng, i, j);
			}
		}
	}

	if (tlng->_type == "4.6.12" && !drawOne){

		for (float i = lowX; i < highX; i += 4.38){
			for (float j = lowY; j < highY; j += 3.80 * 2){
				drawTiling(tlng, i, j);
			}
			for (float j = lowY; j < highY; j += 3.80 * 2){
				drawTiling(tlng, i+2.18, j+ 3.80);
			}
		}
	}
	
	if (tlng->_type == "4.8.8" && !drawOne){

		for (float i = lowX; i < highX; i += 4.24){
			for (float j = lowY; j < highY; j += 2.83){
				drawTiling(tlng, i, j+i/3.0);
			}
		}
	}

	
	if (tlng->_type == "6.6.6" && !drawOne){

		for (float i = lowX; i < highX; i += 2){
			for (float j = lowY; j < highY; j += 3.46){
				drawTiling(tlng, i, j);
			}
		}
	}
	
	
	if (tlng->_type == "10 RD" && !drawOne){

		for (float i = lowX; i < highX; i += 5.99){
			drawTiling(tlng, i+0, 0);
			drawTiling(tlng, i+2.61, 1.9);
			drawTiling(tlng, i+3.374, -1.9);
			drawTiling(tlng, i+0.76, -3.8);
			drawTiling(tlng, i+-0.762, 3.8);
			drawTiling(tlng, i+1.84, 5.7);
			drawTiling(tlng, i+4.135, -5.7);
			drawTiling(tlng, i+1.54, -7.6);
		}
		
	}


	if (tlng->_type == "8 RD" && !drawOne){

		for (float i = lowX; i < highX; i += 2){
			for (float j = lowY; j < highY; j += 2){

				drawTiling(tlng, i, j);
			}
		}
	}
	
	
	
	glutSwapBuffers();

	glFlush();

}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 'p':

	{
		cout << "PRINTING" << endl;

		FILE *fp;
		fopen_s(&fp, "..\\A4\\output\\output.eps", "wb");
		GLint buffsize = 0, state = GL2PS_OVERFLOW;
		GLint viewport[4];

		glGetIntegerv(GL_VIEWPORT, viewport);

		while (state == GL2PS_OVERFLOW){
			buffsize += 1024 * 1024;
			gl2psBeginPage("MyTitle", "MySoftware", viewport,
				GL2PS_EPS, GL2PS_BSP_SORT, GL2PS_SILENT |
				GL2PS_SIMPLE_LINE_OFFSET | GL2PS_NO_BLENDING |
				GL2PS_OCCLUSION_CULL | GL2PS_BEST_ROOT,
				GL_RGBA, 0, NULL, 0, 0, 0, buffsize,
				fp, "MyFile");
			renderScene();
			state = gl2psEndPage();
		}

		fclose(fp);
		cout << "DONE" << endl;



		break;
	}

	}
}



void parseXML(string name){

	tinyxml2::XMLDocument doc;
	string fileName = "..\\A4\\input\\" + name + ".tl";
	doc.LoadFile(fileName.c_str());

	tinyxml2::XMLElement* tilingData = doc.FirstChildElement()->FirstChildElement();

	while (tilingData != NULL){

		cout << "READING: " << tilingData->FirstAttribute()->Value() << endl;

		tiling* tl = new tiling(tilingData->FirstAttribute()->Value());

		tinyxml2::XMLElement* transData = tilingData->FirstChildElement()->FirstChildElement();

		while (transData != NULL) {
			tl->addTranslation(translation{ atof(transData->Attribute("x")), atof(transData->Attribute("y")) });
			transData = transData->NextSiblingElement();
		}


		tinyxml2::XMLElement*  tileData = tilingData->FirstChildElement()->NextSiblingElement();

		while (tileData != NULL){

			tinyxml2::XMLElement* shapeData = tileData->FirstChildElement();

			tile *t = new tile(shapeData->Attribute("type"));


			if (t->_type == "polygon"){
				tinyxml2::XMLElement* polygonData = shapeData->FirstChildElement();

				while (polygonData != NULL){

					float contact;

					if (polygonData->Attribute("contact") != NULL){
						contact = atof(polygonData->Attribute("contact"));
					}
					else contact = 0;

					t->addVertex(vertex{ atof(polygonData->Attribute("x")), atof(polygonData->Attribute("y")), contact });

					polygonData = polygonData->NextSiblingElement();
				}

			}

			else{
				t->_sides = atoi(shapeData->Attribute("sides"));
			}



			shapeData = shapeData->NextSiblingElement();

			while (shapeData != NULL){

				t->addTransform(transfrm{ atof(shapeData->Attribute("a")),
											atof(shapeData->Attribute("b")),
											atof(shapeData->Attribute("c")),
											atof(shapeData->Attribute("d")),
											atof(shapeData->Attribute("e")),
											atof(shapeData->Attribute("f")) });


				shapeData = shapeData->NextSiblingElement();

			}

			tl->addTile(t);


			tinyxml2::XMLElement*transformData = tileData->NextSiblingElement();





			tileData = tileData->NextSiblingElement();


		}




		tilings.push_back(tl);


		tilingData = tilingData->NextSiblingElement();
	}


	


}



int _tmain(int argc, char* argv[])
{

	parseXML("archimedeans");
	parseXML("hanbury");


	
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("A4");

	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / zoom, width / zoom, -height / zoom, height / zoom, 0.f, 100.f);


	BACKGROUNDCOLOR

	// register callbacks
	//glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}


