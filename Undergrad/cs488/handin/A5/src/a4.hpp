#ifndef CS488_A4_HPP
#define CS488_A4_HPP

#include <string>
#include "algebra.hpp"
#include "scene.hpp"
#include "light.hpp"
#include <pthread.h>
#include <vector>


struct arguments{
	std::vector<Ray>* rays;
	SceneNode* root;
	std::vector<Light*>* lights;
	Colour* ambient;
	int id;
};


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
               );

void intersectRays(int numberThreads, SceneNode* root, std::vector<std::vector<Ray>* > rays, std::vector<Light*>* lights, Colour *ambient);

Colour raytrace(Ray ray, arguments *args);




#endif
