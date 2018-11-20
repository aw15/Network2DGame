#pragma once
class StartScene : public Scene
{
public:
	StartScene(Renderer* renderer);
	~StartScene();
	virtual bool Initialize();
	virtual void Render();
	virtual void Update();
	virtual STATE GetState();
	virtual	void KeyInput(unsigned char key);
	virtual void KeyUpInput(unsigned char key);
	virtual void MouseInput(int button, int state, int x, int y);

private:
	Renderer* mRenderer;
	GLuint mStartPage;
};

