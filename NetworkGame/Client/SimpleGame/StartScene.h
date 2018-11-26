#pragma once
class StartScene : public Scene
{
public:
	 StartScene(Renderer* renderer);
	 ~StartScene();
	 bool Initialize();
	 void Render();
	void Update();
	 STATE GetState();
	 void KeyInput(unsigned char key);
	 void KeyUpInput(unsigned char key);
	 void MouseInput(int button, int state, int x, int y);
	 void CleanUp();

private:
	STATE mState = STATE::GamePlay;


};

