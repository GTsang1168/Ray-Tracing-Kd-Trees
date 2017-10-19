/**
\class KdTree
\brief Data structure used to store the model data.

Specifically, this class stores the model data in a kD Tree algorithm which provides a data retrieval complexity of O(n log(n)).
A kD tree is a subset of the BSP tree algorithm. this involves the splitting of data points into recursively smaller
axis-aligned bounding boxes or AABB for short. The distinguishing feature is that an algorithm is used to calculate the splitting location
instead of a hard defined splitting location. This class is used within DataStructure in order to obfuscate the data retrieval process.

\author Gavin Tsang
\date 16/02/2015
\see https://www.youtube.com/watch?&v=3vONlLYtHUE
http://www.realtimerendering.com/intersections.html
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Camera.h"
#include "Point.h"
#include "Ray.h"
#include "Triangle.h"
#include "Vector.h"
#include "AABB.h"

#define MAX_LEVEL 20
#define MIN_TRIANGLE 25

using namespace std;

class KdTree {
public:
	KdTree();
	KdTree(vector<Triangle> * triangles);
	vector<int> getTriangle(Ray ray);
	vector<Ray> getLines(Ray ray);
	
private:

	class Node {
	public:
		Node(vector<int> triangles, KdTree * root, AABB aabbParent, int level, int dimension, int maxLevel, int minTriangle);
		Node();

		vector<int> getTriangle(Ray ray);
		vector<Ray> getLines(Ray ray);

	private:
		double generateSplit(vector<int> triangles);

		int level;
		Node * left = nullptr;
		Node * right = nullptr;
		vector<int> triangles;
		int dimension = 0;
		KdTree * root;
		AABB aabb;
		bool leaf = false;
	};

	vector<Triangle> * triangles;
	Node * initNode;
};
