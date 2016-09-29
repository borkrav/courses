#ifndef CS488_RAY_HPP
#define CS488_RAY_HPP

#include "algebra.hpp"
#include "material.hpp"
#include <limits>
#include <stack>


class Ray {
	
	public:

	Ray();

	Ray(Point3D origin, Vector3D direction) : eyePoint(origin), directionVector(direction), colour(Colour(0,0,0)), bendCount(0), distributed(false) {
		refrIndex = std::stack<double>();
	}


	void bend(Point3D origin, Vector3D direction){
		eyePoint = origin;
		directionVector = direction;
		bendCount++;
	}


	Point3D eyePoint;
	Vector3D directionVector;
	Colour colour;
	int bendCount;
	std::stack<double>refrIndex;
	bool distributed;

};


#endif
