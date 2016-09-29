#include "light.hpp"
#include "ray.hpp"
#include "mesh.hpp"
#include <iostream>
#include <vector>

using namespace std;

Light::Light()
  : colour(0.0, 0.0, 0.0),
    position(0.0, 0.0, 0.0)
{
  falloff[0] = 1.0;
  falloff[1] = 0.0;
  falloff[2] = 0.0;

	left.normalize();
	normal.normalize();
}

std::ostream& operator<<(std::ostream& out, const Light& l)
{
  out << "L[" << l.colour << ", " << l.position << ", ";
  for (int i = 0; i < 3; i++) {
    if (i > 0) out << ", ";
    out << l.falloff[i];
  }
  out << "]";
  return out;
}

double Light::intersect(Ray r){



	Vector3D up = normal.cross(left);

	up.normalize();

	Point3D c1 = position - (area[0]/2)*left - (area[1]/2)*up;
	Point3D c2 = position - (area[0]/2)*left + (area[1]/2)*up;
	Point3D c3 = position + (area[0]/2)*left - (area[1]/2)*up;
	Point3D c4 = position + (area[0]/2)*left + (area[1]/2)*up;

	//cout << position << endl;
	//cout << c1 << c2 << c3 << c4 << endl;

	vector<Point3D>points = vector<Point3D>();

	points.push_back(c1);
	points.push_back(c2);
	points.push_back(c4);
	points.push_back(c3);

	vector<int>face = vector<int>();
	vector<vector<int> > faces = vector<vector<int> >();

	face.push_back(0);
	face.push_back(1);
	face.push_back(2);
	face.push_back(3);

	faces.push_back(face);

	Mesh light = Mesh(points,faces);

	double t = std::numeric_limits<double>::max();
	Vector3D n;		

	light.intersect(r,t,n);

	return t;

}
