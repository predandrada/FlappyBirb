#pragma once
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects {
	Mesh* createBirb(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* createWing(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* createFloor(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* createPipe(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* createStar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
}