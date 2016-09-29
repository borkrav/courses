class Probe {
	
	public:

	Probe() : t(std::numeric_limits<double>::max()) {}

	Probe(double t, Vector3D normal, Point3D intersection, PhongMaterial *hit) : t(t), normal(normal), intersection(intersection), hit(hit) {}

	PhongMaterial *hit;
	double t;
	Vector3D normal;
	Point3D intersection;	

};
