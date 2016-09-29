class Probe {
	
	public:

	Probe() : t(std::numeric_limits<double>::max()) {}

	Probe(double t, Vector3D normal, Point3D intersection, Material *hit) : t(t), normal(normal), intersection(intersection), hit(hit), use(false) {}

	Material *hit;
	double t;
	Vector3D normal;
	Point3D intersection;	
	bool use;

};
