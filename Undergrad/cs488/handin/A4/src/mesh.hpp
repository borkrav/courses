#ifndef CS488_MESH_HPP
#define CS488_MESH_HPP

#include <vector>
#include <iosfwd>
#include "primitive.hpp"
#include "algebra.hpp"

// A polygonal mesh.
class Mesh : public Primitive {
public:
  Mesh(const std::vector<Point3D>& verts,
       const std::vector< std::vector<int> >& faces);

  typedef std::vector<int> Face;

	bool intersect(Ray r, double &tValue, Vector3D &norm);
	bool intersectFace(Face f, Ray &r, double &tValue, Vector3D &norm);
	bool pointInFace(Point3D p, Face f, Vector3D n);
  
private:
  std::vector<Point3D> m_verts;
  std::vector<Face> m_faces;
	
  friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
};

#endif
