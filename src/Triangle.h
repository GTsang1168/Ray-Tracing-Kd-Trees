/**
\class Triangle
\brief Triangle primitive object used to indicate a triangular face or polygon.

This triangle primitive stores all the necessary data required to define a triangular face in three dimensional space. Using multiple
Triangle objects, a model of any shape and size can be created. Several values (such as the normal vector) required in ray tracing
are pre-calculated when a new Triangle object is created.

\author Gavin Tsang
\date 16/02/2015
*/

#pragma once

#include <iostream>
#include <string>

#include "Point.h"
#include "Vector.h"

using namespace std;

class Triangle {
public:
	Triangle(double p[9], int material);
	Triangle(Point p0, Point p1, Point p2, int material = -1);
	Triangle();

	Point getP0() const;
	void setP0(const Point &value);

	Point getP1() const;
	void setP1(const Point &value);

	Point getP2() const;
	void setP2(const Point &value);

	Point getCentroid() const;
	void setCentroid(const Point &value);

	Vector getNormal() const;
	void setNormal(const Vector &value);

	Vector getU() const;
	void setU(const Vector &value);

	Vector getV() const;
	void setV(const Vector &value);

	int getMaterial() const;
	void setMaterial(int value);

private:
	Point p0;
	Point p1;
	Point p2;
	Point centroid;
	Vector normal;
	Vector u, v;
	int material;
};
