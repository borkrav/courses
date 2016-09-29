#include "a4.hpp"
#include "image.hpp"
#include "ray.hpp"
#include <assert.h>
#include <utility>

using namespace std;

int ssfactor;		
int disfactor;	
int SSAA;
int doffactor;
double apeture;
double focalLen;
extern int threads;
pthread_mutex_t lock;
vector<int> progress;

float pixelSizeX = 0;
float pixelSizeY = 0;
int rwidth = 0;
int rheight = 0;
Vector3D gView;
Vector3D gUp;
Vector3D gRight;

void *threadIntersect( void *ptr );

double epsilon = pow(10, -10);

void a4_render(// What to render
               SceneNode* root,
               // Where to output the image
               const std::string& filename,
               // Image size
               int width, int height,
               // Viewing parameters
               const Point3D& eye, const Vector3D& view,
               const Vector3D& up, double fov,
               // Lighting parameters
               const Colour& ambient,
               const std::list<Light*>& lights,
							 int ssaa,
							 int ssFactor,
							 int disFactor,
							 double apetureSize,
							 double focalLength,
							 int dofFactor
               )
{

  srand (time(NULL));

	apeture = apetureSize;
	focalLen = focalLength;
	doffactor = dofFactor;
	SSAA = ssaa;
	ssfactor = ssFactor;
	disfactor = disFactor;
	//root->precompute(Matrix4x4());

	rwidth = width;
	rheight = height;
	
	if (SSAA){
		rwidth*=2;
		rheight*=2;
	}


	vector<vector<Ray>* > rays = vector<vector <Ray>* >(threads);

	progress = vector<int>(threads);
	fill (progress.begin(), progress.end(), 0);

	for (int i = 0; i< threads; i++){
		rays[i] = new vector<Ray>;
	}

	//pixelSizeX = tan(fov*M_PI/180)/width;
	//pixelSizeY = tan(fov*M_PI/180)/height;


	gView = view;
	gUp = up;

	gView.normalize();
	gUp.normalize();


	gRight = gUp.cross(gView);

	int threadIndex = 0;

	for (int i = rheight; i > 0; i--){
		for (int j = rwidth; j > 0; j--){
			

			rays[threadIndex]->push_back(Ray(eye, 
					gView + ((float)j/(float)rwidth*2 - 1)*((fov/2)/180*M_PI)*1*gRight + 
								 ((float)i/(float)rheight*2-1)*((fov/2)/180*M_PI)*gUp));

			threadIndex++;

			if (threadIndex == threads){
				threadIndex = 0;
			}

		}	
	}

	vector<Light*> *visibleLights = new vector<Light*>();

	for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I){
		visibleLights->push_back(*I);
	}


	Colour *ambientLight = new Colour(ambient);

	intersectRays(threads, root, rays, visibleLights, ambientLight);


	Ray* rgbValues[rwidth][rheight]; 

	threadIndex = 0;
	int counter = 0;

	for (int i = 0; i < rheight; i++){
		for (int j = 0; j < rwidth; j++){
			rgbValues[i][j] = &(*(rays[threadIndex]))[counter];
			threadIndex++;

			if (threadIndex == threads){
				counter++;
				threadIndex = 0;
			}
		}
	}



	Image img(width, height, 3);	

	if (!SSAA){
 	 for (int y = 0; y < rheight; y++) {
    	for (int x = 0; x < rwidth; x++) {
				Colour col = rgbValues[y][x]->colour;
				img(x, y, 0) = col.R();
				img(x, y, 1) = col.G();
				img(x, y, 2) = col.B();
			}
		}
	}

	else if (SSAA){

		for (int y = 0; y < rheight-1; y+=2) {
    	for (int x = 0; x < rwidth-1; x+=2) {

				Colour col = rgbValues[y][x]->colour*0.25 + rgbValues[y][x+1]->colour*0.25 +
							rgbValues[y+1][x]->colour*0.25 + rgbValues[y+1][x+1]->colour*0.25;

				img(x/2, y/2, 0) = col.R();
				img(x/2, y/2, 1) = col.G();
				img(x/2, y/2, 2) = col.B();
			}
		}
	}


  img.savePng(filename);


	for (int i = 0; i< threads; i++){
		delete rays[i];
	} 
	
	delete visibleLights;
	delete ambientLight;

  
}


void intersectRays(int numberThreads, SceneNode* root, vector<vector<Ray>* > rays, vector<Light*>* lights, Colour *ambient){

	vector<arguments*> myArgs = vector<arguments*>(numberThreads);

	for (int i = 0; i < numberThreads; i++){
		myArgs[i] = new arguments{rays[i], root, lights, ambient, i};
	}


	pthread_mutex_init(&lock, NULL);
	vector<pthread_t> threads = vector<pthread_t>(numberThreads);
	vector<int> retVals = vector<int>(numberThreads);

	for (int i = 0; i < numberThreads; i++){
		retVals[i] = pthread_create( &(threads[i]), NULL, threadIntersect, myArgs[i]);
	}

	for (int i = 0; i < numberThreads; i++){
		 pthread_join( threads[i], NULL);
	}

	for (int i = 0; i < numberThreads; i++){
		 delete myArgs[i];
	}
}



bool isInShadow(SceneNode* root, Point3D position, Point3D intersection, Light* light){

	Vector3D lightVector = position - intersection;
	Ray shadow = Ray(intersection, lightVector);

	double distance = sqrt (pow(position[0] - intersection[0], 2) + 
															pow(position[1] - intersection[1], 2) + 
															pow(position[2] - intersection[2], 2));

	double length = sqrt(pow(lightVector[0], 2) + 
											 pow(lightVector[1], 2) + 
											 pow(lightVector[2], 2));

	double t = distance/length;

	Point3D testPoint = shadow.eyePoint + (t)*shadow.directionVector;

	assert(testPoint[0] <= position[0] + epsilon && 
				 testPoint[1] <= position[1] + epsilon &&
				 testPoint[2] <= position[2] + epsilon);

	Probe shadowResult = root->intersect(shadow);

	//ignores the shadows of refractive objects (for now?) 
	while (shadowResult.t < t && shadowResult.hit->isTransparent() &&
				 shadowResult.t > epsilon){
		Point3D inter = shadow.eyePoint 
			+ (shadowResult.t+epsilon)*shadow.directionVector;
		Vector3D lv = light->position - inter;
		shadow.bend(inter,lv);
		shadowResult = root->intersect(shadow);
	}

	if (!(shadowResult.t < t && shadowResult.t > epsilon)) return true;
	else return false;

}


int getShadowHitCount(int ssfactor, Point3D intersection, SceneNode* root, Light* light){


	int hitCount = 0;

	double ss = ssfactor;	
	Point3D position = light->position;

	Vector3D up = light->normal.cross(light->left);
	up.normalize();

	Point3D c1 = light->position - 
							 (light->area[0]/2)*light->left - 
							 (light->area[1]/2)*up;	 

	double factorW = light->area[0]/ss;
	double factorH = light->area[1]/ss;

	double offsetW = (double)(rand() % 32)/32;
	double offsetH = (double)(rand() % 32)/32;

	for (int i = 0; i < ssfactor; i++){
		for (int j = 0; j < ssfactor; j++){

			position = c1 + (factorW*(i+offsetW))*light->left +
											(factorH*(j+offsetH))*up;
			
			if(isInShadow(root, position, intersection, light)) hitCount++;

		}
	}

	return hitCount;

}

Colour calculateColour (vector<Light*>* lights, Probe result, SceneNode *root, Ray ray, Colour ambient){

	//if (result.t != std::numeric_limits<double>::max()){
		//ray hit something, find the colour at that spot	

		Colour ambientTerm = ambient*(((PhongMaterial*)result.hit)->m_kd);
		Colour diffuseTerm = (((PhongMaterial*)result.hit)->m_kd);
		Colour specularTerm = (((PhongMaterial*)result.hit)->m_ks);

		Colour diffuseLightTerms = Colour(0,0,0);
		Colour specularLightTerms = Colour(0,0,0);

		for (int j = 0; j < lights->size(); j++){

			Light *light = (*(lights))[j];
		

			Point3D intersection = result.intersection;
			Vector3D lightingVector = light->position - intersection;

			int hitCount = 0;
			double shadowAmount;

			if (ssfactor == 0) { 
				if (isInShadow(root, light->position, intersection, light)) hitCount = 1;
				else hitCount = 0;
				
				shadowAmount = hitCount;
			}

			else {
					hitCount = getShadowHitCount(ssfactor, intersection, root, light);
					shadowAmount = (double)hitCount/(ssfactor*ssfactor);
			}	


			if (shadowAmount != 0){
				result.normal.normalize();

				Vector3D reflectVector = -lightingVector 
								+ 2*(lightingVector.dot(result.normal))*result.normal;
				Vector3D eyeVector = ray.eyePoint - intersection;
						
				eyeVector.normalize();
				reflectVector.normalize();
				lightingVector.normalize();
					

				diffuseLightTerms = diffuseLightTerms + 
				shadowAmount*((light->colour)*(lightingVector.dot(result.normal)));
				
				specularLightTerms = specularLightTerms + shadowAmount*((light->colour)
															*pow(reflectVector.dot(eyeVector),
																	 ((PhongMaterial*)result.hit)->m_shininess));

			}
		}


		return ambientTerm + diffuseTerm*diffuseLightTerms +
					 specularTerm*specularLightTerms;
	
}




Colour distribute(Ray r, arguments *args, double blur){

	if (blur == 0 || r.distributed || disfactor == 0) return raytrace(r, args);

	double red = 0;
	double green = 0;
	double blue = 0;

	int sampleSize = disfactor;
		
	double size = blur*0.005;

	Vector3D vect = r.directionVector;

  double z = (vect[0]*1 + vect[1]*0)/-vect[2];

	assert (vect[2] != 0);

	Vector3D left = Vector3D(1,0,z);

	Vector3D up = vect.cross(left);
	

	left.normalize();
	up.normalize();
	vect.normalize();

	Point3D inter = r.eyePoint + 0.1*vect;
	
	Point3D c1 = inter - size/2*left - size/2*up;
	
	for (int i = 0; i < sampleSize; i++){
		for (int j = 0; j < sampleSize; j++){

			double factor = size/sampleSize;
		
			double offsetW = (double)(rand() % 32)/32;
			double offsetH = (double)(rand() % 32)/32;

			Point3D destination = c1 + (factor*(i+offsetW))*left +
												(factor*(j+offsetH))*up;



			Vector3D dir = destination - r.eyePoint;
	
			Ray ray = r;
			ray.distributed = true;
		
			ray.bend(ray.eyePoint, dir);

			Colour result = raytrace(ray, args);

			red += result.R();
			green += result.G();
			blue += result.B();



		}
	}

	red = red/(sampleSize*sampleSize);
	green = green/(sampleSize*sampleSize);
	blue = blue/(sampleSize*sampleSize);

	return Colour(red,green,blue);
	

}




Colour raytrace(Ray ray, arguments *args){

	//background colour
	Colour col = Colour(0,0,0);

	double lightT = std::numeric_limits<double>::max();


	for (int j = 0; j < args->lights->size(); j++){
		Light *light = (*(args->lights))[j];
		double result = light->intersect(ray);
		if (result < lightT)
			col =  light->colour;
			lightT = result;
	}

	//do intersection	
	Probe result = args->root->intersect(ray);

	if (result.t < pow(10, -5) || ray.bendCount > 10) return col;

	//if I hit a phong surface, do colour calculation
	if (result.t < lightT && result.hit->isPhong()){
		col = calculateColour(args->lights, result, args->root, ray, *(args->ambient));

		//if my phong surfrace is reflective, cast reflections ray
		if (((PhongMaterial*)result.hit)->m_reflect != 0){
			Point3D i = result.intersection;
			Vector3D d = ray.directionVector;
			Vector3D n = result.normal;
			n.normalize();
			Vector3D r = d - 2*(d.dot(n))*n;

			ray.bend(i,r);
			double blur = ((PhongMaterial*)result.hit)->m_blur;

			col = col + distribute(ray, args, blur)
									*((PhongMaterial*)result.hit)->m_reflect;
			
		}

	}
	//if ray has been bounced more then 10 times, stop. Image is good enough



	//if my surface is refractive, cast refraction ray
	if (result.t < lightT && result.hit->isTransparent()){
		double index = ((TransparentMaterial*)result.hit)->m_refract;
		double nr = 0;
		double n1 = 0;
		double n2 = 0;
		double opacity = ((TransparentMaterial*)result.hit)->m_opacity;
		Colour diffuse = ((TransparentMaterial*)result.hit)->m_kd;
		double blur = ((TransparentMaterial*)result.hit)->m_blur;

		Vector3D l = ray.directionVector;
		Point3D inter = ray.eyePoint + (result.t+epsilon)*l;
		Vector3D n = result.normal;
		n.normalize();
		l.normalize();

		if (((TransparentMaterial*)result.hit)->m_refract == 1){
				ray.bend(inter,l);
				col = distribute(ray, args, blur);
		}

		else {


			if (ray.refrIndex.top() != index){
				//entering a new medium
				n1 =  ray.refrIndex.top();
				n2 = index;
				ray.refrIndex.push(index);	
				
			}

			else if (ray.refrIndex.top() == index){
				//leaving the medium
				ray.refrIndex.pop();
				n1 = index;
				n2 = ray.refrIndex.top();
			}

			nr = n1/n2;

			double costhetai = n.dot(-l);
			double expression = 1 - pow(nr,2)*(1-pow(costhetai, 2));
			double costhetat = sqrt(expression);

			if (expression >= 0){			
				//refraction && reflection

				//fresnel's equation

				double rs = pow(((n1*costhetai - n2*costhetat)/
												 (n1*costhetai + n2*costhetat)),2);

				double rp = pow(((n2*costhetai - n1*costhetat)/
												 (n2*costhetai + n1*costhetat)),2);

				double reflectance = (rs+rp)/2;

				//throw anything out of range out
				if (reflectance > 1 || reflectance < 0) reflectance = 0;

				double transmittance = 1 - reflectance;

				Point3D ri = result.intersection;
				Vector3D rd = ray.directionVector;
				Vector3D refl = rd - 2*(rd.dot(n))*n;		

				Ray reflection = ray;
				reflection.bend(ri, refl);		


				if (costhetai > 0){	
					Vector3D t = nr*l + (nr*costhetai - costhetat)*n;
					ray.bend(inter,t);
					col = reflectance*(col + 
							distribute(reflection, args, blur)) + 
								diffuse*(1-opacity) + opacity*transmittance*(col + 
							distribute(ray, args, blur));
				}


				else if (costhetai <= 0){
					Vector3D t = nr*l - (nr*costhetai - costhetat)*n;
					ray.bend(inter,t);
					col = reflectance*(distribute(reflection, args, blur)) + 
								diffuse*(1-opacity) + opacity*transmittance*(col + 
							distribute(ray, args, blur));
				}

			}

			else if (expression < 0) {
				//total internal reflection
				ray.refrIndex.push(index);
				Point3D i = result.intersection;
				Vector3D d = ray.directionVector;
				Vector3D r = d - 2*(d.dot(n))*n;
				ray.bend(i,r);
				col = diffuse*(1-opacity) + opacity*col + 
							distribute(ray, args, blur);
			}
		}

		


	}


	//if my surface is reflective, cast reflection ray


	return col;


}

Colour depthOfField(Ray ray, arguments *args){

	double red = 0;
	double green = 0;
	double blue = 0;

	ray.directionVector.normalize();



	Point3D focalPlanePoint = ray.eyePoint + focalLen*gView;

	Point3D imagePlanePoint = ray.eyePoint + 0.01*gView;

	double t = ((imagePlanePoint-ray.eyePoint).dot(gView))/
						 (ray.directionVector.dot(gView));

	Point3D pixelPoint = ray.eyePoint + t*ray.directionVector;

	t = ((focalPlanePoint-pixelPoint).dot(gView))/
			(ray.directionVector.dot(gView));


	Point3D focalPoint = pixelPoint + t*ray.directionVector;

	Point3D c1 = pixelPoint - apeture/2*gRight - apeture/2*gUp;


	for (int i = 0; i < doffactor; i++){
		for (int j = 0; j < doffactor; j++){

			double factor = apeture/doffactor;
		
			double offsetW = (double)(rand() % 32)/32;
			double offsetH = (double)(rand() % 32)/32;
			//double offsetW = 0.5;
			//double offsetH = 0.5;

			Point3D destination = c1 + (factor*(i+offsetW))*gRight +
																 (factor*(j+offsetH))*gUp;

			Vector3D dofDir = focalPoint - destination;

			Ray dofProbe = ray;

			dofProbe.bend(destination, dofDir);
	

			Colour result = raytrace(dofProbe, args);

			red += result.R();
			green += result.G();
			blue += result.B();

		}
	}
 	
	red = red/(doffactor*doffactor);
	green = green/(doffactor*doffactor);
	blue = blue/(doffactor*doffactor);

	return Colour(red,green,blue);

}

void *threadIntersect(void *ptr) {


	arguments *args = (arguments*)ptr;

	int printCounter = args->rays->size()/100;

	for (int i = 0; i < args->rays->size(); i++){


		//print current progress
		if (printCounter == 0){

			cout << rwidth << "x" << rheight << " ";
			if (SSAA) cout << "(SSAA) ";
			cout << ssfactor*ssfactor << "x Soft Shadows, ";
			cout << disfactor*disfactor << "x Distribution, ";
			cout << doffactor*doffactor << "x DOF"<< endl;
			

			cout << "Rendering with " << progress.size() << " threads:" << endl;

		  pthread_mutex_lock(&lock);
			progress[args->id] = ((double)i/args->rays->size())*100+1;

			for (int i = 0; i < progress.size(); i++){
				cout << "Thread " << i << ": " << progress[i] << endl;
			}

	
		  pthread_mutex_unlock(&lock);

			printCounter = args->rays->size()/100;
		}

		printCounter--;		

		Ray *ray = &(*(args->rays))[i];	

		//the medium the ray starts off traveling in is air
		ray->refrIndex.push(1);		

		if (doffactor != 0) ray->colour = depthOfField(*ray, args);
		else ray->colour = raytrace(*ray, args);	

	}
}
