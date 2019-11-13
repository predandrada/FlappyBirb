#include <vector>
#include <iostream>
#include "Objects.h"
#include <Core/Engine.h>

Mesh* Objects::createWing(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices = {
		VertexFormat(corner + glm::vec3(0, 0.5*length, 0), color),
		VertexFormat(corner + glm::vec3(0.25*length, 0.25*length, 0), color),
		VertexFormat(corner + glm::vec3(0.5*length, 0.5*length, 0), color),
		
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = {
		0, 1, 2,
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