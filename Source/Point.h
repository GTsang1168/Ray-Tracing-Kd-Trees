/**
\class Point
\brief Class used to store the data of a three dimensional point in space.

This Pointer object is used to indicate a location in three dimensional space. This class along with the Vector class is used to perform
the required vector calculations required for ray tracing. Many of the standard operators used within C++ has been overwritten in order to
facilitate vector algebra. As such, a Pointer is to be used much like that of a primitive type such as an int or double.

All data being stored is defined via doubles. This facilitates precision placement of locations in 3D space while balancing the speed of
operations required.

\author Gavin Tsang
\date 16/02/2015
*/

#pragma once
#include <iostream>
#include <string>

#include "Point.h"
#include "Vector.h"

using namespace std;

class Point {
public:
	Point();
	Point(double x, double y, double z);
	bool isEqual(Point point);
	double distance(Point point);
	bool operator ==(const Point point) const;
	Vector operator +(Point point);
	Vector operator -(Point point);
	Point operator +(Vector vector);
	Point operator -(Vector vector);

	double getX() const;
	void setX(double value);

	double getY() const;
	void setY(double value);

	double getZ() const;
	void setZ(double value);

	double getDimension(int dimension) const;
	void setDimension(int dimension, double value);

private:
	double array[3];
};
