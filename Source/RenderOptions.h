#ifndef RENDEROPTIONS_H
#define RENDEROPTIONS_H


class RenderOptions
{
public:
    RenderOptions();
    ~RenderOptions();

	double getGamma() const;
	void setGamma(double value);

	double getRecursiveDepth() const;
	void setRecursiveDepth(double value);

	bool getDefaultMaterial() const;
	void setDefaultMaterial(bool value);

	bool getPhong() const;
	void setPhong(bool value);

	bool getDiffuse() const;
	void setDiffuse(bool value);

	bool getSpecular() const;
	void setSpecular(bool value);

	bool getAmbient() const;
	void setAmbient(bool value);

	bool getShadows() const;
	void setShadows(bool value);

	bool getReflection() const;
	void setReflection(bool value);

	bool getRefraction() const;
	void setRefraction(bool value);

	bool getDistance() const;
	void setDistance(bool value);

	bool getGlobal() const;
	void setGlobal(bool value);

	bool getMultiThread() const;
	void setMultiThread(bool value);

	bool getViewKdTree() const;
	void setViewKdTree(bool value);

private:
	double gamma = 1.4;
	double recursiveDepth = 10;
	bool defaultMaterial = true;
	bool phong = true;
	bool diffuse = true;
	bool specular = true;
	bool ambient = true;
	bool shadows = true;
	bool reflection = true;
	bool refraction = true;
	bool distance = true;
	bool global = false;
	bool multiThread = true;
	bool viewKdTree = false;
};

#endif // RENDEROPTIONS_H
