#include "LightPoint.h"

Light::Light()
{

}

Light::Light(Point p, Colour c)
{
	setLocation(p);
	setColour(c);
}

Light::~Light()
{

}
Point Light::getLocation() const
{
	return location;
}

void Light::setLocation(const Point &value)
{
	location = value;
}
Colour Light::getColour() const
{
	return colour;
}

void Light::setColour(const Colour &value)
{
	colour = value;
}



