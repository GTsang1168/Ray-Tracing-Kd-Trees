#ifndef PHOTONMAPPING_H
#define PHOTONMAPPING_H

#include <vector>
#include <iostream>

#include "DataStructure.h"
#include "LightPoint.h"
#include "Vector.h"
#include "Triangle.h"
#include "Point.h"
#include "Ray.h"
#include "PhotonPoint.h"
#include "tiny_obj_loader.h"
#include "KdTreePhoton.h"

#define DEFAULT_RAY_COUNT 100000
#define PI 3.14159265

class PhotonMapping
{
public:
    PhotonMapping();
	PhotonMapping(DataStructure *dataStructure);
    ~PhotonMapping();

	void generatePhotonMapping(int rayAmount = DEFAULT_RAY_COUNT);

	vector<PhotonPoint> getKNNPhoton(Point location, int k);

private:
	void addPhoton(const PhotonPoint photon, const int index = -1);
	vector<Ray> generatePhotons(const Light light, const int rayAmount);
	void calculatePhoton(Ray photon, Colour light);
	void calculatePhotonIntersectionPath(Ray photon, Colour light, Intersection intersection);

	void reflectPhoton(Ray photon, Colour light, Intersection intersection);
	void refractPhoton(Ray photon, Colour light, Intersection intersection);

	vector<PhotonPoint> photonPoints;

	DataStructure * dataStructure;
	KdTreePhoton kdTree;
};

#endif // PHOTONMAPPING_H
