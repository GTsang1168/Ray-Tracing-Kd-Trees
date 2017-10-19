#include "Vector.h"

Vector::Vector() {}

Vector::Vector(double x, double y, double z) {
	setX(x);
	setY(y);
	setZ(z);
}

Vector Vector::cross(Vector vector) {
	double x = getY() * vector.getZ() - getZ() * vector.getY();
	double y = getZ() * vector.getX() - getX() * vector.getZ();
	double z = getX() * vector.getY() - getY() * vector.getX();
	return Vector(x, y, z);
}

double Vector::dot(Vector vector) {
	return getX() * vector.getX() + getY() * vector.getY() + getZ() * vector.getZ();
}

Vector Vector::operator -(Vector vector) {
	double x = getX() - vector.getX();
	double y = getY() - vector.getY();
	double z = getZ() - vector.getZ();
	return Vector(x, y, z);
}

Vector Vector::operator -() {
	return Vector(-getX(), -getY(), -getZ());
}

Vector Vector::operator+(Vector vector) {
	double x = getX() + vector.getX();
	double y = getY() + vector.getY();
	double z = getZ() + vector.getZ();
	return Vector(x, y, z);
}

Vector Vector::operator *(double scalar) {
	double x = getX() * scalar;
	double y = getY() * scalar;
	double z = getZ() * scalar;
	return Vector(x, y, z);
}

Vector Vector::operator /(double divisor) {
	double x = getX() / divisor;
	double y = getY() / divisor;
	double z = getZ() / divisor;
	return Vector(x, y, z);
}

Vector Vector::normalize(Vector vector) {
	double length = sqrt((vector.getX() * vector.getX()) + (vector.getY() * vector.getY()) + (vector.getZ() * vector.getZ()));
	double x = vector.getX() / length;
	double y = vector.getY() / length;
	double z = vector.getZ() / length;
	return Vector(x, y, z);
}

bool Vector::isEqual(Vector vector) {
	return (getX() == vector.getX() &&
		getY() == vector.getY() &&
		getZ() == vector.getZ());
}
double Vector::getX() const
{
	return array[0];
}

void Vector::setX(double value)
{
	array[0] = value;
}

double Vector::getY() const
{
	return array[1];
}

void Vector::setY(double value)
{
	array[1] = value;
}

double Vector::getZ() const
{
	return array[2];
}

void Vector::setZ(double value)
{
	array[2] = value;
}

double Vector::getDimension(int dimension) const
{
	return array[dimension];
}


