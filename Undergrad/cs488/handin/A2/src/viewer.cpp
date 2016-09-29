#include "viewer.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "draw.hpp"

bool ORTHO = false;


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

	initializeLines();
	m1 = m2 = m3 = false;
	interactionMode = M_ROTATE;
}

Viewer::~Viewer()
{
  // Nothing to do here right now.
}


void Viewer::setMode(Mode mode){

	interactionMode = mode;

}


//this initializes all the lines in our scene
void Viewer::initializeLines(){

	//the cube lines
	modelPoints.push_back((line){Point3D(-1,1,1), Point3D(-1,-1,1)}); //0
  modelPoints.push_back((line){Point3D(-1,-1,1), Point3D(1,-1,1)}); //1
  modelPoints.push_back((line){Point3D(1,-1,1),  Point3D(1,1,1)}); //2
  modelPoints.push_back((line){Point3D(1,1,1),  Point3D(-1,1,1)}); //3
	modelPoints.push_back((line){Point3D(-1,1,-1), Point3D(1,1,-1)}); //4
	modelPoints.push_back((line){Point3D(1,1,-1), Point3D(1,-1,-1)}); //5
	modelPoints.push_back((line){Point3D(1,-1,-1), Point3D(-1,-1,-1)}); //6
	modelPoints.push_back((line){Point3D(-1,-1,-1), Point3D(-1,1,-1)}); //7

	modelPoints.push_back((line){Point3D(-1,1,1), Point3D(-1,1,-1)}); //8
  modelPoints.push_back((line){Point3D(-1,-1,1), Point3D(-1,-1,-1)}); //9
  modelPoints.push_back((line){Point3D(1,-1,1),  Point3D(1,-1,-1)}); //10
  modelPoints.push_back((line){Point3D(1,1,1),  Point3D(1,1,-1)}); //11

	//the model axis lines
  modelPoints.push_back((line){Point3D(0.5,0,0), Point3D(0,0,0)});
  modelPoints.push_back((line){Point3D(0,0.5,0), Point3D(0,0,0)});
  modelPoints.push_back((line){Point3D(0,0,0.5), Point3D(0,0,0)});
  
	//the world axis lines
  worldAxis.push_back((line){Point3D(0.5,0,0), Point3D(0,0,0)});
  worldAxis.push_back((line){Point3D(0,0.5,0), Point3D(0,0,0)});
  worldAxis.push_back((line){Point3D(0,0,0.5), Point3D(0,0,0)});

	for (int i = 0; i < modelPoints.size(); i++){
		orthoLines.push_back((orthoLine){Point2D(0,0), Point2D(0,0)});
	}
	for (int j = 0; j < worldAxis.size(); j++){
		orthoLines.push_back((orthoLine){Point2D(0,0), Point2D(0,0)});
	}
	
	originalViewport = true;

}


void Viewer::orthoProject(std::vector <line> input){

	int current = 0;
	for (int i = 0; i < input.size(); i++){

		orthoLines[i] = (orthoLine){
											Point2D(input[i].origin[0], input[i].origin[1]), 												Point2D(input[i].endpoint[0],input[i].endpoint[1])
										};
		
		current = i;	
	}

	for (int i = 1; i < worldAxis.size(); i++){

		orthoLines[current + i] = (orthoLine){
					 											Point2D(worldAxis[i].origin[0], 
																				worldAxis[i].origin[1]),
					 											Point2D(worldAxis[i].endpoint[0],
																				worldAxis[i].endpoint[1])
															};
	}

}

std::vector <Viewer::line> Viewer::perspectiveProject(std::vector <line> input){

	std::vector <line> projectedPoints;	
		
	for (int i = 0; i < input.size(); i++){

		projectedPoints.push_back((line){
					 											Point3D(((m_projection*(input[i].origin))[0])/
																				input[i].origin[2], 
																				((m_projection*(input[i].origin))[1])/
																				input[i].origin[2], 0),
					 											Point3D(((m_projection*(input[i].endpoint))[0])/
																				input[i].endpoint[2], 
																				((m_projection*(input[i].endpoint))[1])/
																				input[i].endpoint[2], 0)
															});

	}

	return projectedPoints;

}


void Viewer::rotateModel(int degrees, char axis){

	Matrix4x4 m_rotate = rotation((degrees*M_PI)/180,axis);
	m_rt = m_rt*m_rotate;

}

void Viewer::scaleModel(Vector3D scale){

	Matrix4x4 m_scale = scaling(scale);
	m_s = m_s*m_scale;
}

void Viewer::translateModel(Vector3D transalate){

	Matrix4x4 m_translate = translation(transalate);
	m_rt = m_rt*m_translate;

}

void Viewer::translateView(Vector3D transalate){

	Matrix4x4 m_translate = translation(transalate);
	m_viewing = m_translate.invert()*m_viewing;

}

void Viewer::rotateView(double degrees, char axis){

	Matrix4x4 m_rotate = rotation((degrees*M_PI)/180,axis);
	Matrix4x4 m_move1 = translation(-offset);
	Matrix4x4 m_move2 = translation(offset);
	m_viewing = m_move2*m_rotate.invert()*m_move1*m_viewing;

}


void Viewer::clip(std::vector<line> &input, Point3D p, Vector3D n){

std::vector<line>::iterator i = input.begin();

	while (i != input.end()){
		
		if ((i->origin - p).dot(n) < 0 && (i->endpoint - p).dot(n) < 0){
			input.erase(i);
		}

		else if ((i->origin - p).dot(n) > 0 && (i->endpoint - p).dot(n) > 0){
			i++;
		}

		else {

			double t= ((i->origin - p).dot(n))/ ((i->origin - i->endpoint).dot(n));

			Point3D intersection = i->origin + t*(i->endpoint - i->origin);

			if ((i->origin - p).dot(n) > 0){
				i->endpoint = intersection;
			}
			
			else if ((i->endpoint - p).dot(n) > 0){
				i->origin = intersection;
			}

			i++;
		} 

	}

}


void Viewer::invalidate()
{
  // Force a rerender
  Gtk::Allocation allocation = get_allocation();
  get_window()->invalidate_rect( allocation, false);
}

void Viewer::set_perspective(double fov, double aspect,
                             double near, double far)
{
  	m_projection= Matrix4x4(
				Vector4D(1/(tan((fov*M_PI)/360)),0,0,0),
				Vector4D(0,1/(tan((fov*M_PI)/360)),0,0),
				Vector4D(0,0,(far+near)/(far-near),(-2*far*near)/(far-near)),
				Vector4D(0,0,1,0));
}

void Viewer::reset_view()
{
  originalViewport = true;

	m_s = Matrix4x4();
	m_rt = Matrix4x4();

	m_viewing = Matrix4x4();
	m_projection = Matrix4x4();

	translateView(Vector3D(0,0,-20));
	translateModel(Vector3D(-3,0,0));

	interactionMode = M_ROTATE;

	invalidate();
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


	offset = Vector3D(0,0,0);

	if (ORTHO == false){
		translateView(Vector3D(0,0,-20));
		translateModel(Vector3D(-3,0,0));
	}

	else {
		translateModel(Vector3D(100,100,0));
		scaleModel(Vector3D(10,10,10));
	}
	
  gldrawable->gl_end();
}

bool Viewer::on_expose_event(GdkEventExpose* event)
{
  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable) return false;

  if (!gldrawable->gl_begin(get_gl_context()))
    return false;

  // Here is where your drawing code should go.
  
  draw_init(get_width(), get_height());

	if(originalViewport){
		viewH = get_height()*0.9;
		viewW = get_width()*0.9;
		viewC = Point2D(get_width()/2, get_height()/2);
		fov = 30;
		nearPlane = 0.5;
		farPlane = 50;
	}
  
 

  set_colour(Colour(0.1, 0.1, 0.1));


	//go through all modeling points and apply modeling transformations
	std::vector <line> newPoints(modelPoints);
	newPoints.insert(newPoints.end(), worldAxis.begin(), worldAxis.end());

	
	//this transforms the lines for the cube
	for (int i = 0; i < newPoints.size()-6; i++){
		newPoints[i].origin = (m_viewing*m_rt*m_s)*(newPoints[i].origin);
		newPoints[i].endpoint = (m_viewing*m_rt*m_s)*(newPoints[i].endpoint);
	}

	//this transforms the cube's axis, and reverts all scaling
	for (int i = newPoints.size()-6; i < newPoints.size()-3; i++){
		newPoints[i].endpoint = (m_viewing*m_rt)*(newPoints[i].endpoint);
		newPoints[i].origin = (m_viewing*m_rt)*(newPoints[i].origin);
	}
	
	//this transforms the world 
	for (int i = newPoints.size()-3; i < newPoints.size(); i++){
		newPoints[i].origin = m_viewing*(newPoints[i].origin);
		newPoints[i].endpoint = m_viewing*(newPoints[i].endpoint);
	}

	//orthographic projection code

	if (ORTHO){	

		orthoProject(newPoints);

		for (int i = 0; i <= orthoLines.size(); i++){
			draw_line(orthoLines[i].origin, orthoLines[i].endpoint);
		}
	}
	
	//perspective projection code
	else {
	
		set_perspective(fov,1,nearPlane,farPlane);

		//near and far plane clipping
		clip(newPoints, Point3D(0,0,nearPlane), Vector3D(0,0,1));
		clip(newPoints, Point3D(0,0,farPlane), Vector3D(0,0,-1));

		//perspective projection
		std::vector <line> projPoints = perspectiveProject(newPoints);

		//viewport clipping
		clip(projPoints, Point3D(-1,-1, 0), Vector3D(1,0,0));
		clip(projPoints, Point3D(-1,-1, 0), Vector3D(0,1,0));
		clip(projPoints, Point3D(1,1, 0), Vector3D(-1,0,0));
		clip(projPoints, Point3D(1,1, 0), Vector3D(0,-1,0));

		//drawing scene into viewport
		for (int i = 0; i < projPoints.size(); i++){
			draw_line(Point2D(viewC[0] + projPoints[i].origin[0]*viewW/2,
												viewC[1] + projPoints[i].origin[1]*viewH/2), 
			          Point2D(viewC[0] + projPoints[i].endpoint[0]*viewW/2,
												viewC[1] + projPoints[i].endpoint[1]*viewH/2));
		}


		set_colour(Colour(1, 0, 0));

		//draws viewport
		draw_line(Point2D(viewC[0]-viewW/2,viewC[1]-viewH/2), 
			        Point2D(viewC[0]+viewW/2,viewC[1]-viewH/2));
		draw_line(Point2D(viewC[0]-viewW/2,viewC[1]+viewH/2), 
			        Point2D(viewC[0]+viewW/2,viewC[1]+viewH/2));
		draw_line(Point2D(viewC[0]-viewW/2,viewC[1]-viewH/2), 
			        Point2D(viewC[0]-viewW/2,viewC[1]+viewH/2));
		draw_line(Point2D(viewC[0]+viewW/2,viewC[1]-viewH/2), 
			        Point2D(viewC[0]+viewW/2,viewC[1]+viewH/2));
	
	}

  draw_complete();
            
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

  gldrawable->gl_end();

  return true;
}

bool Viewer::on_button_press_event(GdkEventButton* event)
{
  //std::cerr << "Stub: Button " << event->button << " pressed" << std::endl;

	if (event->button == 1 && interactionMode == VIEWPORT){
		m1=true;
		originalViewport = false;
		firstCorner = Point2D(event->x, event->y);
	}

	if (interactionMode == V_PERSPECTIVE){
		originalViewport = false;
	}

	if (event->button == 1) m1 = true;
	if (event->button == 2) m2 = true;
	if (event->button == 3) m3 = true;
	
	x1 = x2 = event->x;
	
  return true;
}

bool Viewer::on_button_release_event(GdkEventButton* event)
{
  //std::cerr << "Stub: Button " << event->button << " released" << std::endl;	

	if (event->button == 1 && interactionMode == VIEWPORT){
		m1=false;
		secondCorner = Point2D(event->x, event->y);
		
		if (secondCorner[0] > get_width()) secondCorner[0] = get_width();
		if (secondCorner[0] < 0) secondCorner[0] = 0;
		if (secondCorner[1] > get_height()) secondCorner[1] = get_height();
		if (secondCorner[1] < 0) secondCorner[1] = 0;

		viewW = abs(secondCorner[0] - firstCorner[0]);
		viewH = abs(secondCorner[1] - firstCorner[1]);
		
		int centreX;		
		int centreY;

		if (firstCorner[0] < secondCorner[0]) centreX = firstCorner[0]+viewW/2;
		else if (firstCorner[0] > secondCorner[0]) centreX = secondCorner[0]+viewW/2;
		if (firstCorner[1] < secondCorner[1]) centreY = firstCorner[1]+viewH/2;
		else if (firstCorner[1] > secondCorner[1]) centreY = secondCorner[1]+viewH/2;

		viewC = Point2D(centreX, centreY);
		invalidate();

	}

	if (event->button == 1) m1 = false;
	if (event->button == 2) m2 = false;
	if (event->button == 3) m3 = false;

  return true;
}

bool Viewer::on_motion_notify_event(GdkEventMotion* event)
{
 // std::cerr << "Stub: Motion at " << event->x << ", " << event->y << std::endl;

	x1 = x2;
	x2 = event->x;
	bool right = false;

	if (x2-x1 > 0) right = true;
	

	if (interactionMode == M_ROTATE){
		if (right){		
			if (m1) rotateModel(2,'x');
			if (m2) rotateModel(2,'y');
			if (m3) rotateModel(2,'z');
		}
		else {		
			if (m1) rotateModel(-2,'x');
			if (m2) rotateModel(-2,'y');
			if (m3) rotateModel(-2,'z');
		}
	}

	if (interactionMode == M_SCALE){
		if (right){		
			if (m1) scaleModel(Vector3D(1.05,1,1));
			if (m2) scaleModel(Vector3D(1,1.05,1));
			if (m3) scaleModel(Vector3D(1,1,1.05));
		}
		else{		
			if (m1) scaleModel(Vector3D(0.95,1,1));
			if (m2) scaleModel(Vector3D(1,0.95,1));
			if (m3) scaleModel(Vector3D(1,1,0.95));
		}
	}

	if (interactionMode == M_TRANSLATE){
		if (right){
			if (m1) translateModel(Vector3D(0.05,0,0));
			if (m2) translateModel(Vector3D(0,0.05,0));
			if (m3) translateModel(Vector3D(0,0,0.05));
		}
		else {
			if (m1) translateModel(Vector3D(-0.05,0,0));
			if (m2) translateModel(Vector3D(0,-0.05,0));
			if (m3) translateModel(Vector3D(0,0,-0.05));
		}
	}

	if (interactionMode == V_TRANSLATE){
		if (right){
			if (m1) translateView(Vector3D(0.1,0,0));
			if (m2) translateView(Vector3D(0,0.1,0));
			if (m3) translateView(Vector3D(0,0,0.1));
		}
		else {
			if (m1) translateView(Vector3D(-0.1,0,0));
			if (m2) translateView(Vector3D(0,-0.1,0));
			if (m3) translateView(Vector3D(0,0,-0.1));
		}
	}

	if (interactionMode == V_ROTATE){
		if (!right){		
			if (m1) rotateView(0.7,'x');
			if (m2) rotateView(0.7,'y');
			if (m3) rotateView(0.7,'z');
		}
		else {
			if (m1) rotateView(-0.7,'x');
			if (m2) rotateView(-0.7,'y');
			if (m3) rotateView(-0.7,'z');
		}
	}
	if (interactionMode == V_PERSPECTIVE){
		if (!right){		
			if (m1 && fov > 5) fov--;
			if (m2 && nearPlane > 0.5) nearPlane-=0.5;
			if (m3 && (int)farPlane > (int)nearPlane+1) farPlane-=0.5;
		}
		else {
			if (m1 && fov < 160) fov++;
			if (m2 && (int)nearPlane < (int)farPlane-1) nearPlane+=0.5;
			if (m3) farPlane+=0.5;
		}
	}
	
	invalidate();

	
  return true;
}
