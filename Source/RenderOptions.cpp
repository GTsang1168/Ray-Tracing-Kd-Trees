#include "RenderOptions.h"

RenderOptions::RenderOptions()
{

}

RenderOptions::~RenderOptions()
{

}
double RenderOptions::getGamma() const
{
	return gamma;
}

void RenderOptions::setGamma(double value)
{
	gamma = value;
}
double RenderOptions::getRecursiveDepth() const
{
	return recursiveDepth;
}

void RenderOptions::setRecursiveDepth(double value)
{
	recursiveDepth = value;
}
bool RenderOptions::getDefaultMaterial() const
{
	return defaultMaterial;
}

void RenderOptions::setDefaultMaterial(bool value)
{
	defaultMaterial = value;
}
bool RenderOptions::getPhong() const
{
	return phong;
}

void RenderOptions::setPhong(bool value)
{
	phong = value;
}
bool RenderOptions::getDiffuse() const
{
	return diffuse;
}

void RenderOptions::setDiffuse(bool value)
{
	diffuse = value;
}
bool RenderOptions::getSpecular() const
{
	return specular;
}

void RenderOptions::setSpecular(bool value)
{
	specular = value;
}
bool RenderOptions::getAmbient() const
{
	return ambient;
}

void RenderOptions::setAmbient(bool value)
{
	ambient = value;
}
bool RenderOptions::getShadows() const
{
	return shadows;
}

void RenderOptions::setShadows(bool value)
{
	shadows = value;
}
bool RenderOptions::getReflection() const
{
	return reflection;
}

void RenderOptions::setReflection(bool value)
{
	reflection = value;
}
bool RenderOptions::getRefraction() const
{
	return refraction;
}

void RenderOptions::setRefraction(bool value)
{
	refraction = value;
}
bool RenderOptions::getDistance() const
{
	return distance;
}

void RenderOptions::setDistance(bool value)
{
	distance = value;
}
bool RenderOptions::getGlobal() const
{
	return global;
}

void RenderOptions::setGlobal(bool value)
{
	global = value;
}
bool RenderOptions::getMultiThread() const
{
	return multiThread;
}

void RenderOptions::setMultiThread(bool value)
{
	multiThread = value;
}
bool RenderOptions::getViewKdTree() const
{
    return viewKdTree;
}

void RenderOptions::setViewKdTree(bool value)
{
    viewKdTree = value;
}

