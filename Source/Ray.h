/**
\class Ray
\brief A Ray is used to indicate an line of infinite length.

This Ray object is used within three dimensional space to represent a light ray being projected. A Ray can be indicated via two Point objects
which indicate two points in three dimesnional space which this ray intersects.

\author Gavin Tsang
\date 16/02/2015
*/

#ifndef RAY_H
#define RAY_H

#include "Point.h"

class Ray
{
public:
    Ray();
	Ray(Point p0, Point p1);
    ~Ray();

	Point getEndPoint() const;
	void setEndPoint(const Point &value);

	Point getOriginPoint() const;
	void setOriginPoint(const Point &value);

	Vector getDirFrac() const;

private:
	void calculateDirFrac();

	Point originPoint, endPoint;
	Vector dirFrac;
};

#endif // RAY_H
