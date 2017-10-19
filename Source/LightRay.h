/**
\class LightRay
\brief Projects a defined ray of "light" and calculates the resulting intensity value.

This class generates a ray of light defined via two Point classes using the newRay method. Then using the DataStructure class paramter which
was indicated at construction of this class, the intersection point is located and the intensity values then calculated. This class can
recursively call itself to generate newly spawned rays in order to generate a realistic image.

Due to the DataStructure paramater, this class is meant as a semi-static class where after construction, only this specific DataStructure
model will be used to calculate ray intensities. The Ray Tracing of other models will require the construction of a new LightRay class with
the new DataStructure class as the paramater.

\author Gavin Tsang
\date 16/02/2015
*/

#pragma once
#include <iostream>
#include <string>
#include <algorithm>

#include "DataStructure.h"
#include "Ray.h"
#include "LightPoint.h"
#include "RenderOptions.h"
#include "PhotonMapping.h"
#define PI 3.14159265

#define MAXLEVEL 10
#define LIGHT_FACTOR_A 10 //0
#define LIGHT_FACTOR_B 0 //8
#define LIGHT_FACTOR_C 0 //2

using namespace std;

class LightRay {
public:
	LightRay();
	LightRay(DataStructure * dataStructure, RenderOptions * renderOptions);
	
	Colour newRay(Ray ray, int level);
private:
	DataStructure * dataStructure;

	struct LightStructure {
		LightStructure();
		LightStructure(Light light, double distanceModifier, Vector lightVector, Vector halfwayVector, double aoi);
		Light light;
		double dissolveTotal;
		double distanceModifier;
		Vector lightVector;
		Vector halfwayVector;
		double aoi;
	};

	struct Calculations {
		Point originPoint;
		Point intersectionPoint;
		Vector originVector;
		Vector normal;
		vector<LightStructure> unobstructedLights;
		material_t material;
		double aoi;
		int depth;
	};

	Colour calculateColour(Calculations calculations);
	Colour calculateVectors(Intersection intersection, Ray originRay, int depth);
	Colour calculateCollision(Intersection intersection, Ray originRay, int depth);
	Colour calculateReflection(Calculations calculations);
	Colour calculateRefraction(Calculations calculations);
	Colour calculateGlobalIllumination(Calculations calculations);

	RenderOptions * renderOptions;
	PhotonMapping photonMapping;
};
