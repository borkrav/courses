#ifndef CS488_LIGHT_HPP
#define CS488_LIGHT_HPP

#include "algebra.hpp"
#include <iosfwd>

class Ray;

// Represents a simple point light.
struct Light {
  Light();
	double intersect(Ray r);
  
  Colour colour;
  Point3D position;
  double falloff[3];
	double area[2];
	Vector3D normal;
	Vector3D left;
};

std::ostream& operator<<(std::ostream& out, const Light& l);




#endif
