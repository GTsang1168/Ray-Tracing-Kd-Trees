#include "RayTracing.h"

RayTracing::RayTracing()
{

}

RayTracing::RayTracing(string &fileName)
{
	Initialize(fileName, &dataStructure);
}

RayTracing::~RayTracing()
{

}

ImageData* RayTracing::getImageData()
{
	return &imageData;
}

void RayTracing::generateKdTree()
{
	dataStructure.generateKdTree();
}

void RayTracing::slotStartRender()
{
	clock = std::clock();
	rayInitialization = RayInitialization(&dataStructure, camera, &imageData, renderOptions);
	boost::thread signalPulser = boost::thread(&RayTracing::signalPulser, this);
	boost::thread startRender = boost::thread(&RayTracing::startRender, this);
}

void RayTracing::signalPulser()
{
	while(!rayInitialization.isRenderDone()) {
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		double duration = (std::clock() - clock) / (double) CLOCKS_PER_SEC;
		int progress = rayInitialization.getRayProgress() / (camera.getHPix() * camera.getWPix());
		emit signalRenderProgress(progress, duration);
	}
	double duration = (std::clock() - clock) / (double) CLOCKS_PER_SEC;
	emit signalRenderProgress(100, duration);
	duration = 0;
}

void RayTracing::startRender()
{
	rayInitialization.generateImage();
}

void RayTracing::startMosaicRender()
{

}

void RayTracing::setRenderOptions(RenderOptions *value)
{
	renderOptions = value;
}

int RayTracing::getTriangleCount()
{
	return dataStructure.getTriangleCount();
}

double RayTracing::getMaxPoint(int dimension)
{
	return dataStructure.getMaxPoint(dimension);
}

double RayTracing::getMinPoint(int dimension)
{
	return dataStructure.getMinPoint(dimension);
}

Camera RayTracing::getCamera() const
{
	return camera;
}

void RayTracing::setCamera(const Camera &value)
{
	camera = value;
	imageData = ImageData(value.getWPix(), value.getHPix());
}

bool RayTracing::isUseKdTree()
{
	return dataStructure.isAccelerateKdTree();
}

void RayTracing::setUseKdTree(const bool &value)
{
	dataStructure.setAccelerateKdTree(value);
}

vector<Light> RayTracing::getLights()
{
	return dataStructure.getLights();
}

void RayTracing::setLights(const vector<Light> lights)
{
	dataStructure.setLights(lights);
}

