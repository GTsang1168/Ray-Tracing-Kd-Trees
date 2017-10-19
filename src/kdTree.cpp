#include "kdTree.h"

KdTree::KdTree() {}

KdTree::KdTree(vector<Triangle> * triangles) {
	this->triangles = triangles;

	vector<int> trianglePointers;
	for (int i = 0; i < triangles->size(); i++) {
		trianglePointers.push_back(i);
	}

	double minX, maxX, minY, maxY, minZ, maxZ;
	minX = (*triangles)[0].getP0().getX();
	maxX = (*triangles)[0].getP0().getX();
	minY = (*triangles)[0].getP0().getY();
	maxY = (*triangles)[0].getP0().getY();
	minZ = (*triangles)[0].getP0().getZ();
	maxZ = (*triangles)[0].getP0().getZ();

    for (Triangle triangle : (*triangles)) {
		maxX = fmax(triangle.getP0().getX(), maxX);
		minX = fmin(triangle.getP0().getX(), minX);
		maxX = fmax(triangle.getP1().getX(), maxX);
		minX = fmin(triangle.getP1().getX(), minX);
		maxX = fmax(triangle.getP2().getX(), maxX);
		minX = fmin(triangle.getP2().getX(), minX);

		maxY = fmax(triangle.getP0().getY(), maxY);
		minY = fmin(triangle.getP0().getY(), minY);
		maxY = fmax(triangle.getP1().getY(), maxY);
		minY = fmin(triangle.getP1().getY(), minY);
		maxY = fmax(triangle.getP2().getY(), maxY);
		minY = fmin(triangle.getP2().getY(), minY);

		maxZ = fmax(triangle.getP0().getZ(), maxZ);
		minZ = fmin(triangle.getP0().getZ(), minZ);
		maxZ = fmax(triangle.getP1().getZ(), maxZ);
		minZ = fmin(triangle.getP1().getZ(), minZ);
		maxZ = fmax(triangle.getP2().getZ(), maxZ);
		minZ = fmin(triangle.getP2().getZ(), minZ);
    }
	int maxLevel = (int) std::fmin(log2(triangles->size()), MAX_LEVEL);
	int minTriangle = MIN_TRIANGLE;
	cout << "KdTree::KdTree() Max Level = " << maxLevel << "\n";
	cout << "KdTree::KdTree() Min Triangle/node = " << minTriangle << "\n";

	initNode = new Node(trianglePointers, this, AABB(Point(minX, minY, minZ), Point(maxX, maxY, maxZ)), 0, 0, maxLevel, minTriangle);
}

vector<int> KdTree::getTriangle(Ray ray) {
	return initNode->getTriangle(ray);
}

vector<Ray> KdTree::getLines(Ray ray)
{
	return initNode->getLines(ray);
}

KdTree::Node::Node() {}

KdTree::Node::Node(vector<int> triangles, KdTree * root, AABB aabb, int level, int dimension, int maxLevel, int minTriangle) {
	this->triangles = triangles;
	this->root = root;
	this->aabb = aabb;
	this->level = level;
	this->dimension = dimension;

	if (level < maxLevel && triangles.size() > minTriangle) {
		double splitPoint = generateSplit(triangles);

		vector<int> leftindices;
		vector<int> rightindices;

		AABB aabbLeft;
		AABB aabbRight;
		if (dimension == 0) {
			aabbLeft = AABB(aabb.min, Point(splitPoint, aabb.max.getY(), aabb.max.getZ()));
			aabbRight = AABB(Point(splitPoint, aabb.min.getY(), aabb.min.getZ()), aabb.max);
		} else if (dimension == 1) {
			aabbLeft = AABB(aabb.min, Point(aabb.max.getX(), splitPoint, aabb.max.getZ()));
			aabbRight = AABB(Point(aabb.min.getX(), splitPoint, aabb.min.getZ()), aabb.max);
		} else {
			aabbLeft = AABB(aabb.min, Point(aabb.max.getX(), aabb.max.getY(), splitPoint));
			aabbRight = AABB(Point(aabb.min.getX(), aabb.min.getY(), splitPoint), aabb.max);
		}

		for (int index: triangles) {
			if (aabbLeft.isIntersect((*root->triangles)[index])) {
				leftindices.push_back(index);
			}
			if (aabbRight.isIntersect((*root->triangles)[index])) {
				rightindices.push_back(index);
			}
		}

		if (dimension == 2) {
			dimension = 0;
		} else {
			dimension++;
		}

		left = new Node(leftindices, root, aabbLeft, level + 1, dimension, maxLevel, minTriangle);
		right = new Node(rightindices, root, aabbRight, level + 1, dimension, maxLevel, minTriangle);
	} else {
		this->triangles = triangles;
		leaf = true;
	}
}

vector<int> KdTree::Node::getTriangle(Ray ray) {
	vector<int> triangleIndices;

	if (aabb.isIntersect(ray)) {
		if (leaf) {
			for (int index : triangles) {
				triangleIndices.push_back(index);
			}
		} else {
            vector<int> leftIndices = left->getTriangle(ray);
            vector<int> rightIndices = right->getTriangle(ray);

			for (int index : leftIndices) {
				triangleIndices.push_back(index);
			}
			for (int index : rightIndices) {
				triangleIndices.push_back(index);
			}
		}
	}

	return triangleIndices;
}

vector<Ray> KdTree::Node::getLines(Ray ray)
{
	vector<Ray> lines;

	if (aabb.isIntersect(ray)) {
		if (leaf) {
			for (Ray line : aabb.getLines()) {
				lines.push_back(line);
			}
		} else {
			vector<Ray> leftLines = left->getLines(ray);
			vector<Ray> rightLines = right->getLines(ray);

			for (Ray line : leftLines) {
				lines.push_back(line);
			}
			for (Ray line : rightLines) {
				lines.push_back(line);
			}
		}
	}

	return lines;
}

double KdTree::Node::generateSplit(vector<int> triangles) {
	map<double, int> map;

	for (int index : triangles) {
		map[(*root->triangles)[index].getCentroid().getDimension(dimension)] = index;
	}

	std::map<double, int>::iterator iterator = map.begin();
	advance(iterator, map.size() / 2);
	return (*root->triangles)[iterator->second].getCentroid().getDimension(dimension);
}
