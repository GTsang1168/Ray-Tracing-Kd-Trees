#pragma once
#include <vector>

#include "kdTree.h"

using namespace std;

class Node
{
public:
	Node();
	Node(AABB box, vector<Triangle> polygons);

private:
	AABB box;
	Node leftNode;
	Node rightNode;
};

