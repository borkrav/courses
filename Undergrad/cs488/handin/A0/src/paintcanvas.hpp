#ifndef PAINTCANVAS_HPP
#define PAINTCANVAS_HPP

#include <list>

#include <gtkmm.h>

#include "algebra.hpp"

// Define a convenient alias to be able to draw graphics later.
// The Cairo graphics context class is a bit like the Graphics
// class in Java's AWT, so we'll borrow that name here.
//
typedef Cairo::RefPtr<Cairo::Context> Graphics;

// An abstract base class that defines shapes we'll store and
// draw.  Each shape is currently defined from two corners m_from 
// and m_to, and a method that asks the shape to draw itself.
// 
class PaintShape
{
public:
	virtual ~PaintShape() {}

	virtual void draw( Graphics gc) = 0;

protected:
	PaintShape( const Point2D& from, const Point2D& to, float r, float g, float b )
		: m_from( from )
		, m_to( to )
		, s_r ( r )
		, s_g ( g )
		, s_b ( b )
	{}

protected:
	Point2D		m_from;
	Point2D		m_to;
	float s_r;
	float s_g;
	float s_b;
	
};

class PaintLine
	: public PaintShape
{
public:
	PaintLine( const Point2D& from, const Point2D& to, float r, float g, float b )
		: PaintShape( from, to, r, g, b )
	{}

	virtual void draw( Graphics gc);
};

class PaintRect
	: public PaintShape
{
public:
	PaintRect( const Point2D& from, const Point2D& to, float r, float g, float b )
		: PaintShape( from, to, r, g, b )
	{}

	virtual void draw( Graphics gc);
};

class PaintOval
	: public PaintShape
{
public:
	PaintOval( const Point2D& from, const Point2D& to, float r, float g, float b )
		: PaintShape( from, to, r, g, b )
	{}

	virtual void draw( Graphics gc );
};

class PaintCanvas 
	: public Gtk::DrawingArea
{
public:
  enum Mode {
    DRAW_LINE,
    DRAW_OVAL,
    DRAW_RECTANGLE
  };
  
  PaintCanvas();
  virtual ~PaintCanvas();

  void set_mode(Mode mode) { m_mode = mode; }
  
  void set_colour(float r, float g, float b) { m_r = r; m_g = g; m_b = b; 
  }

  void clearShapes();
  
protected:

  // Events we implement
  // Note that we could use gtkmm's "signals and slots" mechanism
  // instead, but for many classes there's a convenient member
  // function one just needs to define that'll be called with the
  // event.
  
  virtual bool on_button_press_event(GdkEventButton* button);
  virtual bool on_button_release_event(GdkEventButton* button);

  virtual bool on_expose_event( GdkEventExpose *event );
  

private:

  //these set the global colour
  float m_r;
  float m_g;
  float m_b;

  Mode m_mode; // what to do when a user clicks

  Point2D m_start_pos; // position where the user last clicked

  std::list<PaintShape*> m_shapes;
};

#endif
