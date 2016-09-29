#include "viewer.hpp"
#include "algebra.hpp"
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "scene_lua.hpp"
#include "utilities.hpp"
#include <limits>

//TODO 
//		 ensure settings are correct DONE
//		 tweak lighing DONE
//		 tweak puppet appearance NOPE
//		 clean up code DONE
// 		 note down assumptions made

//assuming can lift code out of trackball project
//assuming immovable joint is defined with max=min
//assuming geometry is on leaf nodes




static Matrix mRotations    = {{1.0, 0.0, 0.0, 0.0},
	                             {0.0, 1.0, 0.0, 0.0},
	                             {0.0, 0.0, 1.0, 0.0},
                               {0.0, 0.0, 0.0, 1.0}};
static Matrix mTranslations = {{1.0, 0.0, 0.0, 0.0},
	                             {0.0, 1.0, 0.0, 0.0},
	                             {0.0, 0.0, 1.0, 0.0},
                               {0.0, 0.0, -20, 1.0}};
static Matrix rotOriginal    = {{1.0, 0.0, 0.0, 0.0},
	                             {0.0, 1.0, 0.0, 0.0},
	                             {0.0, 0.0, 1.0, 0.0},
                               {0.0, 0.0, 0.0, 1.0}};
static Matrix translOriginal = {{1.0, 0.0, 0.0, 0.0},
	                             {0.0, 1.0, 0.0, 0.0},
	                             {0.0, 0.0, 1.0, 0.0},
                               {0.0, 0.0, -20, 1.0}};

Matrix mIdentity     = {{1.0, 0.0, 0.0, 0.0},
                        {0.0, 1.0, 0.0, 0.0},
                        {0.0, 0.0, 1.0, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};



short sXReference, sYReference;
short sXCurrent, sYCurrent;

extern SceneNode* root;

Viewer::Viewer()
{
  Glib::RefPtr<Gdk::GL::Config> glconfig;

  // Ask for an OpenGL Setup with
  //  - red, green and blue component colour
  //  - a depth buffer to avoid things overlapping wrongly
  //  - double-buffered rendering to avoid tearing/flickering
  glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB |
                                     Gdk::GL::MODE_DEPTH |
                                     Gdk::GL::MODE_DOUBLE);
  if (glconfig == 0) {
    // If we can't get this configuration, die
    std::cerr << "Unable to setup OpenGL Configuration!" << std::endl;
    abort();
  }

  // Accept the configuration
  set_gl_capability(glconfig);

  // Register the fact that we want to receive these events
  add_events(Gdk::BUTTON1_MOTION_MASK    |
             Gdk::BUTTON2_MOTION_MASK    |
             Gdk::BUTTON3_MOTION_MASK    |
             Gdk::BUTTON_PRESS_MASK      | 
             Gdk::BUTTON_RELEASE_MASK    |
             Gdk::VISIBILITY_NOTIFY_MASK);

	//initialize my privates
	circle = zBuffer = backf = frontf = false;
	nCurrentDir = DIR_NONE;
	camera = true;
	picking = false;
	m2 = m3 = false;

	yCur = yPrev = xCur = xPrev = 0;
	root->saveState();

	status = 0;

}

Viewer::~Viewer()
{
  // Nothing to do here right now.
}

void resetPosition(){

	for (int i = 0; i<4; i++){
		for (int j = 0; j<4; j++){
			mTranslations[i][j] = translOriginal[i][j];
		}
	}
}

void resetOrientation(){

	for (int i = 0; i<4; i++){
		for (int j = 0; j<4; j++){
			mRotations[i][j] = rotOriginal[i][j];
		}
	}
}


void Viewer::setApp(App app){
	
	status = 0;

	switch(app){

		case R_POS:
			resetPosition();
			break;

		case R_ORI:
			resetOrientation();
			break;
		
		case R_JOINTS:
			root->resetState();
			break;

		case R_ALL:
			resetPosition();
			resetOrientation();
			root->resetState();
			break;
	}

	invalidate();
}

void Viewer::setMode(Mode mode){
	if (mode == POS_ORI){
		camera = true;
		picking = false;
	}
	else {
		camera = false;
		picking = true;
	}
		
}

void Viewer::setEdit(Edit edit){
	if (edit == UNDO){
		if(root->lastState()){
			status = 1;
			//std::cout << "You've hit the beginning of the stack" << std::endl;
		}		
		else status = 0;	
	}
	else if (edit == REDO){
		if(root->nextState()){
			status = 2;
			//std::cout << "You've hit the end of the stack" << std::endl;
		}			
		else status = 0;
	}
	invalidate();
}

void Viewer::setOption(Option option){
	switch (option){
		case CIRCLE:
			if (!circle) circle = true;
			else if (circle) circle = false;
			break;
		case Z_BUFFER:
			if (!zBuffer){
				zBuffer = true;
				glEnable(GL_DEPTH_TEST);
			}
			else if (zBuffer){
				zBuffer = false;
				glDisable(GL_DEPTH_TEST);
			}
			break;
		case BACKF:
			if (!backf){
				backf = true;
				glEnable(GL_CULL_FACE);
				if (frontf) glCullFace(GL_FRONT_AND_BACK);
				else glCullFace(GL_BACK);
			}
			else if (backf){
				backf = false;
				if (frontf) glCullFace(GL_FRONT);
				else glDisable(GL_CULL_FACE);
			}
			break;
		case FRONTF:
			if (!frontf){
				frontf = true;
				glEnable(GL_CULL_FACE);
				if (backf) glCullFace(GL_FRONT_AND_BACK);
				else glCullFace(GL_FRONT);
			}
			else if (frontf){
				frontf = false;
				if (backf) glCullFace(GL_BACK);
				else glDisable(GL_CULL_FACE);
			}
			break;
	}
	invalidate();
}


void Viewer::invalidate()
{
  // Force a rerender
  Gtk::Allocation allocation = get_allocation();
  get_window()->invalidate_rect( allocation, false);
}

void Viewer::on_realize()
{
  // Do some OpenGL setup.
  // First, let the base class do whatever it needs to
  Gtk::GL::DrawingArea::on_realize();
  
  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();
  
  if (!gldrawable)
    return;

  if (!gldrawable->gl_begin(get_gl_context()))
    return;

  glShadeModel(GL_SMOOTH);
  glClearColor( 0.4, 0.4, 0.4, 0.0 );
 // glEnable(GL_DEPTH_TEST);

  gldrawable->gl_end();
}

bool Viewer::on_expose_event(GdkEventExpose* event)
{
  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable) return false;

  if (!gldrawable->gl_begin(get_gl_context()))
    return false;


	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


  // Set up for perspective drawing 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, get_width(), get_height());
  gluPerspective(40.0, (GLfloat)get_width()/(GLfloat)get_height(), 0.1, 1000.0);

	//zoom out


  // change to model view for drawing
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	//glTranslated(0.0, 0.0, -20);

  // Clear framebuffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set up lighting

	
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lp[] = {-5, 10, 0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lp);

	glEnable(GL_NORMALIZE);

  // Draw stuff
	glPushMatrix();
	glLoadMatrixd((GLdouble *)mTranslations);
  glMultMatrixd((GLdouble *)mRotations);
	
	//renders scene
	root->walk_gl(0);
	//std::cout << std::endl;
	glPopMatrix();

	
  if (circle) draw_trackball_circle();

  // Swap the contents of the front and back buffers so we see what we
  // just drew. This should only be done if double buffering is enabled.
  gldrawable->swap_buffers();

  gldrawable->gl_end();

  return true;
}

bool Viewer::on_configure_event(GdkEventConfigure* event)
{
  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable) return false;
  
  if (!gldrawable->gl_begin(get_gl_context()))
    return false;

  // Set up perspective projection, using current size and aspect
  // ratio of display

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, event->width, event->height);
  gluPerspective(40.0, (GLfloat)event->width/(GLfloat)event->height, 0.1, 1000.0);

  // Reset to modelview matrix mode
  
  glMatrixMode(GL_MODELVIEW);

  gldrawable->gl_end();

  return true;
}

void Viewer::draw_trackball_circle()
{
  int current_width = get_width();
  int current_height = get_height();
  
  // Set up for orthogonal drawing to draw a circle on screen.
  // You'll want to make the rest of the function conditional on
  // whether or not we want to draw the circle this time around.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, current_width, current_height);
  glOrtho(0.0, (float)current_width, 
           0.0, (float)current_height, -0.1, 0.1);

  // change to model view for drawing
  glMatrixMode(GL_MODELVIEW);

  // Reset modelview matrix
  glLoadIdentity();

  // draw a circle for use with the trackball 
  glDisable(GL_LIGHTING);
  glEnable(GL_LINE_SMOOTH);
  glColor3f(1.0, 1.0, 1.0);
  double radius = current_width < current_height ? 
    (float)current_width * 0.25 : (float)current_height * 0.25;
  glTranslated((float)current_width * 0.5, (float)current_height * 0.5, 0);
  glBegin(GL_LINE_LOOP);
  for(size_t i=0; i<40; ++i) {
    double cosine = radius * cos(i*2*M_PI/40);
    double sine = radius * sin(i*2*M_PI/40);
    glVertex2f(cosine, sine);
  }
  glEnd();
  glColor3f(0.0, 0.0, 0.0);
  glDisable(GL_LINE_SMOOTH);
}

/*
 * Name      : void vToggleDir(int nDir)
 *
 * Parameters: int nDir - The direction.
 *
 * Returns   : void
 *
 * Purpose   : Toggles the direction in the direction vector on 
 *             and off.
 */
void Viewer::vToggleDir(int nDir) 
{
    nCurrentDir ^= nDir;
}


void processHits (GLint hits, GLuint buffer[])
{
	
	 unsigned int i, j;
   GLuint names, *ptr;

	 float z1 = std::numeric_limits<float>::infinity() ;
	 std::vector<int> name;

   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++) { 
      names = *ptr;
      ptr++;
			if (z1 > (float) *ptr/0x7fffffff){
					z1 = (float) *ptr/0x7fffffff; ptr++;
					ptr++;
					name.clear();				 
      		for (j = 0; j < names; j++) {     
						name.push_back(*ptr); ptr++;
      	}
			}

			else {
				for (j = 0; j < names+2; j++) ptr++;		
			}
   }
	
	//std::cout << "The node selected: "; 
	//for (int i = 0; i < name.size(); i++){
	//	std::cout << name[i] << " ";
	//}	
	//std::cout << std::endl;

	//-1 1 2 4 2 1 1//
/*
	std::vector<int> name;
	name.push_back(-1);
	name.push_back(1);
	name.push_back(2);
	name.push_back(4);
	name.push_back(2);
	name.push_back(1);
	name.push_back(1);

*/

	//-1 1 2 3 1 1//

	if (name.size() > 2) {
		//std::cout << "picking" << std::endl;
		name.erase(name.begin());
		root->pick(name);
	}

}


bool Viewer::on_button_press_event(GdkEventButton* event)
{
 // std::cerr << "Stub: Button " << event->button << " pressed" << std::endl;

	if (event->button == 1 && picking) {

		GLuint buffer[1000];
		GLint hits;
		GLint viewport[4];
		glSelectBuffer(1000, buffer);
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(-1);
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		gluPickMatrix(event->x,viewport[3]-(event->y),1,1,  viewport);
		gluPerspective(40.0, (GLfloat)viewport[2]/(GLfloat)viewport[3], 0.1, 1000.0);
		
		glMatrixMode(GL_MODELVIEW);
		//glPushMatrix();
		glLoadMatrixd((GLdouble *)mTranslations);
  	glMultMatrixd((GLdouble *)mRotations);
		root->walk_gl(0);	
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		hits = glRenderMode(GL_RENDER);


		processHits(hits, buffer);


		glMatrixMode(GL_MODELVIEW);

		glFlush();

	}

	if (event->button == 2 && picking) {
		m2 = true;
		yCur = event->y;
	}

	if (event->button == 3 && picking) {
		m3 = true;
		xCur = event->x;
	}

	if (camera){
		if (event->button == 1) vToggleDir(DIR_X);
		if (event->button == 2) vToggleDir(DIR_Y);
		if (event->button == 3) vToggleDir(DIR_Z);
	

		sXReference = event->x;
		sYReference = event->y;
	
	}

	invalidate();
  return true;
}

bool Viewer::on_button_release_event(GdkEventButton* event)
{
 // std::cerr << "Stub: Button " << event->button << " released" << std::endl;

	if (camera){
		if (event->button == 1) vToggleDir(DIR_X);
		if (event->button == 2) vToggleDir(DIR_Y);
		if (event->button == 3) vToggleDir(DIR_Z);

		sXReference = event->x;
  	sYReference = event->y;

		nCurrentDir = 0;

	}

	if (picking){
		if (event->button == 2){
			 m2 = false;
			 if (root->checkIfSelected('x')) root->saveState();
			 invalidate();

		}

		if (event->button == 3){
			 m3 = false;
			 if (root->checkIfSelected('y')) root->saveState();
			 invalidate();
		}
	}

  return true;
}

bool Viewer::on_motion_notify_event(GdkEventMotion* event)
{
  //std::cerr << "Stub: Motion at " << event->x << ", " << event->y << std::endl;



	if (m3 && picking) {

		bool left;

		xPrev = xCur;
		xCur = event->x;

		if (xCur < xPrev) left = true;

		
		if (left) root->animate(-2, 'y');
		else root->animate(2, 'y');
		invalidate();

		status = 0;
	}

	if (m2 && picking) {

		bool up;

		yPrev = yCur;
		yCur = event->y;

		if (yCur < yPrev) up = true;

		if (up) root->animate(-2, 'x');
		else root->animate(2, 'x');
		invalidate();

		status = 0;
	}

//	std::cout << nCurrentDir << std::endl;

	if (nCurrentDir && camera) {
               sXCurrent     = event->x;
               sYCurrent     = event->y;
               vPerformTransfo((float)sXReference, (float)sXCurrent,
                               (float)sYReference, (float)sYCurrent);
               sXReference   = sXCurrent;
               sYReference   = sYCurrent;
							invalidate();
	}

  return true;
}




void Viewer::vPerformTransfo(float fOldX, float fNewX, float fOldY, float fNewY) 
{
    float  fRotVecX, fRotVecY, fRotVecZ;
    Matrix mNewMat;
  
    /*
     * Track ball rotations are being used.
     */
    if (nCurrentDir & DIR_Z) {
        float fDiameter;
        int iCenterX, iCenterY;
        float fNewModX, fNewModY, fOldModX, fOldModY;
	
        /* vCalcRotVec expects new and old positions in relation to the center of the
         * trackball circle which is centered in the middle of the window and
         * half the smaller of nWinWidth or nWinHeight.
         */
        fDiameter = (get_width() < get_height()) ? get_width() * 0.5 : get_height() * 0.5;
        iCenterX = get_width() / 2;
        iCenterY = get_height() / 2;
        fOldModX = fOldX - iCenterX;
        fOldModY = fOldY - iCenterY;
        fNewModX = fNewX - iCenterX;
        fNewModY = fNewY - iCenterY;

        vCalcRotVec(fNewModX, fNewModY,
                        fOldModX, fOldModY,
                        fDiameter,
                        &fRotVecX, &fRotVecY, &fRotVecZ);
        /* Negate Y component since Y axis increases downwards
         * in screen space and upwards in OpenGL.
         */
        vAxisRotMatrix(fRotVecX, -fRotVecY, fRotVecZ, mNewMat);

        // Since all these matrices are meant to be loaded
        // into the OpenGL matrix stack, we need to transpose the
        // rotation matrix (since OpenGL wants rows stored
        // in columns)
        vTransposeMatrix(mNewMat);
        vRightMultiply(mRotations, mNewMat);
    }

    /*
     * Pan translations are being used.
     */
    if (nCurrentDir & DIR_X) {
        vTranslate((fNewX - fOldX) / ((float)SENS_PANX), 'x', mNewMat);
        vRightMultiply(mTranslations, mNewMat);
        vTranslate(-(fNewY - fOldY) / ((float)SENS_PANY), 'y', mNewMat);
        vRightMultiply(mTranslations, mNewMat);
    }
   
    /*
     * Zoom translations are being used.
     */
    if (nCurrentDir & DIR_Y) {
        vTranslate((fNewY - fOldY) / ((float)SENS_ZOOM), 'z', mNewMat);
        vRightMultiply(mTranslations, mNewMat);
    }
}
