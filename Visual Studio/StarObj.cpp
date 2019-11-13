#include <vector>
#include <iostream>
#include "Objects.h"
#include <Core/Engine.h>

Mesh* Objects::createStar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices = {
		VertexFormat(corner + glm::vec3(length/6, 0, 0), color),
		VertexFormat(corner + glm::vec3(length/2, length/6, 0), color),
		VertexFormat(corner + glm::vec3(5*length/6, 0, 0), color),
		VertexFormat(corner + glm::vec3(2 * (length+10) / 3, length/3, 0), color),
		VertexFormat(corner + glm::vec3(length, 2*length/3, 0), color),
		VertexFormat(corner + glm::vec3(2*length / 3, 2*length/3, 0), color),
		VertexFormat(corner + glm::vec3(length / 2, length, 0), color),
		VertexFormat(corner + glm::vec3(length/3, 2 * length / 3, 0), color),
		VertexFormat(corner + glm::vec3(0, 2*length/3, 0), color),
		VertexFormat(corner + glm::vec3((length-15)/3, length/3, 0), color),

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = {
		9, 0, 1,
		1, 2, 3,
		3, 4, 5,
		5, 6, 7,
		7, 8, 9, 
		9, 1, 3,
		9, 3, 5,
		5, 7, 9
	};

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}
