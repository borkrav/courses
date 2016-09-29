#ifndef CS488_VIEWER_HPP
#define CS488_VIEWER_HPP
#include "game.hpp"

#include <gtkmm.h>
#include <gtkglmm.h>

// The "main" OpenGL widget
class Viewer : public Gtk::GL::DrawingArea {
public:
  Viewer();
  virtual ~Viewer();

	enum Mode {
		WIREFRAME,
		FACE, 
		MULTICOLOURED
	};
	
	void setMode(Mode i);
	void setSpeed(int i);
	void newGame();
	void resetGame();
	void toggleBuffering();
	void controls(int key);
	void drawCube(float x, float y, float z);
  // A useful function that forces this widget to rerender. If you
  // want to render a new frame, do not call on_expose_event
  // directly. Instead call this, which will cause an on_expose_event
  // call when the time is right.
  void invalidate();
  
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

	bool slowGameTimeHandler();
	bool medGameTimeHandler();
	bool fastGameTimeHandler();


	bool render();
	float yRot;
	float ySpeed;
	float xRot;
	float xSpeed;
	float zRot;
	float zSpeed;
	float prevx;
	float x;
	bool m1;
	bool m2;
	bool m3;
	bool scaleToggle;
	float scale;
	int gameSpeed;
	bool multicoloured;	
	bool doubleBuffering;
	Game *g;
	
};

#endif
