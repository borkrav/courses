#include "scene.hpp"
#include <iostream>
#include "transform.hpp"

using namespace std;

SceneNode::SceneNode(const std::string& name)
  : m_name(name)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::precompute(Matrix4x4 m){

	ChildList::const_iterator childIter;
	//cout << "precompute called" << endl;

	m_precomp = m_invtrans*m;

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){		
		(*childIter)->precompute(m_precomp);
	}

}

Probe SceneNode::intersect(Ray r){

	//cout << "intersect called on scene node" << endl;

	ChildList::const_iterator childIter;

	Probe result = Probe();

	r.eyePoint = (m_invtrans)*r.eyePoint;
	r.directionVector = (m_invtrans)*r.directionVector;
	
	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
		
		Probe hit = (*childIter)->intersect(r);



		if (hit.t < result.t){
			result = hit;

		}

		

	}

	result.intersection = m_trans*result.intersection;
	result.normal = m_invtrans.transpose()*result.normal;

	return result;

}

void SceneNode::rotate(char axis, double angle)
{
  //std::cerr << "Stub: Rotate " << m_name << " around " << axis << " by " << angle << std::endl;
  Matrix4x4 m_rotate = rotation((angle*M_PI)/180,axis);
	set_transform(m_trans*m_rotate);
}

void SceneNode::scale(const Vector3D& amount)
{
  //std::cerr << "Stub: Scale " << m_name << " by " << amount << std::endl;
 	Matrix4x4 m_scale = scaling(amount);
	set_transform(m_trans*m_scale);
}

void SceneNode::translate(const Vector3D& amount)
{
  //std::cerr << "Stub: Translate " << m_name << " by " << amount << std::endl;
	Matrix4x4 m_translate = translation(amount);
	set_transform(m_trans*m_translate);
}

bool SceneNode::is_joint() const
{
  return false;
}

JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
}

JointNode::~JointNode()
{
}

bool JointNode::is_joint() const
{
  return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
  m_joint_x.min = min;
  m_joint_x.init = init;
  m_joint_x.max = max;
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;
  m_joint_y.max = max;
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
}


void GeometryNode::precompute(Matrix4x4 m){
	//this stuff doesn't work...
	//cout << "precompute on geometry called" << endl;
	m_precomp = m_invtrans*m;

}

std::pair<Probe,Probe> GeometryNode::getSegment(Ray r){

	double tValue = std::numeric_limits<double>::max();
	Vector3D normal;
	Point3D intersection;
	Probe r1 = Probe();
	Probe r2 = Probe();

	if (m_primitive->intersect(r, tValue, normal)){
		intersection = r.eyePoint + ((tValue)-0.00001)*(r.directionVector);

		if (m_material->isPhong()){
			r1 = Probe(tValue, normal, intersection, (PhongMaterial*)m_material);
		}
		if (m_material->isTransparent()){
			r1 = Probe(tValue, normal, intersection, (TransparentMaterial*)m_material);
		}

		Ray backside = r;
		backside.bend(r.eyePoint + ((tValue)+0.00001)*(r.directionVector), r.directionVector);
		m_primitive->intersect(backside, tValue, normal);
		intersection = backside.eyePoint + ((tValue)-0.00001)*(backside.directionVector);

		if (m_material->isPhong()){
			r2 = Probe(tValue, -normal, intersection, (PhongMaterial*)m_material);
		}
		if (m_material->isTransparent()){
			r2 = Probe(tValue, -normal, intersection, (TransparentMaterial*)m_material);
		}

	}

	pair<Probe,Probe> s1 = make_pair(r1,r2);

	//THIS ONLY WORKS FOR NON-HIERCHIAL DATA
	if (m_op != ""){

		pair<Probe, Probe> s2 = ((GeometryNode*)m_branch)->getSegment(r);	

		if (m_op == "u"){
			
			if (s1.first.t == std::numeric_limits<double>::max() && 
				s2.first.t != std::numeric_limits<double>::max()){
				s2.first.use = true;
				return s2;

			}

			else if (s1.first.t != std::numeric_limits<double>::max() && 
				s2.first.t == std::numeric_limits<double>::max()){
				s1.first.use = true;
				return s1;

			}

			else if (s1.first.t == std::numeric_limits<double>::max() && 
				s2.first.t == std::numeric_limits<double>::max()){
				s1.first.use = true;
				return s1;
			}

			else {
				//get minimum of s1 and s2

				double d1 = s1.first.intersection.distance(r.eyePoint);
				double d2 = s2.first.intersection.distance(r.eyePoint);

				if (d1 < d2) {
					s1.first.use = true;
					return s1;
				}
				else if (d2 < d1){
					s2.first.use = true;
					return s2;
				}
			}
		}

		if (m_op == "n"){
			
			if (s1.first.t == std::numeric_limits<double>::max() || 
					s2.first.t == std::numeric_limits<double>::max()){

				s1.first.t = std::numeric_limits<double>::max();
				return s1;

			}

			else {
				//get smallest first point and smallest last point

				double d1 = s1.first.intersection.distance(r.eyePoint);
				double d2 = s2.first.intersection.distance(r.eyePoint);

				if (d1 > d2) {
					s1.first.use = true;
					return s1;
				}
				else if (d2 > d1){
					s2.first.use = true;
					return s2;
				}

			}
		}


	if (m_op == "d"){
			

			//4 cases

			// s1 ------
			// s2  ---- 

			// s1  ----
			// s2 ------

			// s1 -----
			// s2  -----

			// s1  -----
			// s2 -----

			if (s1.first.t != std::numeric_limits<double>::max() && 
					s2.first.t == std::numeric_limits<double>::max()){

				s1.first.use = true;
				return s1;

			}

			else if (s1.first.t != std::numeric_limits<double>::max() && 
					s2.first.t != std::numeric_limits<double>::max()){

				double d1 = s1.first.intersection.distance(r.eyePoint);
				double d2 = s1.second.intersection.distance(r.eyePoint);
				double d3 = s2.first.intersection.distance(r.eyePoint);
				double d4 = s2.second.intersection.distance(r.eyePoint);

					if (d1 < d3 && d2 > d4) {
						s1.first.use = true;
						return s1;
					}

					else if (d1 > d3 && d2 < d4 || d1 == d3 && d2 == d4){
						s1.first.t = std::numeric_limits<double>::max();
						return s1;
					}

					else if (d1 < d3 && d2 < d4){
						s1.first.use = true;
						return s1;
					}

					else if (d1 > d3 && d2 > d4){
						s2.second.use = true;
						return s2;
					}
			}
		}

		
	}
	
	return s1;


}


Probe GeometryNode::intersect(Ray r){

	r.eyePoint = (m_invtrans)*r.eyePoint;
	r.directionVector = (m_invtrans)*r.directionVector;

	double tValue = std::numeric_limits<double>::max();
	Vector3D normal;
	Point3D intersection;
	Probe result = Probe();

	pair<Probe, Probe> segment;

	segment = getSegment(r);

	if (segment.first.use == true) result = segment.first;
	else if (segment.second.use == true) result = segment.second;
	else result = segment.first;

	 
/*
	else {
		//no csg
		if (m_primitive->intersect(r, tValue, normal)) {
			intersection = r.eyePoint + ((tValue)-0.00001)*(r.directionVector);
		}

		if (m_material->isPhong()){
		result = Probe(tValue, normal, intersection, (PhongMaterial*)m_material);
		}
		if (m_material->isTransparent()){
			result = Probe(tValue, normal, intersection, (TransparentMaterial*)m_material);
		}
	}
*/
	
	result.intersection = m_trans*result.intersection;
	result.normal = m_invtrans.transpose()*result.normal;

	return result;

}

GeometryNode::~GeometryNode()
{
}
 
