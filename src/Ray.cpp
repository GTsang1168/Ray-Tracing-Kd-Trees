#include "Ray.h"

Ray::Ray()
{

}

Ray::Ray(Point p0, Point p1)
{
	setOriginPoint(p0);
	setEndPoint(p1);
	calculateDirFrac();
}

Ray::~Ray()
{

}
Point Ray::getEndPoint() const
{
	return endPoint;
}

void Ray::setEndPoint(const Point &value)
{
	endPoint = value;
}
Point Ray::getOriginPoint() const
{
	return originPoint;
}

void Ray::setOriginPoint(const Point &value)
{
	originPoint = value;
}
Vector Ray::getDirFrac() const
{
	return dirFrac;
}

void Ray::calculateDirFrac()
{
	Vector rayDirection = Vector::normalize(getEndPoint() - getOriginPoint());
	dirFrac = Vector(1 / rayDirection.getX(), 1 / rayDirection.getY(), 1 / rayDirection.getZ());
}



