/**
\class Colour
\brief A colour object is used to store the RGB colour values of a pixel

This class is used mainly in passing colour data in bulk between intersection calculations and used to store image data in the ImageData class.
As stated, this class uses the RGB model of representing colour in which the red, blue and green colour channels are represented via a double
value between 0 and 1.0.

\author Gavin Tsang
\date 16/02/2015
*/

#ifndef COLOUR_H
#define COLOUR_H

#include <assert.h>

#include "Colour.h"

class Colour
{
public:
	Colour();
	Colour(double r, double g, double b);

	double getR() const;
	void setR(double value);

	double getG() const;
	void setG(double value);

	double getB() const;
	void setB(double value);

	double getChannel(int value) const;

	Colour operator *(Colour colour);
	Colour operator +(Colour colour);
	Colour operator -(Colour colour);
	Colour operator *(double value);

private:
	double colour[3];
};

#endif // COLOUR_H

