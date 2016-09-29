#include "material.hpp"

Material::~Material()
{
}

PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks, double shininess)
  : m_kd(kd), m_ks(ks), m_shininess(shininess)
{
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::apply_gl(bool picked) const
{

	GLfloat diffuse[3];
  GLfloat specular[3] = {m_ks.R(), m_ks.G(), m_ks.B()};
  GLfloat shininess[1] = {m_shininess };

	if (!picked){
		diffuse[0] = m_kd.R();
		diffuse[1] = m_kd.G();
		diffuse[2] = m_kd.B(); 
	}

	else {
		diffuse[0] = 0.5;
		diffuse[1] = 0.5;
		diffuse[2] = 0.5; 
	}

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	
  // Perform OpenGL calls necessary to set up this material.
}
