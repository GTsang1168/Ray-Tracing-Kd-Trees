#include "PhotonMapping.h"

PhotonMapping::PhotonMapping()
{

}

PhotonMapping::PhotonMapping(DataStructure *dataStructure)
{
	this->dataStructure = dataStructure;
}

PhotonMapping::~PhotonMapping()
{

}

void PhotonMapping::generatePhotonMapping(int rayAmount)
{
	vector<Light> lights = dataStructure->getLights();
	for(Light light: lights) {
		vector<Ray> photons = generatePhotons(light, rayAmount);
		for(Ray photon: photons) {
			calculatePhoton(photon, light.getColour());
		}
	}

	kdTree = KdTreePhoton(photonPoints);
	std::cout << "PhotonMapping::generatePhotonMapping() generated\n";
}

vector<PhotonPoint> PhotonMapping::getKNNPhoton(Point location, int k)
{
	return kdTree.getKNNPhoton(location, k);
}

void PhotonMapping::addPhoton(const PhotonPoint photon, const int index)
{
	if(index == -1) {
		photonPoints.push_back(photon);
	} else {
		photonPoints[index] = photon;
	}
}

vector<Ray> PhotonMapping::generatePhotons(const Light light, const int rayAmount)
{
	vector<Ray> photons;
	for(int amount = 0; amount < rayAmount; amount++) {
		double azimuth = 2 * PI * (std::rand() % 10000) / 10000;
		double u = 2 * (std::rand() % 10000) / 10000 - 1;
		double w = sqrt(1 - u * u);

		double x = w * cos(azimuth);
		double y = w * sin(azimuth);
		double z = abs(u);

		photons.push_back(Ray(light.getLocation(), Point(x, y, z)));
	}
	return photons;
}

void PhotonMapping::calculatePhoton(Ray photon, Colour light)
{
	vector<Intersection> intersections = dataStructure->getIntersection(photon);
	if(intersections.size() != 0) {
		double distance = intersections[0].getRayOriginDistance();
		int index = 0;
		for(int i = 0; i < intersections.size(); i++) {
			if(intersections[i].getRayOriginDistance() < distance) {
				distance = intersections[i].getRayOriginDistance();
				index = i;
			}
		}
		Intersection intersection = intersections[index];

		calculatePhotonIntersectionPath(photon, light, intersection);
	}
}

void PhotonMapping::calculatePhotonIntersectionPath(Ray photon, Colour light, Intersection intersection)
{
	Triangle * triangle = intersection.getPolygon();
	material_t material = dataStructure->getMaterial(triangle->getMaterial());

	Colour diffuseC = Colour(material.diffuse[0], material.diffuse[1], material.diffuse[2]);
	Colour remainingDiffuseC = Colour(1 - material.diffuse[0], 1 - material.diffuse[1], 1 - material.diffuse[2]);
	Colour specularC = Colour(material.specular[0], material.specular[1], material.specular[2]);
	Colour remainingSpecularC = Colour(1 - material.specular[0], 1 - material.specular[1], 1 - material.specular[2]);

	float diffuse = (material.diffuse[0] + material.diffuse[1] + material.diffuse[2]) / 3;
	float specular = (material.specular[0] + material.specular[1] + material.specular[2]) / 3;
	float transmit = material.dissolve;
	float absorb = 1;
	float reflectTotal = diffuse + specular + transmit + absorb;

	float pd = diffuse / reflectTotal;
	float ps = specular / reflectTotal;
	float pt = transmit / reflectTotal;

	float value = (std::rand() / (float) RAND_MAX);
	Colour remainingLight;

	if(value < pd) {
		remainingLight = light * (remainingDiffuseC);
		reflectPhoton(photon, light * diffuseC, intersection);
	} else if(value < ps + pd) {
		remainingLight = light * (remainingSpecularC);
		reflectPhoton(photon, light * specularC, intersection);
	} else if(value < pt + ps + pd) {
		remainingLight = light * (remainingDiffuseC);
		refractPhoton(photon, light * diffuseC, intersection);
	}

	addPhoton(PhotonPoint(intersection.getIntersection(), remainingLight));
}

void PhotonMapping::reflectPhoton(Ray photon, Colour light, Intersection intersection)
{
	Vector originVector = Vector::normalize(photon.getOriginPoint() - photon.getEndPoint());
	Vector normal = intersection.getPolygon()->getNormal();
	double aoi = normal.dot(originVector);
	Vector reflectionVector = originVector - (normal * (2 * aoi));
	Ray reflectionPhoton(intersection.getIntersection(), intersection.getIntersection() - reflectionVector);
	calculatePhoton(reflectionPhoton, light);
}

void PhotonMapping::refractPhoton(Ray photon, Colour light, Intersection intersection)
{
	Vector originVector = Vector::normalize(photon.getOriginPoint() - photon.getEndPoint());
	Vector normal = intersection.getPolygon()->getNormal();
	double ior = dataStructure->getMaterial(intersection.getPolygon()->getMaterial()).ior;
	double aoi = normal.dot(originVector);

	if (aoi < 0) {
		ior = 1 / ior;
	}
	double sqrt = 1 - (ior*ior * (1 - aoi*aoi));

	if (sqrt >= 0) {
		Vector refractionVector;

		if (aoi >= 0) {
			refractionVector = normal * (ior * (aoi) - std::sqrt(sqrt)) - originVector * ior;
		} else {
			refractionVector = normal * (ior * (aoi) + std::sqrt(sqrt)) - originVector * ior;
		}

		Ray refractionPhoton(intersection.getIntersection(), intersection.getIntersection() + refractionVector);
		calculatePhoton(refractionPhoton, light);
	} else {
		reflectPhoton(photon, light, intersection);
	}
}
