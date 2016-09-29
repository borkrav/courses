#ifndef CS488_VIEWER_HPP
#define CS488_VIEWER_HPP

#include <gtkmm.h>
#include <gtkglmm.h>


typedef GLdouble Matrix[4][4];
#define  DIR_NONE      0x00 
#define  DIR_X         0x01     
#define  DIR_Y         0x02    
#define  DIR_Z         0x04  

#define  SENS_PANX     30.0
#define  SENS_PANY     23.0
#define  SENS_ZOOM     35.0 

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


	enum App{
		R_POS,
		R_ORI,
		R_JOINTS,
		R_ALL
	};
	
	enum Mode{
		POS_ORI,
		JOINTS
	};

	enum Edit{
		UNDO,
		REDO
	};

	enum Option{
		CIRCLE,
		Z_BUFFER,
		BACKF,
		FRONTF
	};

	void setApp(App app);
	void setMode(Mode mode);
	void setEdit(Edit edit);
	void setOption(Option option);

	int status;
  
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

  // Draw a circle for the trackball, with OpenGL commands.
  // Assumes the context for the viewer is active.
  void draw_trackball_circle();
  
private:

	void vToggleDir(int nDir);
	void vPerformTransfo(float fOldX, float fNewX, float fOldY, float fNewY);

	bool circle;
	bool zBuffer;
	bool backf;
	bool frontf;

	bool camera;
	bool picking;

	bool m2;
	bool m3;

	int nCurrentDir;

	int yCur;
	int yPrev;

	int xCur;
	int xPrev;

};

#endif
