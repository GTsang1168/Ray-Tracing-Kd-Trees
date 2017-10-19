#include "AABB.h"

AABB::AABB() {}

AABB::AABB(Point min, Point max) {
	this->min = min;
	this->max = max;
	boxHalfSize = (max - min) / 2;
	center = min + boxHalfSize;

	Point p0 = min;
	Point p1 = Point(min.getX(), min.getY(), max.getZ());
	Point p2 = Point(max.getX(), min.getY(), max.getZ());
	Point p3 = Point(max.getX(), min.getY(), min.getZ());

	Point p7 = max;
	Point p4 = Point(min.getX(), max.getY(), min.getZ());
	Point p5 = Point(max.getX(), max.getY(), min.getZ());
	Point p6 = Point(min.getX(), max.getY(), max.getZ());

	Ray line = Ray(p0, p1);
	lines.push_back(line);
	line = Ray(p1, p2);
	lines.push_back(line);
	line = Ray(p2, p3);
	lines.push_back(line);
	line = Ray(p3, p0);
	lines.push_back(line);

	line = Ray(p4, p6);
	lines.push_back(line);
	line = Ray(p6, p7);
	lines.push_back(line);
	line = Ray(p7, p5);
	lines.push_back(line);
	line = Ray(p5, p4);
	lines.push_back(line);

	line = Ray(p0, p4);
	lines.push_back(line);
	line = Ray(p3, p5);
	lines.push_back(line);
	line = Ray(p2, p7);
	lines.push_back(line);
	line = Ray(p1, p6);
	lines.push_back(line);
}

bool AABB::isIntersect(Ray ray) {
	//Vector rayDirection = Vector::normalize(ray.getEndPoint() - ray.getOriginPoint());
	//Vector dirFrac(1 / rayDirection.getX(), 1 / rayDirection.getY(), 1 / rayDirection.getZ());
	Vector dirFrac = ray.getDirFrac();

	double t1 = (min.getX() - ray.getOriginPoint().getX()) * dirFrac.getX();
	double t2 = (max.getX() - ray.getOriginPoint().getX()) * dirFrac.getX();

	double t3 = (min.getY() - ray.getOriginPoint().getY()) * dirFrac.getY();
	double t4 = (max.getY() - ray.getOriginPoint().getY()) * dirFrac.getY();

	double t5 = (min.getZ() - ray.getOriginPoint().getZ()) * dirFrac.getZ();
	double t6 = (max.getZ() - ray.getOriginPoint().getZ()) * dirFrac.getZ();

	double tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
	double tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

	if(tmax < 0) {
		return false;
	}

	if(tmin > tmax) {
		return false;
	}

	return true;
}

bool AABB::isIntersect(Triangle triangle) {
	Point v0 = Point(0, 0, 0) + (triangle.getP0() - center);
	Point v1 = Point(0, 0, 0) + (triangle.getP1() - center);
	Point v2 = Point(0, 0, 0) + (triangle.getP2() - center);

	Vector edge0 = v1 - v0;
	Vector edge1 = v2 - v1;
	Vector edge2 = v0 - v2;

	return aabbDetection(v0, v1, v2) &&
		planeDetection(triangle.getNormal(), v0, boxHalfSize) &&
			edgeDetection(v0, v1, v2, edge0, edge1, edge2);
}

bool AABB::edgeDetection(Point v0, Point v1, Point v2, Vector edge0, Vector edge1, Vector edge2) {
	double fex = fabs(edge0.getX());
	double fey = fabs(edge0.getY());
	double fez = fabs(edge0.getZ());
	if (!axisTestX(edge0.getZ(), edge0.getY(), fez, fey, v0, v2)) {
		return false;
	}
	if (!axisTestY(edge0.getZ(), edge0.getX(), fez, fex, v0, v2)) {
		return false;
	}
	if (!axisTestZ(edge0.getY(), edge0.getX(), fey, fex, v1, v2)) {
		return false;
	}

	fex = fabs(edge1.getX());
	fey = fabs(edge1.getY());
	fez = fabs(edge1.getZ());
	if (!axisTestX(edge1.getZ(), edge1.getY(), fez, fey, v0, v2)) {
		return false;
	}
	if (!axisTestY(edge1.getZ(), edge1.getX(), fez, fex, v0, v2)) {
		return false;
	}
	if (!axisTestZ(edge1.getY(), edge1.getX(), fey, fex, v0, v1)) {
		return false;
	}

	fex = fabs(edge2.getX());
	fey = fabs(edge2.getY());
	fez = fabs(edge2.getZ());
	if (!axisTestX(edge2.getZ(), edge2.getY(), fez, fey, v0, v1)) {
		return false;
	}
	if (!axisTestY(edge2.getZ(), edge2.getX(), fez, fex, v0, v1)) {
		return false;
	}
	if (!axisTestZ(edge2.getY(), edge2.getX(), fey, fex, v1, v2)) {
		return false;
	}

	return true;
}

bool AABB::aabbDetection(Point v0, Point v1, Point v2) {
	double max = fmax(fmax(v0.getX(), v1.getX()), v2.getX());
	double min = fmin(fmin(v0.getX(), v1.getX()), v2.getX());
	if (min > boxHalfSize.getX() || max < -boxHalfSize.getX()) {
		return false;
	}

	max = fmax(fmax(v0.getY(), v1.getY()), v2.getY());
	min = fmin(fmin(v0.getY(), v1.getY()), v2.getY());
	if (min > boxHalfSize.getY() || max < -boxHalfSize.getY()) {
		return false;
	}

	max = fmax(fmax(v0.getZ(), v1.getZ()), v2.getZ());
	min = fmin(fmin(v0.getZ(), v1.getZ()), v2.getZ());
	if (min > boxHalfSize.getZ() || max < -boxHalfSize.getZ()) {
		return false;
	}

	return true;
}

bool AABB::planeDetection(Vector normal, Point vertex, Vector boxHalfSize) {
	double vMax[3], vMin[3];
	double v;

	for (int dimension = 0; dimension < 3; dimension++) {
		v = vertex.getDimension(dimension);

		if (normal.getDimension(dimension) > 0) {
			vMin[dimension] = -boxHalfSize.getDimension(dimension) - v;
			vMax[dimension] = boxHalfSize.getDimension(dimension) - v;
		} else {
			vMin[dimension] = boxHalfSize.getDimension(dimension) - v;
			vMax[dimension] = -boxHalfSize.getDimension(dimension) - v;
		}
	}

	Vector max(vMax[0], vMax[1], vMax[2]);
	Vector min(vMin[0], vMin[1], vMin[2]);

	if (normal.dot(min) > 0) {
		return false;
	}
	if (normal.dot(max) >= 0) {
		return true;
	}

	return false;
}

bool AABB::axisTestX(double a, double b, double fa, double fb, Point v0, Point v1) {
	double p0 = a*v0.getY() - b*v0.getZ();
	double p2 = a*v1.getY() - b*v1.getZ();

	double min = fmin(p0, p2);
	double max = fmax(p0, p2);

	double rad = fa * boxHalfSize.getY() + fb * boxHalfSize.getZ();

	if (min > rad || max < -rad) {
		return false;
	} else {
		return true;
	}
}

bool AABB::axisTestY(double a, double b, double fa, double fb, Point v0, Point v1) {
	double p0 = a*v0.getX() - b*v0.getZ();
	double p2 = a*v1.getX() - b*v1.getZ();

	double min = fmin(p0, p2);
	double max = fmax(p0, p2);

	double rad = fa * boxHalfSize.getX() + fb * boxHalfSize.getZ();

	if (min > rad || max < -rad) {
		return false;
	} else {
		return true;
	}
}
bool AABB::axisTestZ(double a, double b, double fa, double fb, Point v0, Point v1) {
	double p0 = a*v0.getX() - b*v0.getY();
	double p2 = a*v1.getX() - b*v1.getY();

	double min = fmin(p0, p2);
	double max = fmax(p0, p2);

	double rad = fa * boxHalfSize.getX() + fb * boxHalfSize.getY();

	if (min > rad || max < -rad) {
		return false;
	} else {
		return true;
	}
}
vector<Ray> AABB::getLines() const
{
	return lines;
}
