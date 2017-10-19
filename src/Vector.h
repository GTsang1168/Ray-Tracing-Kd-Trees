/**
\class Vector
\brief A vector primitive object is used to indicate movement within three dimensional space.

A Vector object along with a Point object is used to perform vector algebra which is required to ray trace objects in three dimensional space.
As with Pointer, several standard operators have been overwritten to facilitate vector algebra.

\author Gavin Tsang
\date 16/02/2015
*/

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Vector {
public:
	Vector();
	Vector(double x, double y, double z);
	Vector cross(Vector vector);
	double dot(Vector vector);
	Vector operator -(Vector vector);
	Vector operator -();
	Vector operator +(Vector vector);
	Vector operator *(double scalar);
	Vector operator /(double divisor);
	static Vector normalize(Vector vector);
	bool isEqual(Vector vector);

	double getX() const;
	void setX(double value);

	double getY() const;
	void setY(double value);

	double getZ() const;
	void setZ(double value);

	double getDimension(int dimension) const;

private:
	double array[3];
};
