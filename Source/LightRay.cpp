#include "LightRay.h"

LightRay::LightRay() {}

LightRay::LightRay(DataStructure * dataStructure, RenderOptions * renderOptions) {
    this->dataStructure = dataStructure;
	this->renderOptions = renderOptions;
	photonMapping = PhotonMapping(dataStructure);
}

Colour LightRay::newRay(Ray ray, int depth) {
	vector<Intersection> intersections = dataStructure->getIntersection(ray);
	vector<IntersectionLine> intersectionLines;

	if(renderOptions->getViewKdTree() && depth == 0) {
		intersectionLines = dataStructure->getIntersectionLine(ray);
	}

	double min = HUGE_VALD;
	int minLocation = 0;
	bool lineClosest = false;

	if (intersections.size() != 0) {
		min = intersections[0].getRayOriginDistance();
		for (int i = 0; i < intersections.size(); i++) {
			if (intersections[i].getRayOriginDistance() < min) {
				min = intersections[i].getRayOriginDistance();
				minLocation = i;
				lineClosest = false;
			}
		}
	}

	if (intersectionLines.size() != 0) {
		for (IntersectionLine intersectionLine: intersectionLines) {
			if (intersectionLine.getIntDistance() < min) {
				min = intersectionLine.getIntDistance();
				lineClosest = true;
			}
		}
	}

	if (intersections.size() == 0 && intersectionLines.size() == 0) {
		return Colour(0, 0, 0);
	} else if (lineClosest) {
		return Colour(1, 1, 0);
	} else {
		return calculateCollision(intersections[minLocation], ray, depth);
	}
}

Colour LightRay::calculateCollision(Intersection intersection, Ray originRay, int depth) {
	if (depth <= MAXLEVEL && renderOptions->getPhong()) {
		return calculateVectors(intersection, originRay, depth);
	} else {
		double r = dataStructure->getMaterial(intersection.getPolygon()->getMaterial()).diffuse[0];
		double g = dataStructure->getMaterial(intersection.getPolygon()->getMaterial()).diffuse[1];
		double b = dataStructure->getMaterial(intersection.getPolygon()->getMaterial()).diffuse[2];

		return Colour(r, g, b);
	}
}

Colour LightRay::calculateVectors(Intersection intersection, Ray originRay, int depth) {
	Calculations calculations;

	calculations.depth = depth;
	calculations.material = dataStructure->getMaterial(intersection.getPolygon()->getMaterial());
	calculations.originPoint = originRay.getOriginPoint();
	calculations.intersectionPoint = intersection.getIntersection();
	calculations.originVector = Vector::normalize(calculations.originPoint - calculations.intersectionPoint);
	calculations.normal = Vector::normalize(intersection.getPolygon()->getNormal());

	calculations.aoi = calculations.normal.dot(calculations.originVector);
	//Get correctly facing normal

	for (int i = 0; i < dataStructure->getLights().size(); i++) {
		Light light = dataStructure->getLights()[i];
		vector<Intersection> lightIntersections = dataStructure->getIntersection(Ray(calculations.intersectionPoint, light.getLocation()));

		double dissolveTotal = 1;
		for (Intersection lightIntersection : lightIntersections) {
			if (lightIntersection.getRayOriginDistance() < 1.0) {
				dissolveTotal *= (1 - dataStructure->getMaterial(lightIntersection.getPolygon()->getMaterial()).dissolve);
			}
		}

		if (dissolveTotal != 0) {
			LightStructure lightStructure;
			lightStructure.light = light;
			lightStructure.dissolveTotal = dissolveTotal;
			lightStructure.lightVector = Vector::normalize(light.getLocation() - calculations.intersectionPoint);
			lightStructure.halfwayVector = Vector::normalize(lightStructure.lightVector + calculations.originVector);
			lightStructure.aoi = std::fmax(lightStructure.lightVector.dot(calculations.normal), 0.0);
			/*************************NEED TO WORK OUT NORMALIZED DIATANCES INSTEAD OF ABSOLUTE ATM*******/
			double xd = light.getLocation().getX() - intersection.getIntersection().getX();
			double yd = light.getLocation().getY() - intersection.getIntersection().getY();
			double zd = light.getLocation().getZ() - intersection.getIntersection().getZ();
			double distance = sqrt(xd*xd + yd*yd + zd*zd);
			lightStructure.distanceModifier = 10 /
				(LIGHT_FACTOR_A +
				LIGHT_FACTOR_B * distance +
				LIGHT_FACTOR_C * distance * distance);

			calculations.unobstructedLights.push_back(lightStructure);
		}
	}

	return calculateColour(calculations);
}

Colour LightRay::calculateColour(Calculations calculations) {
	Colour intensityTotal(0, 0, 0);
	Colour diffuseTotal(0, 0, 0);
	Colour specularTotal(0, 0, 0);
	Colour refraction(0, 0, 0);
	Colour reflection(0, 0, 0);

	Colour ambientColour(calculations.material.ambient[0], calculations.material.ambient[1],calculations.material.ambient[2]);
	Colour diffuseColour(calculations.material.diffuse[0], calculations.material.diffuse[1],calculations.material.diffuse[2]);
	Colour specularColour(calculations.material.specular[0], calculations.material.specular[1],calculations.material.specular[2]);
	Colour emissionColour(calculations.material.emission[0], calculations.material.emission[1],calculations.material.emission[2]);

	Colour ambient;
	if(renderOptions->getAmbient()) {
		if(renderOptions->getGlobal()) {
			ambient = ambientColour * calculateGlobalIllumination(calculations);
		} else {
			ambient = ambientColour * Colour(0.5, 0.5, 0.5);
		}
	}

	for (int i = 0; i < calculations.unobstructedLights.size(); i++) {
		LightStructure lightStructure = calculations.unobstructedLights[i];

		Colour diffuse;
		Colour specular;
		Colour light = lightStructure.light.getColour() * lightStructure.dissolveTotal;

		//Diffuse**********************************************************************************
		if(renderOptions->getDiffuse()) {
			diffuse = light * diffuseColour * lightStructure.aoi;
		}
		//******************************************************************************Diffuse End

		//Specular*********************************************************************************
		if (lightStructure.aoi != 0.0 && renderOptions->getSpecular()) {
			specular = light * specularColour * std::pow(calculations.normal.dot(lightStructure.halfwayVector), (double) calculations.material.shininess);
		}
		//*****************************************************************************Specular End

		//Distance*********************************************************************************
		diffuse = diffuse * lightStructure.distanceModifier;
		specular = specular * lightStructure.distanceModifier;
		//*****************************************************************************Distance End
		diffuseTotal = diffuseTotal + diffuse;
		specularTotal = specularTotal + specular;
	}

	//Reflection************************************************************************************
	if(calculations.material.shininess > 1 && renderOptions->getReflection()) {
		reflection = calculateReflection(calculations) * (calculations.material.shininess / 1024) * specularColour;
	}
	//********************************************************************************Reflection End

	//Refraction************************************************************************************
	if(calculations.material.dissolve < 1 && renderOptions->getRefraction()) {
		refraction = calculateRefraction(calculations);
	}
	//********************************************************************************Refraction End

	Colour nonRefractedTotal = (ambient + diffuseTotal + specularTotal + emissionColour + reflection) * calculations.material.dissolve;
	Colour refractedTotal = refraction * (1 - calculations.material.dissolve);

	intensityTotal = refractedTotal + nonRefractedTotal;
	intensityTotal.setR(std::min(intensityTotal.getR(), 1.0));
	intensityTotal.setG(std::min(intensityTotal.getG(), 1.0));
	intensityTotal.setB(std::min(intensityTotal.getB(), 1.0));

	return intensityTotal;
}

Colour LightRay::calculateReflection(Calculations calculations) {
	Vector originVector = calculations.originVector;
	Vector reflectionVector = originVector - (calculations.normal * (2 * calculations.aoi));
	Ray reflectionRay(calculations.intersectionPoint, calculations.intersectionPoint - reflectionVector);
	return newRay(reflectionRay, calculations.depth + 1);
}

Colour LightRay::calculateRefraction(Calculations calculations) {
	Vector originVector = calculations.originVector;
	Vector normal = calculations.normal;
	double ior = calculations.material.ior;
	double aoi = calculations.aoi;

	if (aoi < 0) {
		ior = 1 / ior;
	}
	double sqrt = 1 - (ior*ior * (1 - aoi*aoi));
	//double sqrt = 1 - (ior*ior * (1 - powf(2, aoi)));

	if (sqrt >= 0) {
		Vector refractionVector;

		if (aoi >= 0) {
			refractionVector = normal * (ior * (aoi) - std::sqrt(sqrt)) - originVector * ior;
		} else {
			refractionVector = normal * (ior * (aoi) + std::sqrt(sqrt)) - originVector * ior;
		}

		Ray refractionRay(calculations.intersectionPoint, calculations.intersectionPoint + refractionVector);
		return newRay(refractionRay, calculations.depth + 1);
	} else {
		return calculateReflection(calculations);
	}
}

Colour LightRay::calculateGlobalIllumination(Calculations calculations)
{
	Colour colour;
	//K nearest neighbour algorithm involving photon mapping class. probably just a method call to photon mapping to produce value or close to value.

	return colour;
}

LightRay::LightStructure::LightStructure(Light light, double distanceModifier, Vector lightVector, Vector halfwayVector, double diffuseDotProduct) {
	this->light = light;
	this->distanceModifier = distanceModifier;
	this->lightVector = lightVector;
	this->halfwayVector = halfwayVector;
	this->aoi = diffuseDotProduct;
}

LightRay::LightStructure::LightStructure() {}
