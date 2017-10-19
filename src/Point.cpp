#include "Point.h"

Point::Point() {}

Point::Point(double x, double y, double z) {
	setX(x);
	setY(y);
	setZ(z);
}

bool Point::isEqual(Point point) {
	return (getX() == point.getX() &&
		getY() == point.getY() &&
			getZ() == point.getZ());
}

double Point::distance(Point point)
{
	double x0 = getX();
	double y0 = getY();
	double z0 = getZ();
	double x1 = point.getX();
	double y1 = point.getY();
	double z1 = point.getZ();

	return std::pow(x1 - x0, 2) + std::pow(y1 - y0, 2) + std::pow(z1 - z0, 2);
}

bool Point::operator ==(const Point point) const {
	return (getX() == point.getX() &&
		getY() == point.getY() &&
		getZ() == point.getZ());
}

Vector Point::operator+(Point point) {
	double x = getX() + point.getX();
	double y = getY() + point.getY();
	double z = getZ() + point.getZ();
	return Vector(x, y, z);
}

Vector Point::operator-(Point point) {
	double x = getX() - point.getX();
	double y = getY() - point.getY();
	double z = getZ() - point.getZ();
	return Vector(x, y, z);
}

Point Point::operator+(Vector vector) {
	double x = getX() + vector.getX();
	double y = getY() + vector.getY();
	double z = getZ() + vector.getZ();
	return Point(x, y, z);
}

Point Point::operator-(Vector vector) {
	double x = getX() - vector.getX();
	double y = getY() - vector.getY();
	double z = getZ() - vector.getZ();
	return Point(x, y, z);
}
double Point::getX() const
{
	return array[0];
}

void Point::setX(double value)
{
	array[0] = value;
}
double Point::getY() const
{
	return array[1];
}

void Point::setY(double value)
{
	array[1] = value;
}
double Point::getZ() const
{
	return array[2];
}

void Point::setZ(double value)
{
	array[2] = value;
}

double Point::getDimension(int dimension) const
{
	return array[dimension];
}

void Point::setDimension(int dimension, double value)
{
	array[dimension] = value;
}



