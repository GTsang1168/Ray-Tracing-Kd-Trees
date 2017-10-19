#include "initialize.h"

using namespace std;
using namespace tinyobj;

Initialize::Initialize(string fileName, DataStructure * dataStructure) {
	cout << "Initialize::Initialize() Loading file: " << fileName << "\n";
	int error = fileLoad(fileName);
	if(error == 1) {
		cout << "Initialize::Initialize() File loaded sucessfully\n";
	} else {
		cout << "Initialize::Initialize() Error in loading file\n";
        throw 0;
	}

	cout << "Initialize::Initialize() Saving data\n";
	error = saveDataStructure(dataStructure);
	if(error == 1) {
		cout << "Initialize::Initialize() Data saved sucessfully\n";
	} else {
		cout << "Initialize::Initialize() Error in saving data\n";
	}
}

int Initialize::fileLoad(string fileName) {
	string error = LoadObj(m_polygon, m_material, fileName.c_str());

	if(error.empty()) {
		return 1;
	} else {
		cout << "Initialize::fileLoad() " << error;
		return 0;
	}
}

int Initialize::saveDataStructure(DataStructure * dataStructure) {
	for (shape_t shape : m_polygon) {
		for (int i = 0; i < shape.mesh.indices.size() / 3; i++) {
			int indices[3];
			indices[0] = shape.mesh.indices[3 * i + 0];
			indices[1] = shape.mesh.indices[3 * i + 1];
			indices[2] = shape.mesh.indices[3 * i + 2];

			double trianglePosition[9];
			for (int j = 0; j < 3; j++) {
				trianglePosition[3 * j + 0] = shape.mesh.positions[3 * indices[j] + 0];
				trianglePosition[3 * j + 1] = shape.mesh.positions[3 * indices[j] + 1];
				trianglePosition[3 * j + 2] = shape.mesh.positions[3 * indices[j] + 2];
			}

			triangles.push_back(Triangle(trianglePosition, shape.mesh.material_ids[0]));
		}
	}
	cout << "Initialize::saveDataStructure() No. of triangles = " << triangles.size() << "\n";
	(*dataStructure).setPolygon(triangles);
	(*dataStructure).setMaterial(m_material);
	return 1;
}
