#pragma once
class EndScene : public Scene
{
public:
	EndScene(Renderer* renderer);
	~EndScene();
	bool Initialize();
	void Render();
	void Update();
	void SetState(STATE state) { mState = state; }
	STATE GetState();
	void KeyInput(unsigned char key);
	void KeyUpInput(unsigned char key);
	void MouseInput(int button, int state, int x, int y);
	void CleanUp();

private:
	STATE mState = STATE::GamePlay;

};

