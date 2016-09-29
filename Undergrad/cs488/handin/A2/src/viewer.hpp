#ifndef CS488_VIEWER_HPP
#define CS488_VIEWER_HPP

#include <gtkmm.h>
#include <gtkglmm.h>
#include "algebra.hpp"
#include <stdlib.h>
#include "a2.hpp"

// The "main" OpenGL widget
class Viewer : public Gtk::GL::DrawingArea {
public:
  Viewer();
  virtual ~Viewer();

  // A useful function that forces this widget to rerender. If you
  // want to render a new frame, do not call on_expose_event
  // directly. Instead call this, which will cause an on_expose_event
  // call when the time is right.
  void invalidate();

  // *** Fill in these functions (in viewer.cpp) ***

  // Set the parameters of the current perspective projection using
  // the semantics of gluPerspective().
  void set_perspective(double fov, double aspect,
                       double near, double far);

  // Restore all the transforms and perspective parameters to their
  // original state. Set the viewport to its initial size.
  void reset_view();


	enum Mode{
		M_ROTATE,
		M_TRANSLATE,
		M_SCALE,
		V_ROTATE,
		V_TRANSLATE,
		V_PERSPECTIVE,
		VIEWPORT
	};

	void setMode(Mode mode);

	Mode interactionMode;
	double nearPlane;
	double farPlane;

protected:

  // Events we implement
  // Note that we could use gtkmm's "signals and slots" mechanism
  // instead, but for many classes there's a convenient member
  // function one just needs to define that'll be called with the
  // event.

  // Called when GL is first initialized
  virtual void on_realize();
  // Called when our window needs to be redrawn
  virtual bool on_expose_event(GdkEventExpose* event);
  // Called when the window is resized
  virtual bool on_configure_event(GdkEventConfigure* event);
  // Called when a mouse button is pressed
  virtual bool on_button_press_event(GdkEventButton* event);
  // Called when a mouse button is released
  virtual bool on_button_release_event(GdkEventButton* event);
  // Called when the mouse moves
  virtual bool on_motion_notify_event(GdkEventMotion* event);

private:




  // *** Fill me in ***
  // You will want to declare some more matrices here
  
	struct line {
		Point3D origin;
		Point3D endpoint;
	};

	struct orthoLine {
		Point2D origin;
		Point2D endpoint;
	};


	void initializeLines();
	void orthoProject(std::vector <line> input);
	void rotateModel(int degrees, char axis);
	void scaleModel(Vector3D scale);
	void translateModel(Vector3D translate);
	void translateView(Vector3D translate);
	void rotateView(double degrees, char axis);
	std::vector <line> perspectiveProject(std::vector <line> input);
	void clip(std::vector<line> &input, Point3D p, Vector3D n);


	Matrix4x4 m_s;
	Matrix4x4 m_rt;

	Matrix4x4 m_viewing;
	Matrix4x4 m_projection;

	Vector3D offset;

	bool originalViewport;
	int viewH;
	int viewW;
	Point2D viewC;
	Point2D firstCorner;
	Point2D secondCorner;


	double fov;

  std::vector <line> modelPoints;	
  std::vector <line> worldAxis;

	std::vector <orthoLine> orthoLines;


	//stuff for controls

	bool m1;
	bool m2;
	bool m3;

	int x1;
	int x2;

};

#endif
