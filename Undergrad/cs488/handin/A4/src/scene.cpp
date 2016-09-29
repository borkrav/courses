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
		//	cout << result.t << endl;
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
	//cout << "precompute on geometry called" << endl;
	m_precomp = m_invtrans*m;

}


Probe GeometryNode::intersect(Ray r){

	//cout << "intersect called on geometry node" << endl;

	//r.eyePoint = (m_precomp)*r.eyePoint;
//	r.directionVector = (m_precomp)*r.directionVector;
	r.eyePoint = (m_invtrans)*r.eyePoint;
	r.directionVector = (m_invtrans)*r.directionVector;

	Probe result = Probe();

	double tValue = std::numeric_limits<double>::max();
	Vector3D normal;
	Point3D intersection;

	if (m_primitive->intersect(r, tValue, normal)) {

		intersection = r.eyePoint + ((tValue)-0.00001)*(r.directionVector);
		result = Probe(tValue, normal, intersection, (PhongMaterial*)m_material);


		result.intersection = m_trans*result.intersection;
		result.normal = m_invtrans.transpose()*result.normal;


		return result;
		
	}
	


	return result;

	

}

GeometryNode::~GeometryNode()
{
}
 
