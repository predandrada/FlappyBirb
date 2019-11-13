#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class GameEngine : public SimpleScene {
	public:
		GameEngine();
		~GameEngine();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 birbMatrix;
		glm::mat3 wingMatrix;
		glm::mat3 floorMatrix;
		glm::mat3 pipeMatrix;
		glm::mat3 starMatrix;


		int extra[5] = { rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10 };
		int i;
		float sizeUnit;
		float pipe_positionsX[5] = {600, 900, 1200, 1500, 1800};
		float pipe_positionsY[5];
	
		float score;
		float translateX, translateY;
		float rotate;
		float scaleWingX, scaleWingY;
		float pipeX, pipeY;
		bool isPlaying = false;
		float speed;
		float velocity;
		bool gameOver = false;
};