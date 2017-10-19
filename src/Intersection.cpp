#include "Intersection.h"

Intersection::Intersection()
{

}

Intersection::Intersection(Point intPoint, Triangle *polygon, double rayOriginDistance)
{
	setIntersection(intPoint);
	setPolygon(polygon);
	setRayOriginDistance(rayOriginDistance);
}

Intersection::~Intersection()
{

}

Triangle *Intersection::getPolygon() const
{
	return polygon;
}

void Intersection::setPolygon(Triangle *value)
{
	polygon = value;
}
double Intersection::getRayOriginDistance() const
{
	return rayOriginDistance;
}

void Intersection::setRayOriginDistance(double value)
{
	rayOriginDistance = value;
}
Point Intersection::getIntersection() const
{
	return intPoint;
}

void Intersection::setIntersection(const Point &value)
{
	intPoint = value;
}

