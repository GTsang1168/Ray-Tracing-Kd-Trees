/**
\class Camera
\brief Defines the camera object indicating the user's viewpoint.

Defines the paramaters required for a camera to exist within three dimensional space. Also precalculates the exact location of each
pixel within the imaginary "film strip" in which the projected rays will save their calculated intensities to. This along with the origin
location for each ray provides the data needed to generate each pixel's ray. This is used in conjunction with the RayInitialization class
to raytrace a model.

\author Gavin Tsang
\date 16/02/2015
\see http://web.cse.ohio-state.edu/~hwshen/681/Site/Slides_files/basic_algo.pdf
*/	

#pragma once
#include <assert.h>

#include "Camera.h"
#include "Point.h"

using namespace std;

class Camera
{
public:
	Camera(Point location, Vector upOrientation, Vector viewVector, double planeDistance, double width, double height, int wPix, int hPix);
	Camera(Point location, Point lookAt, double planeDistance, double width, double height, int wPix, int hPix);
    Camera();

	Point getPixelLocation(int i, int j);
	Point getLocation();

	int getWPix() const;

	int getHPix() const;

private:
	Point location;
	Vector viewVector;
	double planeDistance;
	double width, height;
	int wPix, hPix;

	Vector v, u;
	Point planeCentre;
	Point pixelOrigin;
};

