/**
\class RayInitialization
\brief Initiates the ray tracing process.

This class takes in the required classes for ray tracing and initiates the ray tracing process by projecting a ray through each pixel indicated
via the Camera class using the model indicated via the DataStructure class. The resulting image is then stored within the ImageData class to
be accessed at a later date for actual image generation. The LightRay class is used to perform the actual ray tracing calculations. This class
is simply used to facilitate the integration of these individual classes into a processable application.

\author Gavin Tsang
\date 16/02/2015
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <assert.h>
#include <vector>
#include <thread>
#include "boost/thread/thread.hpp"

#include "DataStructure.h"
#include "Camera.h"
#include "ImageData.h"
#include "LightRay.h"
#include "RenderOptions.h"

#define LINE_JUMP 5;

using namespace std;

class RayInitialization
{
public:
	void setMultiThread(bool value);
	bool isMultiThread();
	bool isRenderDone() const;

	void generateImage();
	int getRayProgress() const;

	RayInitialization(DataStructure * dataStructure, Camera camera, ImageData * imageData, RenderOptions * renderOptions);
	RayInitialization();

private:
	void setRayProgress(int value);
	void setRenderDone(bool value);

	void makeRay(int x, int y);
	void makeThread();
	bool getNextThreadJob(int * x, int * y);
	
	DataStructure * dataStructure;
	vector<bool> lineRendering;
	int lineCount = 0;
	Camera camera;
	ImageData * imageData;
	RenderOptions * renderOptions;
	LightRay lightRay;
	bool multiThread = true;
	int rayProgress = 0;
	bool renderDone = false;
};
