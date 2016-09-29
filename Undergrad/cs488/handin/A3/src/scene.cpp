#include "scene.hpp"
#include <iostream>



SceneNode::SceneNode(const std::string& name)
  : m_name(name), selected(false), xAnimatable(false), yAnimatable(false)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::walk_gl(bool picking) const
{

  // Fill me in
	//std::cout << "walk_gl called on scene node" << std::endl;

	ChildList::const_iterator childIter;
	
	glPushMatrix();


	float matrix[16];
	int k = 0;
	for (int i = 0; i < 4; i++){
		Vector4D a =  m_trans.getColumn(i);
		for (int j = 0; j < 4; j++){
			matrix[k] = a[j];
			k++;
		}
	}
	glMultMatrixf(matrix);

	int i = 1;	

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
		glPushName(i);
		(*childIter)->walk_gl();
		glPopName();
		i++;
	}
	glPopMatrix();
}

void SceneNode::saveState(){

	ChildList::const_iterator childIter;

	if (is_joint()) push();

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
	
		(*childIter)->saveState();	
		
	}
}  

bool SceneNode::lastState(){
	
	bool answer = 0;

	ChildList::const_iterator childIter;

	if (is_joint()) answer = answer || pop();

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
	
		answer = answer || (*childIter)->lastState();	
		
	}
	
	return answer;

} 

bool SceneNode::nextState(){

	bool answer = 0;

	ChildList::const_iterator childIter;

	if (is_joint()) answer = answer || load();

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
	
		answer = answer || (*childIter)->nextState();	
		
	}
	return answer;
} 

void SceneNode::resetState(){
	
	int sp = 0;


	ChildList::const_iterator childIter;

	while (sp != 1){



		for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
	
			sp = (*childIter)->stackPointer;	
		
		}

		lastState();
	}

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
	
		(*childIter)->clearStack();	
		
	}


} 

bool SceneNode::checkIfSelected(char axis){

	bool answer;

	ChildList::const_iterator childIter;


	if (axis == 'x') {
		//std::cout << selected << xAnimatable <<std::endl; 
		answer = selected && xAnimatable;
	}
	else if (axis == 'y'){
		//std::cout << selected << yAnimatable <<std::endl; 
		answer = selected && yAnimatable;
	}

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
	
		if (axis == 'x') answer = answer || (*childIter)->checkIfSelected('x');	
		else if (axis == 'y') answer = answer || (*childIter)->checkIfSelected('y');	
	}
		
	return answer;

} 



void SceneNode::pick(std::vector<int > names){

	//std::cout << names[0] << std::endl;

	ChildList::const_iterator childIter;
	int i = 1;
	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){

		if (i == names[0]){
			names.erase(names.begin());			
			(*childIter)->pick(names);
			break;
		}
		i++;		
	}
}

void SceneNode::animate(int angle, char axis){

	ChildList::const_iterator childIter;

	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){

		(*childIter)->animate(angle, axis);

	}

}

void SceneNode::rotate(char axis, double angle)
{
 // std::cerr << "Stub: Rotate " << m_name << " around " << axis << " by " << 		angle << std::endl;

	Matrix4x4 m_rotate = rotation((angle*M_PI)/180,axis);
	m_trans = m_trans*m_rotate;


}

void SceneNode::scale(const Vector3D& amount)
{
 //std::cerr << "Stub: Scale " << m_name << " by " << amount << std::endl;
	
	Matrix4x4 m_scale = scaling(amount);
	m_trans = m_trans*m_scale;

}

void SceneNode::translate(const Vector3D& amount)
{
 // std::cerr << "Stub: Translate " << m_name << " by " << amount << std::endl;
	
	Matrix4x4 m_translate = translation(amount);
	m_trans = m_trans*m_translate; 

}

bool SceneNode::is_joint() const
{
  return false;
}

void SceneNode::push(){}
void SceneNode::clearStack(){}
bool SceneNode::pop(){return 0;}
bool SceneNode::load(){return 0;}


JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
}

JointNode::~JointNode()
{
}

void JointNode::walk_gl(bool picking) const
{
//std::cout << "walk_gl called on joint node" << std::endl;
  // Fill me in

	//std::cout << stackPointer << " " << redoStack.size() << std::endl;

	ChildList::const_iterator childIter;
	
	glPushMatrix();


	float matrix[16];
	int k = 0;
	for (int i = 0; i < 4; i++){
		Vector4D a =  m_trans.getColumn(i);
		for (int j = 0; j < 4; j++){
			matrix[k] = a[j];
			k++;
		}
	}
	glMultMatrixf(matrix);
	int i = 1;	
	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
		glPushName(i);
		(*childIter)->walk_gl();
		glPopName();
		i++;
	}
	glPopMatrix();


}

void JointNode::pick(std::vector<int > names){


	if (names.size() == 2) {

		if (m_joint_x.min != m_joint_x.max || m_joint_y.min != m_joint_y.max){
				
			
			
			ChildList::const_iterator childIter;
			int i = 1;
			for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){

				if (i == names[0]){

					if ((*childIter)->selected == true && selected) {
						selected = false;
						//std::cout << "joint deselected" << std::endl;
					}
					else {
						selected = true;		
						//std::cout << "joint selected" << std::endl;				
					}
		
					names.erase(names.begin());			
					(*childIter)->pick(names);
					break;
				}
				i++;		
			}	
		}	


	}

	else {

		ChildList::const_iterator childIter;
		int i = 1;
		for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){

			if (i == names[0]){
				names.erase(names.begin());			
				(*childIter)->pick(names);
				break;
			}
			i++;		
		}
	}
}

void JointNode::push(){

	std::vector< std::pair<Matrix4x4, std::pair <int, int> > >temp;

	if (stackPointer < redoStack.size()){
		for (int i = 0; i< stackPointer; i++){
			temp.push_back(std::make_pair(redoStack[i].first,redoStack[i].second));
		}
		redoStack = temp;
		stackPointer = redoStack.size();
	}

	//std::cout << "done copying" << std::endl;

//	std::cout << "push: " << m_joint_x.init << std::endl;
	
	redoStack.push_back(std::make_pair (m_trans, std::make_pair (x_current, y_current)));
	stackPointer++;
	
}

void JointNode::clearStack(){

	std::vector< std::pair<Matrix4x4, std::pair <int, int> > >temp;

	if (stackPointer < redoStack.size()){
		for (int i = 0; i< stackPointer; i++){
			temp.push_back(std::make_pair(redoStack[i].first,redoStack[i].second));
		}
		redoStack = temp;
		stackPointer = redoStack.size();
	}


	ChildList::const_iterator childIter;


	for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){
	
		(*childIter)->clearStack();	
		
	}
	
}

bool JointNode::pop(){

	if (stackPointer == 1){
		return 1;
	}

	else {
		m_trans = redoStack[stackPointer-2].first;
		//std::cout << m_trans <<std::endl;
		//std::cout << std::endl; 

		x_current = redoStack[stackPointer-2].second.first;
		y_current = redoStack[stackPointer-2].second.second;
	//	std::cout << "pop: " << m_joint_x.init << std::endl;

		stackPointer--;
		return 0;
	}

}

bool JointNode::load(){

	if (stackPointer == redoStack.size()){
		return 1;
	}



	else {
		m_trans = redoStack[stackPointer].first;
		x_current = redoStack[stackPointer].second.first;
		y_current = redoStack[stackPointer].second.second;
		stackPointer++;
		return 0;
	}

}

void JointNode::animate(int angle, char axis){

	if (selected) {
		//std::cout << m_name << std::endl;

		//std::cout << m_joint_x.min << " " << m_joint_x.init << " " << m_joint_x.max<< std::endl;

		//std::cout << (m_joint_x.min < m_joint_x.init+angle) << std::endl;
		//std::cout << (m_joint_x.init+angle < m_joint_x.max) << std::endl;




		
		if (axis == 'x'){

			if (m_joint_x.min < x_current+angle && x_current+angle < m_joint_x.max ){
					//std::cout << "moving" << std::endl;
				
				if (xAnimatable && yAnimatable) {
					//rotate('y', m_joint_y.init-y_current);

					x_current+=angle;
					rotate('x', angle);

					//rotate('y', -(m_joint_y.init-y_current));
				}

				else {
					x_current+=angle;
					rotate('x', angle);
				}
				
			}
		}

		else if (axis == 'y'){

			if (m_joint_y.min < y_current+angle && y_current+angle < m_joint_y.max ){
					//std::cout << "moving" << std::endl;
				
				if (xAnimatable && yAnimatable){
					rotate('x', m_joint_x.init-x_current);

					y_current+=angle;
					rotate('y', angle);

					rotate('x', -(m_joint_x.init-x_current));
				}

				else {
					y_current+=angle;
					rotate('y', angle);
				}
			}
		}

		
		ChildList::const_iterator childIter;

		for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){

			if (axis == 'x')(*childIter)->animate(angle, 'x');
			else if (axis == 'y')(*childIter)->animate(angle, 'y');

		}
	}

	else {
		ChildList::const_iterator childIter;

		for (childIter = m_children.begin(); childIter != m_children.end(); childIter++){

			if (axis == 'x')(*childIter)->animate(angle, 'x');
			else if (axis == 'y')(*childIter)->animate(angle, 'y');
		}
	}
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
	x_current = init;

	if (min == max) xAnimatable = false;
	else xAnimatable = true;	

	rotate('x', init);

	stackPointer = 0;

	//redoStack.clear();	
	//redoStack.push_back(m_trans);
	//stackPointer = redoStack.size();	
	
	selected = false;
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;
  m_joint_y.max = max;
	y_current = init;

	if (min == max) yAnimatable = false;
	else yAnimatable = true;	

	rotate('y', init);	

	stackPointer = 0;

	//redoStack.clear();	
	//redoStack.push_back(m_trans);	
	//stackPointer = redoStack.size();	

	selected = false;	
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
}

void GeometryNode::walk_gl(bool picking) const
{

	
	glPushMatrix();
	
	float matrix[16];
	int k = 0;
	for (int i = 0; i < 4; i++){
		Vector4D a =  m_trans.getColumn(i);
		for (int j = 0; j < 4; j++){
			matrix[k] = a[j];
			k++;
		}
	}
	glMultMatrixf(matrix);


	m_material->apply_gl(m_primitive->picked);
	glPushName(1);
	m_primitive->walk_gl(m_primitive->picked);

	glPopName();
	glPopMatrix();


	
  // Fill me in
}


void GeometryNode::pick(std::vector<int > names){

	//std::cout << "GEOMETRY NODE" << std::endl;

	
	if (m_primitive->picked){
		m_primitive->picked = false;
		selected = false;
	}

	else {
		m_primitive->picked = true;
		selected = true;
	}
			
	
	

}
 
