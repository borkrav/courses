#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP
#include <GL/gl.h>
#include <GL/glu.h>
#include "algebra.hpp"

class Primitive {
public:
  virtual ~Primitive();
  virtual void walk_gl(bool picking) const = 0;
	bool picked;
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
  virtual void walk_gl(bool picking) const;
	//static void render();

};

#endif
