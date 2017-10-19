#ifndef PHOTONPOINT_H
#define PHOTONPOINT_H

#include "Point.h"
#include "Colour.h"

class PhotonPoint
{
public:
    PhotonPoint();
	PhotonPoint(Point location, Colour colour);
    ~PhotonPoint();

	Point getLocation() const;
	void setLocation(const Point &value);

	Colour getColour() const;
	void setColour(const Colour &value);

private:
	Point location;
	Colour colour;
};

#endif // PHOTONPOINT_H
