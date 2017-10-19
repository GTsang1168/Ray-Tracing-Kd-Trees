/**
\class LightPoint
\brief A LightPoint object indicates a point light source.

A lightsource is defined as a single Point in three dimensional space which radiates light indicated via a Colour object. Multiple light
sources can be defined and stored within DataStructure to provide illumination over a model. The colour of light being projected is defined
using the Colour object with bright lights being high RGB values while dim lights are indicated by low RGB values.

\author Gavin Tsang
\date 16/02/2015
*/

#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

#include "Point.h"
#include "Colour.h"

class Light
{
public:
	Light();
	Light(Point p, Colour c);
	~Light();

	Point getLocation() const;
	void setLocation(const Point &value);

	Colour getColour() const;
	void setColour(const Colour &value);

private:
	Point location;
	Colour colour;
};

#endif // LIGHTPOINT_H
