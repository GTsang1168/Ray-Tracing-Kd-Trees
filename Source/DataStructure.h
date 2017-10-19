/**
\class DataStructure
\brief Stores the model data in a data structure to be accessed by other classes.

This class obfuscates the model data retrieval into a single getIntersection method. This performs all intersection tests using
either a naive data structure or, if the correct options are selected, using a kD Tree. This class is used within RayInitialization to 
provide the necessary data for ray tracing. Initialization of this class requires the use of the Initialize class in order to generate
the correct input array to store the data. Triangle-Point storage is naively stored with each Triangle containing 3 unique Points.

\author Gavin Tsang
\date 16/02/2015
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "tiny_obj_loader.h"
#include "Triangle.h"
#include "LightPoint.h"
#include "Ray.h"
#include "kdTree.h"
#include "Intersection.h"
#include "IntersectionLine.h"

using namespace std;
using namespace tinyobj;

class DataStructure {
	public:
		enum Dimension {X = 0, Y = 1, Z = 2};
        DataStructure();
		void setAccelerateKdTree(bool accelerate);
		bool isAccelerateKdTree();
		material_t getMaterial(int index);
		vector<Light> getLights();
		void setPolygon(vector<Triangle> polygon);
		void setMaterial(vector<material_t> material);
		void setLights(vector<Light> lights);
		double getMaxPoint(int dimension);
		double getMinPoint(int dimension);
		int getTriangleCount();

		void generateKdTree();
		vector<Intersection> getIntersection(Ray ray);
		vector<IntersectionLine> getIntersectionLine(Ray ray);

		double getMaxSize() const;

		double getMinSize() const;

private:
		vector<Intersection> intersectionKd(Ray ray);
		vector<Intersection> intersectionNoKd(Ray ray);
		double intersection(Ray ray, Triangle triangle, Point * intPoint);
		void setMaxSize(double value);
		void setMinSize(double value);

		vector<Light> lights;
		vector<Triangle> triangle;
		vector<material_t> m_material;
		bool accelerateKdTree = false;
		bool kdTreeGenerated = false;
		KdTree kdTree;

		double maxSize;
		double minSize;

        material_t generateDefaultMaterial();

        material_t defaultMaterial;
};

