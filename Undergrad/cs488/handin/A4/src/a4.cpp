#include "a4.hpp"
#include "image.hpp"
#include "ray.hpp"
//#include "probe.hpp"
#include <utility>

using namespace std;

extern int threads;
pthread_mutex_t lock;
vector<int> progress;


struct arguments{
	vector<Ray>* rays;
	SceneNode* root;
	vector<Light*>* lights;
	Colour* ambient;
	int id;
};

void *threadIntersect( void *ptr );


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
               const std::list<Light*>& lights
               )
{
  // Fill in raytracing code here.

  srand (time(NULL));


	//root->precompute(Matrix4x4());

	vector<vector<Ray>* > rays = vector<vector <Ray>* >(threads);

	progress = vector<int>(threads);
	fill (progress.begin(), progress.end(), 0);

	for (int i = 0; i< threads; i++){
		rays[i] = new vector<Ray>;
	}

	Vector3D myView = view;
	Vector3D myUp = up;

	myView.normalize();
	myUp.normalize();


	Vector3D right = myUp.cross(myView);

	int threadIndex = 0;
	//int counter = 0;

	for (int i = height; i > 0; i--){
		for (int j = width; j > 0; j--){
			

			rays[threadIndex]->push_back(Ray(eye, 
					myView + ((float)j/(float)width*2 - 1)*((fov/2)/180*M_PI)*1*right + 
								 ((float)i/(float)height*2-1)*((fov/2)/180*M_PI)*myUp));

			//counter++;
			threadIndex++;

			//if (threadIndex != threads-1 && counter == width*height/threads){
			//	counter = 0;
			//	threadIndex++;
			//}

			if (threadIndex == threads){
				threadIndex = 0;
			}

		}	
	}

	vector<Light*> *visibleLights = new vector<Light*>();

	for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I){
		visibleLights->push_back(*I);
	}

//	std::cerr << "Running with " << threads << " threads" << std::endl;

	Colour *ambientLight = new Colour(ambient);

	intersectRays(threads, root, rays, visibleLights, ambientLight);


/*
  std::cerr << "Stub: a4_render(" << root << ",\n     "
            << filename << ", " << width << ", " << height << ",\n     "
            << eye << ", " << view << ", " << up << ", " << fov << ",\n     "
            << ambient << ",\n     {";

  for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I) {
    if (I != lights.begin()) std::cerr << ", ";
    std::cerr << **I;
  }
  std::cerr << "});" << std::endl;
  */

  Image img(width, height, 3);	

	threadIndex = 0;
	int counter = 0;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < height; x++) {

			Colour col = (*(rays[threadIndex]))[counter].colour;

			img(x, y, 0) = col.R();
			img(x, y, 1) = col.G();
			img(x, y, 2) = col.B();
		
			//counter++;
			threadIndex++;

			if (threadIndex == threads){
				counter++;
				threadIndex = 0;
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


void *threadIntersect( void *ptr )
{

	double epsilon = pow(10, -10);

	arguments *args = (arguments*)ptr;

	int printCounter = args->rays->size()/100;

	for (int i = 0; i < args->rays->size(); i++){


		if (printCounter == 0){

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
		
		Probe result = args->root->intersect(*ray);

		if (result.t != std::numeric_limits<double>::max()){
		//ray hit something, find the colour at that spot	

	//	ray->colour = (result.hit->m_kd);
		
		
		Colour ambientTerm = *(args->ambient)*(result.hit->m_kd);
		Colour diffuseTerm = (result.hit->m_kd);
		Colour specularTerm = (result.hit->m_ks);

		Colour diffuseLightTerms = Colour(0,0,0);
		Colour specularLightTerms = Colour(0,0,0);
		
		bool inShadow = true;

			for (int j = 0; j < args->lights->size(); j++){

				Light *light = (*(args->lights))[j];
				//Point3D intersection = ray->eyePoint + ((ray->t)-0.00001)*(ray->directionVector);
				Point3D intersection = result.intersection;
				Vector3D lightVector = light->position - intersection;
				Ray shadow = Ray(intersection, lightVector);
				
				Probe shadowResult = args->root->intersect(shadow);
				
				if (!(shadowResult.t != std::numeric_limits<double>::max() && shadowResult.t > epsilon)){
					//The light is visible from here, do lighting calculation

					if (inShadow) inShadow = false;

					result.normal.normalize();

					Vector3D reflectVector = -lightVector 
									+ 2*(lightVector.dot(result.normal))*result.normal;
					Vector3D eyeVector = ray->eyePoint - intersection;
							
					eyeVector.normalize();
					reflectVector.normalize();
					lightVector.normalize();
						

					diffuseLightTerms = diffuseLightTerms + (light->colour)*(lightVector.dot(result.normal));
					
					specularLightTerms = specularLightTerms + (light->colour)
																*pow(reflectVector.dot(eyeVector), result.hit->m_shininess);

					
				}
			}
			if (!inShadow) ray->colour = ambientTerm + 
													diffuseTerm*diffuseLightTerms + 
													specularTerm*specularLightTerms;	
			else ray->colour = ambientTerm;
		}
		else {
			//ray->colour = Colour(abs(ray->directionVector[1])*3, abs(ray->directionVector[1])*3, 0);

			int random = rand() % 200 + 1;

			if (random == 1) ray->colour = Colour(1,1,1);
			else ray->colour = Colour(0,0,0);

		}
	}
}
