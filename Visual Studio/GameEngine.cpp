#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "GameEngine.h"
#include "TransformMatrix.h"
#include "Objects.h"

GameEngine::GameEngine() {}
GameEngine::~GameEngine() {}

void GameEngine::Init() {
	
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	
	// colors
	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 birbColor = glm::vec3(1, 0.93f, 0.54f);
	glm::vec3 wingColor = glm::vec3(1, 0.8f, 0.2f);
	glm::vec3 floorColor = glm::vec3(0.804f, 0.973f, 0.945f);
	glm::vec3 pipeColor = glm::vec3(0.584f, 0.616f, 0.698f);
	glm::vec3 starColor = glm::vec3(1, 0.93f, 0.54f);

	// measurements
	sizeUnit = 100;
	translateX = 100;
	translateY = 350;
	rotate = 0;
	scaleWingX = 1;
	scaleWingY = 0;
	
	pipeX = 600;
	pipeY = -100;

	speed = 12;
	velocity = 0;
	score = 5;

	Mesh* birb = Objects::createBirb("birb", corner, sizeUnit, birbColor, true);
	AddMeshToList(birb);

	Mesh* wing = Objects::createWing("wing", corner, sizeUnit, wingColor, true);
	AddMeshToList(wing);

	Mesh* floor = Objects::createFloor("floor", corner, sizeUnit, floorColor, true);
	AddMeshToList(floor);

	Mesh* pipe = Objects::createPipe("pipe", corner, sizeUnit, pipeColor, true);
	AddMeshToList(pipe);

	Mesh* star = Objects::createStar("star", corner, sizeUnit, starColor , true);
	AddMeshToList(star);
}

void GameEngine::FrameStart() {
	glClearColor(0.098f, 0.071f, 0.247f, 1);
	//glClearColor(0.149f, 0.106f, 0.384f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void GameEngine::Update(float deltaTimeSeconds) {
	
	// to keep the height of the pipes random we use the extra[] values
	for (i = 0; i < 5; i++) {
		pipe_positionsY[i] = pipeY + extra[i] * 15 + 490;
	}
	
	// the game stops and the screen freezes
	if (gameOver) {
		isPlaying = false;
	}

	// birb movement
	if (isPlaying) {
		// gravity
		translateY += speed * velocity * deltaTimeSeconds;
		velocity -= 0.5f;
		// rotation
		rotate += speed * velocity*deltaTimeSeconds/130;
		if (rotate > 0.3f) {
			rotate = 0.3f;
		}
		if (rotate < -1.5f) {
			rotate = -1.5f;
		}

		// wing animation
		if (velocity > 0) {
			scaleWingY += 0.008f;
		}
		else {
			scaleWingY -= 0.008f;
		}

		// checking collisions
		for (int i = 0; i < 5; i++) {
			if (pipe_positionsX[i] >= 0 && pipe_positionsX[i] <= translateX + 0.75f*sizeUnit) {
				if (translateY >= pipe_positionsY[i] - 55
					|| translateY <= pipe_positionsY[i] - 220) {
					std::cout << "Oh no! Your birb crashed. GAME OVER.\n";
					std::cout << "Your final score is: " << score;
					gameOver = true;
					break;
				}
			}
		}

		// pipe endless movement
		for (i = 0; i < 5; i++) {
			pipe_positionsX[i] -= 100 * deltaTimeSeconds;
			if (pipe_positionsX[i] < -150) {
				pipe_positionsX[i] = 1300;
				// keeping the pipes' random height
				extra[i] = rand() % 10;
				score += 5;
				std::cout << "Your current score is: " << score << "\n";
			}
		}
	}
	
	// birb
	birbMatrix = glm::mat3(1);
	birbMatrix *= TransformMatrix::Translate(translateX, translateY);
	birbMatrix *= TransformMatrix::Scale(0.6f, 0.6f);
	birbMatrix *= TransformMatrix::Translate(50, 30);
	birbMatrix *= TransformMatrix::Rotate(rotate);
	birbMatrix *= TransformMatrix::Translate(-50, -30);
	
	// wing
	wingMatrix = glm::mat3(1);
	wingMatrix *= TransformMatrix::Translate(translateX, translateY + 2);
	wingMatrix *= TransformMatrix::Scale(0.6f, 0.6f);
	wingMatrix *= TransformMatrix::Translate(55, 30);
	wingMatrix *= TransformMatrix::Rotate(scaleWingY);
	wingMatrix *= TransformMatrix::Translate(-55, -30);
	wingMatrix *= TransformMatrix::Translate(50, 30);
	wingMatrix *= TransformMatrix::Rotate(rotate);
	wingMatrix *= TransformMatrix::Translate(-50, -30);

	// pipes again
	for (i = 0; i < 5; i++) {
		pipeMatrix = glm::mat3(1);
		pipeMatrix *= TransformMatrix::Translate(pipe_positionsX[i], pipe_positionsY[i]);
		RenderMesh2D(meshes["pipe"], shaders["VertexColor"], pipeMatrix);
		pipeMatrix *= TransformMatrix::Translate(0, -560);
		RenderMesh2D(meshes["pipe"], shaders["VertexColor"], pipeMatrix);
	}

	//floor
	floorMatrix = glm::mat3(1);
	RenderMesh2D(meshes["floor"], shaders["VertexColor"], floorMatrix);
	RenderMesh2D(meshes["wing"], shaders["VertexColor"], wingMatrix);
	RenderMesh2D(meshes["birb"], shaders["VertexColor"], birbMatrix);
	
	// stars
	// i really like stars
	starMatrix = glm::mat3(1);
	starMatrix *= TransformMatrix::Translate(100, 600);
	starMatrix *= TransformMatrix::Scale(0.2f, 0.2f);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(600, 50);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(200, -200);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(500, -50);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(600, 100);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(250, -200);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(500, 250);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(600, -80);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(210, 120);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(500, -370);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(630, 150);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(100, -200);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
	starMatrix *= TransformMatrix::Translate(500, 500);
	RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);

}

void GameEngine::FrameEnd() {}
void GameEngine::OnInputUpdate(float deltaTime, int mods) {
	if (window->KeyHold(GLFW_KEY_SPACE)) {
		// BIRB UP!!!
		velocity = 20;
	}
}

void GameEngine::OnKeyPress(int key, int mods) {
	if (window->KeyHold(GLFW_KEY_ENTER)) {
		isPlaying = true;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		isPlaying = false;
	}
}
void GameEngine::OnKeyRelease(int key, int mods) {}
void GameEngine::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {}
void GameEngine::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}
void GameEngine::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}
void GameEngine::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}
void GameEngine::OnWindowResize(int width, int height) {}