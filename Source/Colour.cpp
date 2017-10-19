#include "Colour.h"

Colour::Colour() {}

Colour::Colour(double r, double g, double b)
{
	setR(r);
	setG(g);
	setB(b);
}
double Colour::getR() const
{
	return colour[0];
}

void Colour::setR(double value)
{
	colour[0] = value;
}
double Colour::getG() const
{
	return colour[1];
}

void Colour::setG(double value)
{
	colour[1] = value;
}
double Colour::getB() const
{
	return colour[2];
}

void Colour::setB(double value)
{
	colour[2] = value;
}

double Colour::getChannel(int value) const
{
	return colour[value];
}

Colour Colour::operator *(Colour colour)
{
	Colour result;
	result.setR(getR() * colour.getR());
	result.setG(getG() * colour.getG());
	result.setB(getB() * colour.getB());
	return result;
}

Colour Colour::operator +(Colour colour)
{
	Colour result;
	result.setR(getR() + colour.getR());
	result.setG(getG() + colour.getG());
	result.setB(getB() + colour.getB());
	return result;
}

Colour Colour::operator -(Colour colour)
{
	Colour result;
	result.setR(getR() - colour.getR());
	result.setG(getG() - colour.getG());
	result.setB(getB() - colour.getB());
	return result;
}

Colour Colour::operator *(double value)
{
	Colour result;
	result.setR(getR() * value);
	result.setG(getG() * value);
	result.setB(getB() * value);
	return result;
}
