#include "primitive.hpp"

static GLuint listIndex;

Primitive::~Primitive()
{
}

Sphere::~Sphere()
{
}


static void render(int tess){

	if (listIndex == NULL){

		listIndex = glGenLists(1);
	
		glNewList(listIndex, GL_COMPILE);

			GLUquadric *quad = gluNewQuadric();

			gluSphere(quad, 1, tess, tess);
		glEndList();
	
		glCallList(listIndex);
	}

	else glCallList(listIndex);

}

void Sphere::walk_gl(bool picking) const
{

	//std::cout << picking;

	render(50);

  
}
