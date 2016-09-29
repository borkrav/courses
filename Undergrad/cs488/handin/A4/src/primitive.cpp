#include "primitive.hpp"
#include "polyroots.hpp"

using namespace std;

Primitive::~Primitive()
{
}

bool Primitive::intersect(Ray r, double &tValue, Vector3D &norm){
	return false;
}

Sphere::~Sphere()
{
}

Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

bool NonhierSphere::intersect(Ray r, double &tValue, Vector3D &norm){

	//cout << "intersect called on NonhierSphere" << endl;


	Vector3D d = r.directionVector;
	//d.normalize();

	//cout << d << endl;	

	double A = d.dot(d);
	double B = 2*((r.eyePoint - m_pos).dot(d));
	double C = (r.eyePoint - m_pos).dot((r.eyePoint - m_pos)) - m_radius*m_radius;

	double roots[2] = {0,0};

	int result = quadraticRoots(A,B,C,roots);
		
	//cout << A << " " << B << " " << C << endl;
	//cout << roots[0] << " " << roots[1]<< endl;

	if (result  > 0) {
		if (result == 1){
			if (roots[0] < 0) tValue = std::numeric_limits<double>::max();
			else tValue = roots[0];
		}
		else if (result == 2){
			if (roots[0] < 0 && roots[1] < 0){
				 tValue = std::numeric_limits<double>::max();
			}
			else if (roots[0] < 0) tValue = roots[1];
			else if (roots[1] < 0) tValue = roots[0];
			else tValue = min(roots[0], roots[1]);
		}

		//cout << tValue << endl;

		norm = (r.eyePoint + tValue*d) - m_pos;
		//norm.normalize();

		return true;
	}

	return false;
		

}

NonhierBox::~NonhierBox()
{
}

int NonhierBox::intersectPlane(Point3D bp, Vector3D bn, Point3D lp, Vector3D dir, double &tValue, Vector3D &norm){

	double num = (bp-lp).dot(bn);
	double den = dir.dot(bn);

	if (num == 0 && den == 0){
		return 0;
	}

	else if (den == 0){
		return 0;
	}

	else{
		//ray intersects
	
		double t = num/den;

		double e = 0.00001;
		
		if (t > 0) {
			Point3D inter = lp + t*dir;

			if (inter[0] >= m_pos[0] - e && inter[0] <= m_pos[0] + m_size + e && 
					inter[1] >= m_pos[1] - e && inter[1] <= m_pos[1] + m_size + e &&
					inter[2] >= m_pos[2] - e && inter[2] <= m_pos[2] + m_size + e){

				if (t < tValue){
					tValue = t;
					norm = bn;
					return 1;
				}
			}
	}
	
	return 0;

	}
	
}

bool NonhierBox::intersect(Ray r, double &tValue, Vector3D &norm){

	//cout << "intersect called on NonhierBox" << endl;

	//gotta transform the normals at some point, for rotations. Should be interesting


	Point3D bp[6] =  {Point3D(m_pos[0], m_pos[1], m_pos[2] + m_size), 
										Point3D(m_pos[0], m_pos[1], m_pos[2]),
										Point3D(m_pos[0], m_pos[1] + m_size, m_pos[2]),
										Point3D(m_pos[0], m_pos[1], m_pos[2]),
										Point3D(m_pos[0] + m_size, m_pos[1], m_pos[2]),
										Point3D(m_pos[0], m_pos[1], m_pos[2])};
	

	Vector3D bn[6] = {Vector3D(0,0,1),
										Vector3D(0,0,-1),
										Vector3D(0,1,0),
										Vector3D(0,-1,0),
										Vector3D(1,0,0),
										Vector3D(-1,0,0)};
	
	Point3D lp = r.eyePoint;
	Vector3D dir = r.directionVector;

	int result = 0;

	for (int i = 0; i < 6; i++){
		result += intersectPlane(bp[i], bn[i], lp, dir, tValue, norm);
	}


	if (result >= 1) return true;

	else return false;


}
