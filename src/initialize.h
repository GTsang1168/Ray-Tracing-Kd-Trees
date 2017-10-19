/**
\class Initialize
\brief Parses the .OBJ and .MTL file.

This class parses the indicated file into an application readable format and stores the data in a DataStructure class which can then be 
retrieved at a later point. This class uses the external tinyobj class to parse the models.

\author Gavin Tsang
\date 16/02/2015
\see http://syoyo.github.io/tinyobjloader/
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "tiny_obj_loader.h"
#include "DataStructure.h"
#include "Triangle.h"

#define SHAPE_SIZE 200

using namespace std;
using namespace tinyobj;

class Initialize {
	public:
		Initialize(string fileName, DataStructure * dataStructure);
	private:
		vector<shape_t> m_polygon;
		vector<material_t> m_material;
		vector<Triangle> triangles;

		int fileLoad(string fileName);
		int saveDataStructure(DataStructure * dataStructure);
};
