#ifndef INTERSECTIONLINE_H
#define INTERSECTIONLINE_H

#include "Ray.h"

class IntersectionLine
{
public:
    IntersectionLine();
	IntersectionLine(Ray ray, double intDistance);
    ~IntersectionLine();

	double getIntDistance() const;
	void setIntDistance(double value);

	Ray getRay() const;
	void setRay(const Ray &value);

private:
	double intDistance;
	Ray ray;
};

#endif // INTERSECTIONLINE_H
