#include "Triangle.h"

Triangle::Triangle() {}

Point Triangle::getP0() const
{
    return p0;
}

void Triangle::setP0(const Point &value)
{
    p0 = value;
}

Point Triangle::getP1() const
{
    return p1;
}

void Triangle::setP1(const Point &value)
{
    p1 = value;
}

Point Triangle::getP2() const
{
    return p2;
}

void Triangle::setP2(const Point &value)
{
    p2 = value;
}

Point Triangle::getCentroid() const
{
    return centroid;
}

void Triangle::setCentroid(const Point &value)
{
    centroid = value;
}

Vector Triangle::getNormal() const
{
    return normal;
}

void Triangle::setNormal(const Vector &value)
{
    normal = value;
}
Vector Triangle::getU() const
{
    return u;
}

void Triangle::setU(const Vector &value)
{
    u = value;
}

Vector Triangle::getV() const
{
    return v;
}

void Triangle::setV(const Vector &value)
{
    v = value;
}

int Triangle::getMaterial() const
{
    return material;
}

void Triangle::setMaterial(int value)
{
    material = value;
}

Triangle::Triangle(Point p0, Point p1, Point p2, int material) {
	setP0(p0);
	setP1(p1);
	setP2(p2);
	setMaterial(material);
	setU(p1 - p0);
	setV(p2 - p0);
	setNormal(Vector::normalize(getU().cross(getV())));
	centroid = Point((p0.getX() + p1.getX() + p2.getX()) / 3, (p0.getY() + p1.getY() + p2.getY()) / 3, (p0.getZ() + p1.getZ() + p2.getZ()) / 3);
}

Triangle::Triangle(double p[9], int material) {
	setP0(Point(p[0], p[1], p[2]));
	setP1(Point(p[3], p[4], p[5]));
	setP2(Point(p[6], p[7], p[8]));
	setMaterial(material);
	setU(getP1() - getP0());
	setV(getP2() - getP0());
	setNormal(Vector::normalize(getU().cross(getV())));
	centroid = Point((p0.getX() + p1.getX() + p2.getX()) / 3, (p0.getY() + p1.getY() + p2.getY()) / 3, (p0.getZ() + p1.getZ() + p2.getZ()) / 3);
}
