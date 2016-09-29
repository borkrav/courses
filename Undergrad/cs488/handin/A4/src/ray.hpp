#ifndef CS488_RAY_HPP
#define CS488_RAY_HPP

#include "algebra.hpp"
#include "material.hpp"
#include <limits>


class Ray {
	
	public:

	Ray(Point3D origin, Vector3D direction) : eyePoint(origin), directionVector(direction), colour(Colour(0,0,0)) /*t(std::numeric_limits<double>::max())*/ {}


	Point3D eyePoint;
	Vector3D directionVector;
	Colour colour;

//	PhongMaterial *hit;
//	double t;
//	Vector3D normal;

//	Point3D intersection;	

};


#endif
