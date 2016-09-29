// A3.cpp : Defines the entry point for the console application.
//

// A2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


using namespace std;


struct cell {
	bool tl;
	bool t;
	bool tr;
	bool r;
	bool br;
	bool b;
	bool bl;
	bool l;
	int type;
};



bool operator==(const cell &c1, const cell c2){
	return c1.tl == c2.tl && c1.t == c2.t && c1.tr == c2.tr && c1.r == c2.r && c1.br == c2.br && c1.b == c2.b && c1.bl == c2.bl && c1.l == c2.l;
}

enum direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	UL,
	UR,
	DL,
	DR
};



int width = 600;
int height = 600;

float posx = 0, posy=0;

int sx = 0, sy = 0;

int gridWidth, gridHeight, numBreakers;

vector <vector<cell>> cells;

direction last = LEFT;

bool turn = false;

bool started = false;


void move(direction dir){
	switch (dir)
	{
	case LEFT:
		posx -= 1;
		last = LEFT;
		break;
	case RIGHT:
		posx += 1;
		last = RIGHT;
		break;
	case UP:
		posy -= 1;
		last = UP;
		break;
	case DOWN:
		posy += 1;
		last = DOWN;
		break;
	case UL:
		posx -= 1;
		posy -= 1;
		last = UL;
		break;
	case UR:
		posx += 1;
		posy -= 1;
		last = UR;
		break;
	case DL:
		posx -= 1;
		posy += 1;
		last = DL;
		break;
	case DR:
		posx += 1;
		posy += 1;
		last = DR;
		break;
	default:
		break;
	}
}


void drawSquare(){
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);

	glVertex2f(-0.05, -0.05);
	glVertex2f(-0.05, 0.05);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, -0.05);
	glEnd();
}


//add more cases later
void updateCell(){

	if (cells[posx][posy] == cell{ 1, 1, 1, 0, 1, 0, 1, 1 }){

		cells[posx][posy].type = 22;


		if (last == LEFT) move(DOWN);
		else if (last == UP) move(RIGHT);


	}

	else if (cells[posx][posy] == cell{ 1, 1, 1, 0, 0, 0, 1, 0 }){

		cells[posx][posy].type = 11;


		if (last == UL) move(LEFT);
		else if (last == RIGHT) move(DR);



	}

	else if (cells[posx][posy] == cell{ 1, 0, 1, 1, 1, 0, 1, 1 }){

		cells[posx][posy].type = 1;


		if (last == DOWN) move(DOWN);
		else if (last == UP) move(UP);



	}

	else if (cells[posx][posy] == cell{ 1, 0, 1, 0, 0, 0, 1, 1 }){
		
		cells[posx][posy].type = 15;


		if (last == DOWN) move(DR);
		else if (last == UL) move(UP);


		
	}

	else if (cells[posx][posy] == cell{ 0, 0, 0, 0, 0, 0, 0, 0 }){

		if (last == DL) {
			cells[posx][posy].type = 4;

			move(DL);
		}

		else if (last == DR){
			cells[posx][posy].type = 3;

			move(DR);
		}

		else if (last == UL) {
			cells[posx][posy].type = 3;

			move(UL);

		}
		else if (last == UR){
			cells[posx][posy].type = 4;

			move(UR);
		}

	}

	else if (cells[posx][posy] == cell{ 0, 0, 1, 0, 0, 0, 0, 0 }){
		
		cells[posx][posy].type = 3;

		if (last == DR) move(DR);
		else if (last == UL) move(UL);


		
	}

	else if (cells[posx][posy] == cell{ 0, 0, 0, 0, 0, 0, 1, 0 }){

		cells[posx][posy].type = 3;

		if (last == DR) move(DR);
		else if (last == UL) move(UL);



	}

	else if (cells[posx][posy] == cell{ 1, 0, 0, 0, 1, 0, 0, 0 }){

		cells[posx][posy].type = 4;


		if (last == DL) move(DL);
		else if (last == UR) move(UR);



	}

	else if (cells[posx][posy] == cell{ 0, 0, 0, 0, 1, 1, 1, 0 }){

		if (last == DR) {
			cells[posx][posy].type = 13;

			move(RIGHT);
			turn = true;

		}
		else if (last == DL){
			cells[posx][posy].type = 14;

			move(LEFT);
			turn = true;

		}

		else if (last == RIGHT && turn == true){
			cells[posx][posy].type = 14;

			move(UR);
			turn = false;

		}

		else if (last == LEFT && turn == true){
			cells[posx][posy].type = 13;

			move(UL);
			turn = false;

		}
	}

	else if (cells[posx][posy] == cell{ 1, 1, 1, 0, 0, 0, 0, 0 }){

		if (last == UL) {
			cells[posx][posy].type = 11;

			move(LEFT);
			turn = true;

		}
		else if (last == UR){
			cells[posx][posy].type = 12;

			move(RIGHT);
			turn = true;

		}

		else if (last == RIGHT && turn == true){
			cells[posx][posy].type = 11;

			move(DR);
			turn = false;

		}

		else if (last == LEFT && turn == true){
			cells[posx][posy].type = 12;

			move(DL);
			turn = false;
		}
	}



	else if (cells[posx][posy] == cell{ 1, 0, 0, 0, 0, 0, 1, 1 }){

		if (last == DL) {
			cells[posx][posy].type = 17;

			move(DOWN);
			turn = true;

		}
		else if (last == UL){
			cells[posx][posy].type = 15;

			move(UP);
			turn = true;

		}

		else if (last == DOWN && turn == true){
			cells[posx][posy].type = 15;

			move(DR);
			turn = false;

		}

		else if (last == UP && turn == true){
			cells[posx][posy].type = 17;

			move(UR);
			turn = false;

		}
	}

	else if (cells[posx][posy] == cell{ 0, 0, 1, 1, 1, 0, 0, 0 }){

		if (last == UR) {
			cells[posx][posy].type = 16;

			move(UP);
			turn = true;

		}
		else if (last == DR){
			cells[posx][posy].type = 18;

			move(DOWN);
			turn = true;

		}

		else if (last == DOWN && turn == true){
			cells[posx][posy].type = 16;

			move(DL);
			turn = false;

		}

		else if (last == UP && turn == true){
			cells[posx][posy].type = 18;
			move(UL);
			turn = false;

		}
	}

	else if (cells[posx][posy] == cell{ 1, 1, 1, 1, 1, 0, 0, 0 }){
		cells[posx][posy].type = 21;

		if (last == RIGHT) move(DOWN);
		else if (last == UP) move(LEFT);

	}

	else if (cells[posx][posy] == cell{ 0, 0, 1, 1, 1, 1, 1, 0 }){
		cells[posx][posy].type = 24;

		if (last == DOWN) move(LEFT);
		else if (last == LEFT) move(UP);

	}

	else if (cells[posx][posy] == cell{ 1, 0, 0, 0, 1, 1, 1, 1 }){
		cells[posx][posy].type = 23;

		if (last == DOWN) move(RIGHT);
		else if (last == LEFT) move(UP);

	}

}




void renderScene(void) {

	//Sleep(100);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLUquadric *quad = gluNewQuadric();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 0);


	for (int i = 0; i < gridWidth; i++){
		for (int j = 0; j < gridWidth; j++){

			//Draws full grid

			//tl
			glPushMatrix();
			glTranslatef(i + 1, j + 1, 0);
			if (cells[i][j].tl == 1){
				drawSquare();
			}
			else {
				glColor3f(0, 0, 1);
				glutSolidSphere(0.05, 50, 50);
			}
			glPopMatrix();

			//t
			if (cells[i][j].t == 1){
				glBegin(GL_LINES);
				glColor3f(0, 0, 0);
				glVertex3f(i + 1, j + 1, 0);
				glVertex3f(i + 2, j + 1, 0);
				glEnd();
			}

			//tr
			glPushMatrix();
			glTranslatef(i + 2, j + 1, 0);
			if (cells[i][j].tr == 1){
				drawSquare();
			}
			else {
				glColor3f(0, 0, 1);
				glutSolidSphere(0.05, 50, 50);
			}
			glPopMatrix();

			//r
			if (cells[i][j].r == 1){
				glBegin(GL_LINES);
				glColor3f(0, 0, 0);
				glVertex3f(i + 2, j + 1, 0);
				glVertex3f(i + 2, j + 2, 0);
				glEnd();
			}

			//br
			glPushMatrix();
			glTranslatef(i + 2, j + 2, 0);
			if (cells[i][j].br == 1){
				drawSquare();
			}
			else {
				glColor3f(0, 0, 1);
				glutSolidSphere(0.05, 50, 50);
			}
			glPopMatrix();

			//b
			if (cells[i][j].b == 1){
				glBegin(GL_LINES);
				glColor3f(0, 0, 0);
				glVertex3f(i + 1, j + 2, 0);
				glVertex3f(i + 2, j + 2, 0);
				glEnd();
			}

			//bl
			glPushMatrix();
			glTranslatef(i + 1, j + 2, 0);
			if (cells[i][j].bl == 1){
				drawSquare();
			}
			else {
				glColor3f(0, 0, 1);
				glutSolidSphere(0.05, 50, 50);
			}
			glPopMatrix();

			//l
			if (cells[i][j].l == 1){
				glBegin(GL_LINES);
				glColor3f(0, 0, 0);
				glVertex3f(i + 1, j + 1, 0);
				glVertex3f(i + 1, j + 2, 0);
				glEnd();
			}

		}
	}

	for (int i = 0; i < gridWidth; i++){
		for (int j = 0; j < gridHeight; j++){
			cout << "	" << cells[j][i].type << " ";
		}
		cout << endl;
	}

	cout << endl;


	if (!started || posx != sx || posy != sy) updateCell();
	started = true;
	glPushMatrix();


	glTranslatef(posx+1.5, posy+1.5, 0);

	glColor3f(1, 0, 0);

	//glBegin(GL_LINES);
	//glVertex3f(posx + 1.5, posy + 1.5, 0);


	//glVertex3f(posx + 1.5, posy + 1.5, 0);
	//glEnd();

	glutSolidSphere(0.05, 50, 50);

	glPopMatrix();

	
	glutSwapBuffers();

	glFlush();

}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 'p':

		{
			ofstream outputFile("..\\A3\\output\\output.html");

			if (outputFile.is_open())
			{

				//standard 10x10

				//13x13 need to be scaled to same size

				string path = "C:\\Users\\Boris\\Documents\\GitHub\\masters\\CS791\\A3\\Tiles\\";

				int width = 100;
				int height = 100;


				outputFile << "<!DOCTYPE html>" << endl;
				outputFile << "<html>" << endl;
				outputFile << "<body>" << endl;


				for (int i = 0; i < gridWidth; i++){
					for (int j = 0; j < gridHeight; j++){

						int cell = cells[j][i].type;


						outputFile << " <object style=\"position:fixed; top: " << i * 100 << "px; left: " << j * 100 << "px; \" data='" << path << cell << ".svg' width=\""<<width<<"\" height=\""<<height<<"\" type=\"image/svg+xml\"></object>" << endl;

						

					}
					cout << endl;
				}

				//for the criss cross

				//
				// w x
				// y z
				//
				// where all are pieces with diagonals
				// place tile at that offset


				outputFile << "</body>" << endl;
				outputFile << "</html>" << endl;


			}

			outputFile.close();

		}

		break;
	

	}
}



bool checkBounds(int i, int j){

	if (i >= 0 && i < gridWidth && j >= 0 && j < gridHeight){
		return true;
	}
	else return false;

}


int _tmain(int argc, char* argv[])
{
	

	ifstream inputFile("..\\A3\\input\\test1.txt");

	string line;

	int a, b, c;

	getline(inputFile, line);
	istringstream iss(line);
	iss >> a >> b >> c;
	gridWidth = a;
	gridHeight = b;
	numBreakers = c;



	for (int i = 0; i < gridWidth; i++){
		vector<cell> temp;
		for (int j = 0; j < gridHeight; j++){
			temp.push_back(cell{ 0, 0, 0, 0, 0, 0, 0, 0 });
		}
		cells.push_back(temp);

	}



	while (getline(inputFile, line))
	{
		istringstream iss(line);
		string c;

		iss >> a >> b >> c;

		//offset for the drawing by 1

		if (c == "S"){

			//x-1 and x

			if (checkBounds(a, b - 1)){
				cells[a][b-1].bl = 1;
			}

			if (checkBounds(a, b)){
				cells[a][b].l = 1;
				cells[a][b].tl = 1;
				cells[a][b].bl = 1;
			}

			if (checkBounds(a, b + 1)){
				cells[a][b + 1].l = 1;
				cells[a][b + 1].tl = 1;
				cells[a][b + 1].bl = 1;
			}

			if (checkBounds(a, b + 2)){
				cells[a][b + 2].tl = 1;
			}

			if (checkBounds(a-1, b - 1)){
				cells[a-1][b-1].br = 1;
			}

			if (checkBounds(a-1, b)){
				cells[a-1][b].r= 1;
				cells[a-1][b].tr = 1;
				cells[a-1][b].br = 1;
			}

			if (checkBounds(a - 1, b + 1)){
				cells[a - 1][b + 1].r = 1;
				cells[a - 1][b + 1].tr = 1;
				cells[a - 1][b + 1].br = 1;
			}

			if (checkBounds(a - 1, b + 2)){
				cells[a - 1][b + 2].tr = 1;
			}

		}

		if (c == "E"){

			//cell to the left
			if (checkBounds(a - 1, b)){
				cells[a - 1][b].tr = 1;
			}

			//cell under line
			if (checkBounds(a, b)){
				cells[a][b].t = 1;
				cells[a][b].tr = 1;
				cells[a][b].tl = 1;
			}

			//cell under line
			if (checkBounds(a + 1, b)){
				cells[a+1][b].t = 1;
				cells[a+1][b].tr = 1;
				cells[a+1][b].tl = 1;
			}

			//cell to the right
			if (checkBounds(a + 2, b)){
				cells[a + 2][b].tl = 1;
			}




			//cell to the left
			if (checkBounds(a - 1, b-1)){
				cells[a - 1][b - 1].br = 1;
			}


			//cell above line
			if (checkBounds(a, b - 1)){
				cells[a][b - 1].b = 1;
				cells[a][b - 1].br = 1;
				cells[a][b - 1].bl = 1;
			}

			//cell above line
			if (checkBounds(a + 1, b - 1)){
				cells[a + 1][b - 1].b = 1;
				cells[a + 1][b - 1].br = 1;
				cells[a + 1][b - 1].bl = 1;
			}

			//cell to the right
			if (checkBounds(a + 2, b - 1)){
				cells[a + 2][b - 1].bl = 1;
			}

		}



	}


	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("A3");

	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, gridWidth + 2, gridHeight + 2, 0, 0.f, 1.f);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// register callbacks
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}

