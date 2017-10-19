		//http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_7_Kd-Trees_and_More_Speed.shtml
//http://www.cplusplus.com/reference/map/multimap/

#include "DataStructure.h"

using namespace std;
using namespace tinyobj;

DataStructure::DataStructure() {
	defaultMaterial = generateDefaultMaterial();
}

void DataStructure::setAccelerateKdTree(bool accelerate) {
	accelerateKdTree = accelerate;
}

bool DataStructure::isAccelerateKdTree() {
	return accelerateKdTree;
}

void DataStructure::setPolygon(vector<Triangle> polygon) {
	triangle = polygon;
	for(int dimension = 0; dimension < 3; dimension++) {
		setMaxSize(fmax(getMaxSize(), getMaxPoint(dimension)));
		setMinSize(fmax(getMinSize(), getMinPoint(dimension)));
	}
	cout << "DataStructure::setPolygon() " << triangle.size() << " triangles saved\n";
}

void DataStructure::setMaterial(vector<material_t> material) {
	m_material = material;
}

material_t DataStructure::getMaterial(int index) {
    if(index > 0) {
        return m_material[index];
    } else {
        return defaultMaterial;
    }
}

vector<Intersection> DataStructure::getIntersection(Ray ray) {
	if(DataStructure::isAccelerateKdTree()) {
		if (!kdTreeGenerated) {
			cout << "DataStructure::getIntersectionKd() Kd-Tree has not been generated";
			return intersectionNoKd(ray);
		} else {
			return DataStructure::intersectionKd(ray);
		}
	} else {
		return DataStructure::intersectionNoKd(ray);
	}
}

//http://www.gamedev.net/topic/589705-rayline-intersection-in-3d/
vector<IntersectionLine> DataStructure::getIntersectionLine(Ray ray)
{
	vector<IntersectionLine> lineIntersections;
	vector<Ray> lines = kdTree.getLines(ray);

	for(Ray line: lines) {
		Vector u = ray.getEndPoint() - ray.getOriginPoint();
		Vector v = line.getEndPoint() - line.getOriginPoint();
		Vector w = ray.getOriginPoint() - line.getOriginPoint();
		double a = u.dot(u);
		double b = u.dot(v);
		double c = v.dot(v);
		double d = u.dot(w);
		double e = v.dot(w);
		double D = a * c - b * b;
		double sc, sN, sD = D;
		double tc, tN, tD = D;

		//Lines are parallel
		if (D < 0.000001) {
			sN = 0;
			sD = 1;
			tN = e;
			tD = c;
		//Closest point on infinite lines
		} else {
			sN = b * e - c * d;
			tN = a * e - b * d;
			if (sN < 0) {
				sN = 0;
				tN = e;
				tD = c;
			}
		}

		//Closest point lies past lower limit of line segment
		if (tN < 0) {
			tN = 0;
			if(-d < 0) {
				sN = 0;
			} else {
				sN = -d;
				sD = a;
			}
		//Closest point lies past upper limit of line segment
		} else if (tN > tD) {
			tN = tD;
			if ((-d + b) < 0) {
				sN = 0;
			} else {
				sN = -d + b;
				sD = a;
			}
		}

		//Calculate fraction of where closest point is:
		//on the ray
		sc = (fabs(sN) < 0.000001 ? 0.0f : sN / sD);
		//on the line segment
		tc = (fabs(tN) < 0.000001 ? 0.0f : tN / tD);

		//Vector between the two points of closest approach
		Vector dP = w + (u * sc) - (v * tc);

		//Distance of closest approach vector
		double distance = sqrt(dP.dot(dP));

		//Distance is less than an acceptable margin of error
		//(Also dictates width of lines to be drawn)
		if(distance < (getMaxSize() - getMinSize()) * 0.005) {
			lineIntersections.push_back(IntersectionLine(line, sc));
		}
	}

	return lineIntersections;
}

vector<Light> DataStructure::getLights() {
	return lights;
}

void DataStructure::setLights(vector<Light> lights) {
	this->lights = lights;
}

//Naive split position heuristic
void DataStructure::generateKdTree() {
	kdTreeGenerated = true;
	kdTree = KdTree(&triangle);
}

vector<Intersection> DataStructure::intersectionKd(Ray ray) {
	vector<Intersection> intersections;
	vector<int> triangleIndeces = kdTree.getTriangle(ray);

	Point point;
	double distance;
	for (int index : triangleIndeces) {
		distance = intersection(ray, triangle[index], &point);
		if (distance > 0) {
			intersections.push_back(Intersection(point, &triangle[index], distance));
		}
	}

	return intersections;
}

vector<Intersection> DataStructure::intersectionNoKd(Ray ray) {
	vector<Intersection> intersections;
	Point point;
	double distance;
	for (int i = 0; i < triangle.size(); i++) {
		distance = intersection(ray, triangle[i], &point);
		if (distance > 0) {
			intersections.push_back(Intersection(point, &triangle[i], distance));
		}
	}
	return intersections;
}

//returns distance from ray.getP0()
double DataStructure::intersection(Ray ray, Triangle triangle, Point * intPoint) {
	Vector dir = ray.getEndPoint() - ray.getOriginPoint();
	Vector w0 = ray.getOriginPoint() - triangle.getP0();

	//Get correctly facing normal
	if((-triangle.getNormal()).dot(dir) < 0) {
		triangle.setNormal(-triangle.getNormal());
	}

	double a = -(triangle.getNormal().dot(w0));
	double b = triangle.getNormal().dot(dir);

	if (fabs(b) < 0.00001) {
		//is parallel to plane
		return 0;
	}

	double r = a / b;

	if (r < 0.0001) {
		//Points away from triangle
		return 0;
	}

	(*intPoint) = ray.getOriginPoint() + (dir * r);

	double uu = triangle.getU().dot(triangle.getU());
	double uv = triangle.getU().dot(triangle.getV());
	double vv = triangle.getV().dot(triangle.getV());
	Vector w = (*intPoint) - triangle.getP0();
	double wu = w.dot(triangle.getU());
	double wv = w.dot(triangle.getV());
	double d = uv * uv - uu * vv;

	double s = (uv * wv - vv * wu) / d;
	if (s < 0.0 || s > 1.0) {
		//Intersect point outside triangle boundaries
		return 0;
	}
	double t = (uv * wu - uu * wv) / d;
	if (t < 0.0 || (s + t) > 1.0) {
		//Intersect point outside triangle boundaries
		return 0;
	}

	return r;
}

double DataStructure::getMinSize() const
{
	return minSize;
}

void DataStructure::setMinSize(double value)
{
	minSize = value;
}

double DataStructure::getMaxSize() const
{
	return maxSize;
}

void DataStructure::setMaxSize(double value)
{
	maxSize = value;
}


material_t DataStructure::generateDefaultMaterial() {
	material_t material;
	material.ambient[0] = 0.0f;
	material.ambient[1] = 0.0f;
    material.ambient[2] = 0.0f;
    material.diffuse[0] = 0.784314f;
    material.diffuse[1] = 0.784314f;
    material.diffuse[2] = 0.784314f;
    material.specular[0] = 0.215686f;
    material.specular[1] = 0.215686f;
    material.specular[2] = 0.215686f;
    material.emission[0] = 0.0f;
    material.emission[1] = 0.0f;
    material.emission[2] = 0.0f;
    material.dissolve = 1.0f;
    material.shininess = 255.0f;
    return material;
}

double DataStructure::getMaxPoint(int dimension) {
	if(dimension == X) {
		double maxX = triangle[0].getP0().getX();
        for (Triangle tri : triangle) {
			maxX = fmax(tri.getP0().getX(), maxX);
			maxX = fmax(tri.getP1().getX(), maxX);
			maxX = fmax(tri.getP2().getX(), maxX);
        }
        return maxX;
	} else if(dimension == Y) {
		double maxY = triangle[0].getP0().getY();
        for (Triangle tri : triangle) {
			maxY = fmax(tri.getP0().getY(), maxY);
			maxY = fmax(tri.getP1().getY(), maxY);
			maxY = fmax(tri.getP2().getY(), maxY);
        }
        return maxY;
    } else {
		double maxZ = triangle[0].getP0().getZ();
        for (Triangle tri : triangle) {
			maxZ = fmax(tri.getP0().getZ(), maxZ);
			maxZ = fmax(tri.getP1().getZ(), maxZ);
			maxZ = fmax(tri.getP2().getZ(), maxZ);
        }
        return maxZ;
    }
}

double DataStructure::getMinPoint(int dimension) {
	if(dimension == X) {
		double minX = triangle[0].getP0().getX();
        for (Triangle tri : triangle) {
			minX = fmin(tri.getP0().getX(), minX);
			minX = fmin(tri.getP1().getX(), minX);
			minX = fmin(tri.getP2().getX(), minX);
        }
        return minX;
	} else if(dimension == Y) {
		double minY = triangle[0].getP0().getY();
        for (Triangle tri : triangle) {
			minY = fmin(tri.getP0().getY(), minY);
			minY = fmin(tri.getP1().getY(), minY);
			minY = fmin(tri.getP2().getY(), minY);
        }
        return minY;
    } else {
		double minZ = triangle[0].getP0().getZ();
        for (Triangle tri : triangle) {
			minZ = fmin(tri.getP0().getZ(), minZ);
			minZ = fmin(tri.getP1().getZ(), minZ);
			minZ = fmin(tri.getP2().getZ(), minZ);
        }
        return minZ;
	}
}

int DataStructure::getTriangleCount()
{
	return triangle.size();
}
