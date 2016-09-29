#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"
#include "ray.hpp"
#include <vector>

class Primitive {
public:
  virtual ~Primitive();
	virtual bool intersect(Ray r, double &tValue, Vector3D &norm);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const Point3D& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
	
	bool intersect(Ray r, double &tValue, Vector3D &norm);

private:
  Point3D m_pos;
  double m_radius;
};

class Cyllinder : public Primitive {
public:
  Cyllinder(){}
  virtual ~Cyllinder();
	
	bool intersect(Ray r, double &tValue, Vector3D &norm);

};

class Cone : public Primitive {
public:
  Cone(){}
  virtual ~Cone();
	
	bool intersect(Ray r, double &tValue, Vector3D &norm);

};

class NonhierBox : public Primitive {
public:
  NonhierBox(const Point3D& pos, double size)
    : m_pos(pos), m_size(size)
  {
  }
  
  virtual ~NonhierBox();
	bool intersect(Ray r, double &tValue, Vector3D &norm);
	int intersectPlane(Point3D bp, Vector3D bn, Point3D lp, Vector3D dir, double &tValue, Vector3D &norm);

private:
  Point3D m_pos;
  double m_size;
};


class Sphere : public NonhierSphere {
public:
	Sphere() : NonhierSphere(Point3D(0,0,0), 1){}
  virtual ~Sphere();
};

class Cube : public NonhierBox {
public:
	Cube() : NonhierBox(Point3D(0,0,0), 1) {}
  virtual ~Cube();
};

#endif
