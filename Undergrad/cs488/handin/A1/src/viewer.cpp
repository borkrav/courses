#include "viewer.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>


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
    //std::cerr << "Unable to setup OpenGL Configuration!" << std::endl;
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
						 
						 
	yRot = 0;
	ySpeed = 0;
	m2=false;
	zRot = 0;
	zSpeed = 0;
	m1=false;
	xRot = 0;
	xSpeed = 0;
	m3=false;
	doubleBuffering = false;
	scaleToggle = false;
	scale = 1;
	gameSpeed = 1;
	multicoloured = false;
	
	g = new Game(10, 20);
	
	sigc::slot0<bool> slow_tick_slot = sigc::mem_fun(*this, &Viewer::slowGameTimeHandler);
	sigc::connection sGameConn = Glib::signal_timeout().connect(slow_tick_slot, 200);
	
	sigc::slot0<bool> med_tick_slot = sigc::mem_fun(*this, &Viewer::medGameTimeHandler);
	sigc::connection mGameConn = Glib::signal_timeout().connect(med_tick_slot, 100);
	
	sigc::slot0<bool> fast_tick_slot = sigc::mem_fun(*this, &Viewer::fastGameTimeHandler);
	sigc::connection fGameConn = Glib::signal_timeout().connect(fast_tick_slot, 50);
	
	sigc::slot0<bool> render_slot = sigc::mem_fun(*this, &Viewer::render);
	sigc::connection renderConn = Glib::signal_timeout().connect(render_slot, 16.66);
						 
}

//this is the callback to the gameConn timeout connection. Advances and redraws the game
bool Viewer::slowGameTimeHandler(){
	
	if (gameSpeed == 1){
		g->tick();
	}
	//invalidate();
	return true;
}

bool Viewer::medGameTimeHandler(){
	
	if (gameSpeed == 2){
		g->tick();
	}
	//invalidate();
	return true;
}

bool Viewer::fastGameTimeHandler(){
	
	if (gameSpeed == 3){
		g->tick();
	}
	//invalidate();
	return true;
}

//this function is called 60 times per second, it calls invalidate and re-draws the screen
bool Viewer::render(){

	yRot += ySpeed;	
	if(ySpeed > 1) ySpeed -=0.3;
	else if(ySpeed < -1) ySpeed +=0.3;
	else ySpeed=0;
	
	zRot += zSpeed;	
	if(zSpeed > 1) zSpeed -=0.3;
	else if(zSpeed < -1) zSpeed +=0.3;
	else zSpeed=0;
	
	xRot += xSpeed;	
	if(xSpeed > 1) xSpeed -=0.3;
	else if(xSpeed < -1) xSpeed +=0.3;
	else xSpeed=0;



	invalidate();
	return true;
}

void Viewer::setMode(Mode i){

	if (i == WIREFRAME) { //enable wireframe
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
	
	if (i == FACE) { //enable wireframe
		multicoloured = false;
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
	
	if (i == MULTICOLOURED) { //enable wireframe
		multicoloured = true;
	}
	
}

void Viewer::setSpeed(int i){

	gameSpeed = i;
	
}

void Viewer::newGame(){
	g->reset();
	//std::cout << "NEW GAME" << std::endl;


}

void Viewer::resetGame(){
	
	yRot = 0;
	ySpeed = 0;
	zRot = 0;
	zSpeed = 0;
	xRot = 0;
	xSpeed = 0;
	scale = 1;
	
	//std::cout << "RESET GAME" << std::endl;


}

void Viewer::toggleBuffering(){
	if (!doubleBuffering) {
		doubleBuffering = true;
	//	std::cout << "DB on" << std::endl;
	}
	else if (doubleBuffering) {
		doubleBuffering = false;	
	//	std::cout << "DB off" << std::endl;
	}
}


void Viewer::controls(int key){

	switch(key){
		case 1:
			g->moveLeft();
			break;
			
		case 2:
			g->rotateCCW();
			break;
			
		case 3:
			g->moveRight();
			break;
			
		case 4:
			g->rotateCW();
			break;
			
		case 5:
			g->drop();
			break;
			
	}


}

void Viewer::drawCube(float x, float y, float z){

	//this is the scale, used for debugging
	int i = 1;

	glBegin(GL_QUADS);
	//top face
	if (multicoloured) glColor3d(1, 1, 0);
	glVertex3d(x, y+i, z+i);
	glVertex3d(x, y+i, z);
	glVertex3d(x+i, y+i, z);
	glVertex3d(x+i, y+i, z+i); 
	
	//bottom face
	if (multicoloured) glColor3d(0, 0.5, 0.0);
	glVertex3d(x, y, z+i);
	glVertex3d(x, y, z);
	glVertex3d(x+i, y, z);
	glVertex3d(x+i, y, z+i);
	
	//left face
	if (multicoloured) glColor3d(0.0, 1.0, 1.0);
	glVertex3d(x, y, z+i);
	glVertex3d(x, y+i, z+i);
	glVertex3d(x, y+i, z);
	glVertex3d(x, y, z);

	//right face
	if (multicoloured) glColor3d(1.0, 0 , 1.0);
	glVertex3d(x+i, y, z+i);
	glVertex3d(x+i, y, z);
	glVertex3d(x+i, y+i, z);
	glVertex3d(x+i, y+i, z+i); 

	//front face
	if (multicoloured) glColor3d(0.0, 0.0, 0.5);
	glVertex3d(x, y+i, z+i);
	glVertex3d(x, y,z+i);
	glVertex3d(x+i, y, z+i);
	glVertex3d(x+i, y+i, z+i);

	//back face
	if (multicoloured) glColor3d(1, 0.0, 0);
	glVertex3d(x, y, z);
	glVertex3d(x+i, y, z);
	glVertex3d(x+i, y+i, z);
	glVertex3d(x, y+i, z);

	glEnd();

}



Viewer::~Viewer()
{
  // Nothing to do here right now.
}

void Viewer::invalidate()
{
  //Force a rerender
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

  // Just enable depth testing and set the background colour.
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.7, 0.7, 1.0, 0.0);

  gldrawable->gl_end();
}

bool Viewer::on_expose_event(GdkEventExpose* event)
{


  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable) return false;

  if (!gldrawable->gl_begin(get_gl_context()))
    return false;

  // Clear the screen

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



  if (!doubleBuffering) {
	glDrawBuffer(GL_FRONT);
  }

  else if (doubleBuffering) {
	glDrawBuffer(GL_BACK);
  }

  // Modify the current projection matrix so that we move the 
  // camera away from the origin.  We'll draw the game at the
  // origin, and we need to back up to see it.

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glTranslated(0.0, 0.0, -40.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	//zoom in and out with this
//	glTranslatef(0, 0, -100);


	//glRotatef(anglex, 1, 0, 0);
	
	
  // Not implemented: set up lighting (if necessary)

  // Not implemented: scale and rotate the scene
	
	glScalef(scale, scale, scale);

//	std::cout << xRot << std::endl;
//	std::cout << yRot << std::endl;
//	std::cout << zRot << std::endl;
	glRotatef(xRot, 1, 0, 0); 	
	glRotatef(yRot, 0, 1, 0); 
	glRotatef(zRot, 0, 0, 1); 



	
	//glScalef(1/2, 1/2, 1/2);


  // You'll be drawing unit cubes, so the game will have width
  // 10 and height 24 (game = 20, stripe = 4).  Let's translate
  // the game so that we can draw it starting at (0,0) but have
  // it appear centered in the window.
  glTranslated(-5.0, -12.0, 0.0);

  // Not implemented: actually draw the current game state.
  // Here's some test code that draws red triangles at the
  // corners of the game board.
  glColor3d(0, 0, 0);

	
  
	/*
  glBegin(GL_TRIANGLES);
	
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);

  glVertex3d(9.0, 0.0, 0.0);
  glVertex3d(10.0, 0.0, 0.0);
  glVertex3d(10.0, 1.0, 0.0);

  glVertex3d(0.0, 19.0, 0.0);
  glVertex3d(1.0, 20.0, 0.0);
  glVertex3d(0.0, 20.0, 0.0);

  glVertex3d(10.0, 19.0, 0.0);
  glVertex3d(10.0, 20.0, 0.0);
  glVertex3d(9.0, 20.0, 0.0);
  glEnd(); 
*/

	//Draws the U-shaped well
	for (int i = 0; i <20; i++){
		drawCube(-1,i,0.0);
		drawCube(10,i,0.0);
	}
	for (int i = -1; i < 11; i++){
		drawCube(i,-1,0.0);
	} 
	
	
	for (int i = 0; i<23; i++){
		for (int j = 0; j<10; j++){
			int cube = g->get(i,j);
			
			if (!multicoloured){
				switch(cube){
					case 0:
						glColor3d(1, 0, 0);
					break;
					case 1:
						glColor3d(1, 1, 0);
					break;
					case 2:
						glColor3d(0, 0.5, 0.0);
					break;
					case 3:
						glColor3d(0.0, 1.0, 1.0);
					break;
					case 4:
						glColor3d(0.0, 0 , 1.0);
					break;
					case 5:
						glColor3d(0.0, 0.0, 0.5);
					break;
					case 6:
						glColor3d(0.5, 0.0, 0.5);
					break;
				}
			}
			if (cube != -1) drawCube(j,i,0.0); 
			
		}
	}
	
	
  // We pushed a matrix onto the PROJECTION stack earlier, we 
  // need to pop it.

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  // Swap the contents of the front and back buffers so we see what we
  // just drew. This should only be done if double buffering is enabled.
  if(doubleBuffering) gldrawable->swap_buffers();
  else if(!doubleBuffering) glFlush();
	
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

bool Viewer::on_button_press_event(GdkEventButton* event)
{
 // std::cerr << "Stub: Button " << event->button << " pressed" << std::endl;
//	std::cout << event->state << event->button << std::endl;	
	//if (event->state == 16){
	//	scaleToggle = false;
	//}
	
			
	if (event->state == 16 && event->button == 2){
		scaleToggle = false;		
		m2=true;
		ySpeed = 0;
		prevx = x = event->x;
		//std::cout << "x: " << x << std::endl;
	}
	
	else if (event->state == 16 && event->button == 1){
		scaleToggle = false;	
		m1=true;
		xSpeed = 0;
		prevx = x = event->x;
		//std::cout << "x: " << x << std::endl;
	}
	
	else if (event->state == 16 && event->button == 3){
		scaleToggle = false;	
		m3=true;
		zSpeed = 0;
		prevx = x = event->x;
		//std::cout << "x: " << x << std::endl;
	}
	
	
	else if (event->state == 17
			 && (event->button == 2 || event->button == 1 || event->button ==  3)){
		scaleToggle = true;
	}

  return true;
}

bool Viewer::on_button_release_event(GdkEventButton* event)
{
 // std::cerr << "Stub: Button " << event->button << " released" << std::endl;
		
	if (event->button == 2 && !scaleToggle){
		m2=false; 
		float gravityValue = event->x - prevx;
		//std::cout << "Gravity: " << gravityValue << std::endl;

		if (gravityValue > 3){
			ySpeed = gravityValue/3;
		}
		else if (gravityValue < -3){
			ySpeed = gravityValue/3;
		}
		else {
			ySpeed = 0;
		}	
		//std::cout << "Speed: " << ySpeed << std::endl;	

	}
	
	else if (event->button == 1 && !scaleToggle){
		m1=false; 
		float gravityValue = event->x - prevx;
		//std::cout << "Gravity: " << gravityValue << std::endl;

		if (gravityValue > 3){
			xSpeed = gravityValue/3;
		}
		else if (gravityValue < -3){
			xSpeed = gravityValue/3;
		}
		else {
			xSpeed = 0;
		}	
		//std::cout << "Speed: " << ySpeed << std::endl;	

	}
	
	else if (event->button == 3 && !scaleToggle){
		m3=false; 
		float gravityValue = event->x - prevx;
		//std::cout << "Gravity: " << gravityValue << std::endl;

		if (gravityValue > 3){
			zSpeed = gravityValue/3;
		}
		else if (gravityValue < -3){
			zSpeed = gravityValue/3;
		}
		else {
			zSpeed = 0;
		}	
		//std::cout << "Speed: " << ySpeed << std::endl;	

	}
	

	
  return true;
}

bool Viewer::on_motion_notify_event(GdkEventMotion* event)
{
  //std::cerr << "Stub: Motion at " << event->x << ", " << event->y << std::endl;
	
	if (scaleToggle){
	
		prevx = x;
		x = event->x;
		if (prevx > x && scale > 0.25){
			scale -= 0.03;
		}
		else if (prevx < x && scale < 1){
			scale += 0.03;
		}
		
//		std::cout << scale << std::endl;
	}
	
	else if (m2 && !scaleToggle){
	 	prevx = x;
		x = event->x;
		if (prevx > x){
			yRot -= 2;
		}
		else {
			yRot += 2;
		}
		//std::cout << yRot << std::endl;
	//	invalidate();
	}
	
	else if (m1 && !scaleToggle){
	 	prevx = x;
		x = event->x;
		if (prevx > x){
			xRot -= 2;
		}
		else {
			xRot += 2;
		}
		//std::cout << yRot << std::endl;
	//	invalidate();
	}
	
	else if (m3 && !scaleToggle){
	 	prevx = x;
		x = event->x;
		if (prevx > x){
			zRot -= 2;
		}
		else {
			zRot += 2;
		}
		//std::cout << yRot << std::endl;
	//	invalidate();
	}
	
  return true;
}
