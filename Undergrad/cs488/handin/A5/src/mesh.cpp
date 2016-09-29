#include "mesh.hpp"
#include <iostream>

using namespace std;

Mesh::Mesh(const std::vector<Point3D>& verts,
           const std::vector< std::vector<int> >& faces)
  : m_verts(verts),
    m_faces(faces)
{
}


bool Mesh::pointInFace(Point3D p, Face f, Vector3D n){

	for (int i = 0; i < f.size(); i++){

		int j = 0;
		if (i+1 != f.size()) j = i+1;
	
		Vector3D m = (p - m_verts[f[j]]).cross(m_verts[f[i]] - m_verts[f[j]]);

		if (m.dot(n) < 0) return false;

	}

	return true;

}


bool Mesh::intersectFace(Face f, Ray &r, double &tValue, Vector3D &norm){


	Point3D lp = r.eyePoint;
	Vector3D dir = r.directionVector;

	Vector3D fn = (m_verts[f[2]] - m_verts[f[1]]).cross(
																	(m_verts[f[0]] - m_verts[f[1]]));
	Point3D fp = m_verts[f[1]];

	double num = (fp-lp).dot(fn);
	double den = dir.dot(fn);

	if (num == 0 && den == 0){
		return false;
	}

	else if (den == 0){
		return false;
	}

	else{
		//ray intersects
	
		double t = num/den;
		
		if (t > 0) {
			Point3D inter = lp + t*dir;

			if (pointInFace(inter, f, fn)){

				if (t < tValue){
					tValue = t;
					norm = fn;
					return true;
				}					
			}
		}
	}

	return false;

}


bool Mesh::intersect(Ray r, double &tValue, Vector3D &norm){


	double xMax = -std::numeric_limits<double>::max(); 
	double yMax = -std::numeric_limits<double>::max(); 
	double zMax = -std::numeric_limits<double>::max(); 

	double xMin = std::numeric_limits<double>::max(); 
	double yMin = std::numeric_limits<double>::max(); 
	double zMin = std::numeric_limits<double>::max(); 

	for (int i = 0; i < m_verts.size(); i++){

		if (m_verts[i][0] > xMax) xMax = m_verts[i][0];
		if (m_verts[i][1] > yMax) yMax = m_verts[i][1];
		if (m_verts[i][2] > zMax) zMax = m_verts[i][2];

		if (m_verts[i][0] < xMin) xMin = m_verts[i][0];
		if (m_verts[i][1] < yMin) yMin = m_verts[i][1];
		if (m_verts[i][2] < zMin) zMin = m_verts[i][2];


	}

	Point3D origin = Point3D(xMin, yMin, zMin);
	double size = fmax(xMax - xMin, fmax(yMax - yMin, zMax - zMin));

	NonhierBox boundingBox = NonhierBox(origin,size);

	

	if (boundingBox.intersect(r, tValue, norm)) {

		tValue = std::numeric_limits<double>::max();

		for (int i = 0; i < m_faces.size(); i++){
			
			intersectFace(m_faces[i], r, tValue, norm);
			
		}

		if (tValue < std::numeric_limits<double>::max()) return true;
		else return false;

	}

	//missed the box
	return false;

}



std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  std::cerr << "mesh({";
  for (std::vector<Point3D>::const_iterator I = mesh.m_verts.begin(); I != mesh.m_verts.end(); ++I) {
    if (I != mesh.m_verts.begin()) std::cerr << ",\n      ";
    std::cerr << *I;
  }
  std::cerr << "},\n\n     {";
  
  for (std::vector<Mesh::Face>::const_iterator I = mesh.m_faces.begin(); I != mesh.m_faces.end(); ++I) {
    if (I != mesh.m_faces.begin()) std::cerr << ",\n      ";
    std::cerr << "[";
    for (Mesh::Face::const_iterator J = I->begin(); J != I->end(); ++J) {
      if (J != I->begin()) std::cerr << ", ";
      std::cerr << *J;
    }
    std::cerr << "]";
  }
  std::cerr << "});" << std::endl;
  return out;
}
