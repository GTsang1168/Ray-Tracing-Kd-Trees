#ifndef KDTREEPHOTON_H
#define KDTREEPHOTON_H

#include <map>

#include "PhotonPoint.h"
#include "Point.h"
#include "AABB.h"

#define MIN_PHOTONS 1
#define MAX_LEVEL 50

class KdTreePhoton
{
public:
    KdTreePhoton();
	KdTreePhoton(vector<PhotonPoint> photons);
    ~KdTreePhoton();

	vector<PhotonPoint> getKNNPhoton(Point location, int k);

private:
	class Node
	{
	public:
		Node(vector<int> photons, KdTreePhoton * root, int level, int dimension, Node * parent = nullptr);

		int level;
		Node * left = nullptr;
		Node * right = nullptr;
		Node * parent = nullptr;
		int dimension = 0;
		KdTreePhoton * root;
		PhotonPoint splitPoint;
		bool leaf = false;

	private:
		PhotonPoint generateSplit(vector<int> photons);
	};

	vector<PhotonPoint> photons;
	Node * rootNode;
};

#endif // KDTREEPHOTON_H
