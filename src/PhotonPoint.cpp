#include "PhotonPoint.h"

PhotonPoint::PhotonPoint()
{

}

PhotonPoint::PhotonPoint(Point location, Colour colour)
{
	setLocation(location);
	setColour(colour);
}

PhotonPoint::~PhotonPoint()
{

}
Point PhotonPoint::getLocation() const
{
	return location;
}

void PhotonPoint::setLocation(const Point &value)
{
	location = value;
}
Colour PhotonPoint::getColour() const
{
	return colour;
}

void PhotonPoint::setColour(const Colour &value)
{
	colour = value;
}



