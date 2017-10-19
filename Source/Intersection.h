/**
\class Intersection
\brief Used to store the data generated when a ray intersects with a Triangle object.

Using said data, colour intensities can then be calculated without the need to directly access the DataStructure containing the data and thus
provide obfuscation to the overall workings of the application.

\author Gavin Tsang
\date 16/02/2015
*/

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Point.h"
#include "Triangle.h"
#include "Triangle.h"

class Intersection
{
public:
    Intersection();
	Intersection(Point intPoint, Triangle * polygon, double rayOriginDistance);
	~Intersection();

	Triangle *getPolygon() const;
	void setPolygon(Triangle *value);

	double getRayOriginDistance() const;
	void setRayOriginDistance(double value);

	Point getIntersection() const;
	void setIntersection(const Point &value);

private:
	Point intPoint;
	Triangle * polygon;
	double rayOriginDistance;
};

#endif // INTERSECTION_H
