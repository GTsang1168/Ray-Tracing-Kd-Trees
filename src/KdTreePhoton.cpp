#include "KdTreePhoton.h"

KdTreePhoton::KdTreePhoton()
{

}

KdTreePhoton::KdTreePhoton(vector<PhotonPoint> photons)
{
	this->photons = photons;

	vector<int> photonPointers;
	for (int i = 0; i < photons.size(); i++) {
		photonPointers.push_back(i);
	}

	double minX, maxX, minY, maxY, minZ, maxZ;
	minX = photons[0].getLocation().getX();
	maxX = photons[0].getLocation().getX();
	minY = photons[0].getLocation().getY();
	maxY = photons[0].getLocation().getY();
	minZ = photons[0].getLocation().getZ();
	maxZ = photons[0].getLocation().getZ();

	for (PhotonPoint photon : photons) {
		maxX = fmax(photon.getLocation().getX(), maxX);
		minX = fmin(photon.getLocation().getX(), minX);

		maxY = fmax(photon.getLocation().getY(), maxY);
		minY = fmin(photon.getLocation().getY(), minY);

		maxZ = fmax(photon.getLocation().getZ(), maxZ);
		minZ = fmin(photon.getLocation().getZ(), minZ);
	}
	int maxLevel = (int) std::fmin(log2(photons.size()), MAX_LEVEL);
	int minPoints = MIN_PHOTONS;

	rootNode = new Node(photonPointers, this, 0, 0);
}

KdTreePhoton::~KdTreePhoton()
{

}

vector<PhotonPoint> KdTreePhoton::getKNNPhoton(Point location, int k)
{
	vector<PhotonPoint> photons;

	Node * currentNode = rootNode;
	while(!currentNode->leaf) {
		int dimension = currentNode->dimension;
		Point point = currentNode->splitPoint.getLocation();

		if(location.getDimension(dimension) <= point.getDimension(dimension)) {
			currentNode = currentNode->left;
		} else {
			currentNode = currentNode->right;
		}
	}

	Node * bestNode = currentNode;
	double bestDistance = bestNode->splitPoint.getLocation().distance(location);

	while(currentNode->parent != nullptr) {
		currentNode->parent = currentNode;
		if(currentNode->splitPoint.getLocation().distance(location) < bestDistance) {
			bestNode = currentNode;
			bestDistance = bestNode->splitPoint.getLocation().distance(location);
		}
		int dimension = currentNode->dimension;
		double distance = std::abs(currentNode->splitPoint.getLocation().getDimension(dimension) - location.getDimension(dimension));
		if(distance < bestDistance) {
		}
	}

	return photons;
}



KdTreePhoton::Node::Node(vector<int> photons, KdTreePhoton *root, int level, int dimension, Node *parent)
{
	this->root = root;
	this->level = level;
	this->dimension = dimension;
	this->parent = parent;
	splitPoint = generateSplit(photons);

	if (photons.size() > 1) {
		vector<int> leftindices;
		vector<int> rightindices;

		for (int index: photons) {
			if (root->photons[index].getLocation() == splitPoint.getLocation()) {}
			else if (root->photons[index].getLocation().getDimension(dimension) <= splitPoint.getLocation().getDimension(dimension)) {
				leftindices.push_back(index);
			}
			else if (root->photons[index].getLocation().getDimension(dimension) > splitPoint.getLocation().getDimension(dimension)) {
				rightindices.push_back(index);
			}
		}

		if (dimension == 2) {
			dimension = 0;
		} else {
			dimension++;
		}

		left = new Node(leftindices, root, level + 1, dimension, this);
		right = new Node(rightindices, root, level + 1, dimension, this);
	} else {
		leaf = true;
	}
}

PhotonPoint KdTreePhoton::Node::generateSplit(vector<int> photons)
{
	if(photons.size() == 1) {
		return root->photons[0];
	} else {
		map<double, int> map;

		for (int index : photons) {
			map[root->photons[index].getLocation().getDimension(dimension)] = index;
		}

		std::map<double, int>::iterator iterator = map.begin();
		advance(iterator, map.size() / 2);
		return root->photons[iterator->second];
	}
}
