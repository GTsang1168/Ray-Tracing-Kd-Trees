#include "Camera.h"

Camera::Camera(Point location, Vector upOrientation, Vector viewVector, double planeDistance, double width, double height, int wPix = 768, int hPix = 768) {
	assert(!upOrientation.isEqual(viewVector));
	this->location = location;
	this->v = Vector::normalize(upOrientation);
	this->viewVector = Vector::normalize(viewVector);
	this->planeDistance = planeDistance;
	this->width = width;
	this->height = height;
	this->wPix = wPix;
	this->hPix = hPix;

	u = v.cross(this->viewVector);
	v = u.cross(this->viewVector);
	planeCentre = location + (this->viewVector * planeDistance);
	pixelOrigin = planeCentre + (u * (width / 2)) + (v * (height / 2));
}

Camera::Camera(Point location, Point lookAt, double planeDistance, double width, double height, int wPix = 768, int hPix = 768) {
	Vector viewVector = lookAt - location;
    Vector rightVector = viewVector.cross(Vector(0, 1, 0));
    Vector upOrientation(rightVector.cross(viewVector));

	this->location = location;
	this->v = Vector::normalize(upOrientation);
	this->viewVector = Vector::normalize(viewVector);
    assert(!v.isEqual(this->viewVector));
	this->planeDistance = planeDistance;
	this->width = width;
	this->height = height;
	this->wPix = wPix;
	this->hPix = hPix;

	u = v.cross(this->viewVector);
	planeCentre = location + (this->viewVector * planeDistance);
	pixelOrigin = planeCentre + (u * (width / 2)) + (v * (height / 2));
}

Camera::Camera() {}

Point Camera::getPixelLocation(int i, int j) {
	assert(i < wPix);
	assert(j < hPix);
	return pixelOrigin - (u * i * (width / wPix)) - (v * j * (height / hPix));
}

Point Camera::getLocation() {
	return location;
}

int Camera::getWPix() const
{
    return wPix;
}

int Camera::getHPix() const
{
    return hPix;
}
