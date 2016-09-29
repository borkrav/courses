#ifndef CS488_MATERIAL_HPP
#define CS488_MATERIAL_HPP

#include "algebra.hpp"

class Material {
	public:
		virtual ~Material();
		virtual bool isPhong();
	  virtual bool isTransparent();

	protected:
		Material()
		{
		}
};


class PhongMaterial : public Material {


public:

  PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflect, double blur);

  virtual ~PhongMaterial();
	bool isPhong();
	bool isTransparent();
  Colour m_kd;
  Colour m_ks;
	double m_reflect;
  double m_shininess;
	double m_blur;
};

class TransparentMaterial : public Material {

public:

  TransparentMaterial(const Colour& kd, double refract, double opacity, double blur);

  virtual ~TransparentMaterial();
	bool isPhong();
	bool isTransparent();
  Colour m_kd;
	double m_refract;
  double m_opacity;
	double m_blur;
};


#endif
