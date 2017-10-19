//http://www.boost.org/doc/libs/1_37_0/doc/html/thread/thread_management.html#thread.thread_management.thread.hardware_concurrency

#include "RayInitialization.h"

RayInitialization::RayInitialization(DataStructure * dataStructure, Camera camera, ImageData * imageData, RenderOptions * renderOptions) {
	lightRay = LightRay(dataStructure, renderOptions);
	this->dataStructure = dataStructure;
	this->camera = camera;
	this->imageData = imageData;
	this->renderOptions = renderOptions;

	setMultiThread(renderOptions->getMultiThread());

	for(int i = 0; i < imageData->getHeight(); i++) {
		lineRendering.push_back(false);
	}
}

RayInitialization::RayInitialization() {}

void RayInitialization::setMultiThread(bool value) {
	multiThread = value;
}

bool RayInitialization::isMultiThread() {
	return multiThread;
}

void RayInitialization::generateImage() {
	int width = (*imageData).getWidth();
	int height = (*imageData).getHeight();

	lineCount = 0;

	if (multiThread) {
		int threadNo = boost::thread().hardware_concurrency();
		boost::thread_group threadGroup;

		for (int i = 0; i < threadNo; i++) {
			boost::thread * thread = new boost::thread(&RayInitialization::makeThread, this);
			threadGroup.add_thread(thread);
		}

		threadGroup.join_all();
	} else {
		for (int y = getRayProgress(); y < height; y++) {
			for (int x = 0; x < width; x++) {
				makeRay(x, y);
			}
			setRayProgress(getRayProgress() + 1);
		}
	}
	setRenderDone(true);
}

void RayInitialization::makeRay(int x, int y) {
	Ray ray(camera.getLocation(), camera.getPixelLocation(x, y));
	imageData->setPixel(x, y, lightRay.newRay(ray, 0));
	setRayProgress(getRayProgress() + 1);
}

void RayInitialization::makeThread() {
	int x, y;
	while(getNextThreadJob(&x, &y)) {
		while (!lineRendering[y]) {
			lineRendering[y] = true;
			for (int i = x; i < imageData->getWidth(); i++) {
				makeRay(i, y);
			}
			y++;
			if(y > imageData->getHeight() - 1) {
				break;
			}
		}
	}
}

int RayInitialization::getRayProgress() const
{
	return rayProgress;
}

void RayInitialization::setRayProgress(int value)
{
	rayProgress = value;
}

bool RayInitialization::isRenderDone() const
{
	return renderDone;
}

void RayInitialization::setRenderDone(bool value)
{
	renderDone = value;
	if(value) {
		for(int i = 0; i < lineRendering.size(); i++) {
			lineRendering[i] = false;
		}
		lineCount = 0;
	}
}

bool RayInitialization::getNextThreadJob(int * x, int * y)
{
	(*x) = 0;
	lineCount += LINE_JUMP;
	if(lineCount > imageData->getHeight() - 1) {
		lineCount = lineCount + 1 - LINE_JUMP;
	}
	(*y) = lineCount;
	if(lineCount > imageData->getHeight() - 1) {
		return false;
	} else {
		return true;
	}
}

