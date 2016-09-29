#include "material.hpp"

Material::~Material()
{
}

bool Material::isPhong(){
	return false;
}
bool Material::isTransparent(){
	return false;
}


PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflect, double blur)
  : m_kd(kd), m_ks(ks), m_shininess(shininess), m_reflect(reflect), m_blur(blur)
{
}

PhongMaterial::~PhongMaterial()
{
}

bool PhongMaterial::isPhong(){
	return true;
}
bool PhongMaterial::isTransparent(){
	return false;
}


TransparentMaterial::TransparentMaterial(const Colour& kd, double refract, double opacity, double blur)
  : m_kd(kd), m_refract(refract), m_opacity(opacity), m_blur(blur)
{
}

TransparentMaterial::~TransparentMaterial()
{
}

bool TransparentMaterial::isPhong(){
	return false;
}
bool TransparentMaterial::isTransparent(){
	return true;
}



