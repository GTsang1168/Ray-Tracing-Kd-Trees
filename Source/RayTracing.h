#ifndef RAYTRACING_H
#define RAYTRACING_H

#include <QObject>
#include <ctime>
#include <vector>
#include <string>

#include "initialize.h"
#include "ImageData.h"
#include "Camera.h"
#include "DataStructure.h"
#include "RenderOptions.h"
#include "RayInitialization.h"
#include "LightPoint.h"

class RayTracing : public QObject
{
	Q_OBJECT

public:
	RayTracing();
	RayTracing(string &fileName);
    ~RayTracing();
	ImageData* getImageData();
	void generateKdTree();

	Camera getCamera() const;
	void setCamera(const Camera &value);

	bool isUseKdTree();
	void setUseKdTree(const bool &value);

	vector<Light> getLights();
	void setLights(const vector<Light> lights);

	void setRenderOptions(RenderOptions *value);
	int getTriangleCount();
	double getMaxPoint(int dimension);
	double getMinPoint(int dimension);

public slots:
	void slotStartRender();

signals:
	void signalRenderProgress(int percentageDone, double durationPast);

private:
	void signalPulser();
	void startRender();
	void startMosaicRender();

	DataStructure dataStructure;
	RayInitialization rayInitialization;
	Camera camera;
	ImageData imageData;
	RenderOptions *renderOptions;
	std::clock_t clock;
};

#endif // RAYTRACING_H
