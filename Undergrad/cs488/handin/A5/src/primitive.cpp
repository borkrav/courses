#include "primitive.hpp"
#include "polyroots.hpp"

using namespace std;

double e = 0.00001;

double planeIntersect(Point3D pp, Vector3D pn, Point3D lp, Vector3D ld){

	double num = (pp-lp).dot(pn);
	double den = ld.dot(pn);

	if (num == 0 && den == 0){
		return std::numeric_limits<double>::max();
	}

	else if (den == 0){
		return std::numeric_limits<double>::max();
	}

	else{
		//ray intersects
		return num/den;
	}
}



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

Cyllinder::~Cyllinder()
{
}

bool Cyllinder::intersect(Ray r, double &tValue, Vector3D &norm){

	//cout << "a";

	double m_radius = 1;

	double A = pow(r.directionVector[0],2) +  pow(r.directionVector[2],2);
	double B = 2*r.eyePoint[0]*r.directionVector[0] +
						 2*r.eyePoint[2]*r.directionVector[2];
	double C = pow(r.eyePoint[0], 2) + pow(r.eyePoint[2], 2) - pow(m_radius, 2);   

	double roots[2] = {0,0};

	int result = quadraticRoots(A,B,C,roots);
	
	double ts = std::numeric_limits<double>::max();
	double tt = std::numeric_limits<double>::max();
	double tb = std::numeric_limits<double>::max();
	Vector3D ns;	
	Vector3D nt;	
	Vector3D nb;	

	if (result > 0) {
		if (result == 1){
			if (roots[0] < 0) ts = std::numeric_limits<double>::max();
			else ts = roots[0];
		}
		else if (result == 2){
			if (roots[0] < 0 && roots[1] < 0){
				 ts = std::numeric_limits<double>::max();
			}
			else if (roots[0] < 0) ts = roots[1];
			else if (roots[1] < 0) ts = roots[0];
			else ts = min(roots[0], roots[1]);
		}

		Point3D is = r.eyePoint + ts*r.directionVector;

		ns = is - Point3D(0,is[1],0);

		if (is[1] > 2 || is[1] < 0) ts = std::numeric_limits<double>::max();

		tt = planeIntersect(Point3D(0,2,0), Vector3D(0,1,0), 
															 r.eyePoint, r.directionVector);
		

		if (tt < std::numeric_limits<double>::max()){
			Point3D it = r.eyePoint + tt*r.directionVector;

			if ((it-Point3D(0,2,0)).dot((it-Point3D(0,2,0))) <= pow(m_radius,2)){
				nt = Vector3D(0,1,0);
			}
			else {
				tt = std::numeric_limits<double>::max();
			}

		}
		

		tb = planeIntersect(Point3D(0,0,0), Vector3D(0,-1,0), 
															 r.eyePoint, r.directionVector);
	

		if (tb < std::numeric_limits<double>::max()){
			Point3D ib = r.eyePoint + tb*r.directionVector;

			if ((ib-Point3D(0,0,0)).dot((ib-Point3D(0,0,0))) <= pow(m_radius,2)){
				nb = Vector3D(0,-1,0);
			}
			else {
				tb = std::numeric_limits<double>::max();
			}

		}

		if (tb < ts && tb < tt){
			tValue = tb;
			norm = nb;		
		}

		else if (tt < ts && tt < tb){
			tValue = tt;
			norm = nt;		
		}

		else {
			tValue = ts;
			norm = ns;
		}

		//cout << "b";
		return true;
	}
	//cout << "c";
	return false;


}

Cone::~Cone()
{
}

bool Cone::intersect(Ray r, double &tValue, Vector3D &norm){

	double m_radius = 2;

	double A = pow(r.directionVector[0],2) +  pow(r.directionVector[2],2) - 
					   pow(r.directionVector[1],2);
	double B = 2*r.eyePoint[0]*r.directionVector[0] +
						 2*r.eyePoint[2]*r.directionVector[2] - 
						 2*r.eyePoint[1]*r.directionVector[1];
	double C = pow(r.eyePoint[0], 2) + pow(r.eyePoint[2], 2) - 
						 pow(r.eyePoint[1], 2);   

	double roots[2] = {0,0};

	int result = quadraticRoots(A,B,C,roots);
	
	double ts = std::numeric_limits<double>::max();
	double tt = std::numeric_limits<double>::max();
	Vector3D ns;	
	Vector3D nt;	

	if (result > 0) {
		if (result == 1){
			if (roots[0] < 0) ts = std::numeric_limits<double>::max();
			else ts = roots[0];
		}
		else if (result == 2){
			if (roots[0] < 0 && roots[1] < 0){
				 ts = std::numeric_limits<double>::max();
			}
			else if (roots[0] < 0) ts = roots[1];
			else if (roots[1] < 0) ts = roots[0];
			else ts = min(roots[0], roots[1]);
		}

		Point3D is = r.eyePoint + ts*r.directionVector;

		ns = is - Point3D(0,is[1]+abs(is[0]),0);

		if (is[1] > 2 || is[1] < 0) ts = std::numeric_limits<double>::max();

		tt = planeIntersect(Point3D(0,2,0), Vector3D(0,1,0), 
															 r.eyePoint, r.directionVector);
		

		if (tt < std::numeric_limits<double>::max()){
			Point3D it = r.eyePoint + tt*r.directionVector;

			if ((it-Point3D(0,2,0)).dot((it-Point3D(0,2,0))) <= pow(m_radius,2)){
				nt = Vector3D(0,1,0);
			}
			else {
				tt = std::numeric_limits<double>::max();
			}

		}

		if (tt < ts){
			tValue = tt;
			norm = nt;	
			return true;	
		}

		else {
			tValue = ts;
			norm = ns;
			return true;
		}



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


//	if (tValue < std::numeric_limits<double>::max()){
	//	Point3D intersection = r.eyePoint + ((tValue)-0.00001)*(r.directionVector);
		//Point3D bmIntersection = r.eyePoint + ((tValue+2)-0.00001)*(r.directionVector);

	//	Point3D bm = intersection + 2*norm;

	//	bm = Point3D(bm[0]+sin(bm[0]/100),
							//	 bm[1]+sin(bm[1]/100),
							//	 bm[2]+sin(bm[2]/100));
	
//((float)rand())/RAND_MAX * 2.0 - 1.0

		//cout << intersection << bm << endl;	

		//cout << sin(intersection[0])/100 << endl;
		//cout << intersection <<	bm << endl;

	//	norm = bm - intersection;
//	}

	if (result >= 1) return true;

	else return false;


}
