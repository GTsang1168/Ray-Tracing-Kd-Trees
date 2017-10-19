#include "IntersectionLine.h"

IntersectionLine::IntersectionLine()
{

}

IntersectionLine::IntersectionLine(Ray ray, double intDistance)
{
	setRay(ray);
	setIntDistance(intDistance);
}

IntersectionLine::~IntersectionLine()
{

}
double IntersectionLine::getIntDistance() const
{
	return intDistance;
}

void IntersectionLine::setIntDistance(double value)
{
	intDistance = value;
}
Ray IntersectionLine::getRay() const
{
	return ray;
}

void IntersectionLine::setRay(const Ray &value)
{
	ray = value;
}



