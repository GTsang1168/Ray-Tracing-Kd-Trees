#ifndef AABB_H
#define AABB_H

#include <vector>

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Triangle.h"

class AABB {
public:
	AABB();
	AABB(Point min, Point max);
	bool isIntersect(Ray ray);
	bool isIntersect(Triangle triangle);

	Point min;
	Point max;
	Point center;
	Vector boxHalfSize;
	vector<Ray> getLines() const;

private:
	bool edgeDetection(Point v0, Point v1, Point v2, Vector edge0, Vector edge1, Vector edge2);
	bool aabbDetection(Point v0, Point v1, Point v2);
	bool planeDetection(Vector normal, Point vertex, Vector boxHalfSize);
	bool axisTestX(double a, double b, double fa, double fb, Point v0, Point v1);
	bool axisTestY(double a, double b, double fa, double fb, Point v0, Point v1);
	bool axisTestZ(double a, double b, double fa, double fb, Point v0, Point v1);

	vector<Ray> lines;
};

#endif // AABB_H
