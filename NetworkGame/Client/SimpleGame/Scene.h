#pragma once
class Scene
{
public:
	Scene();
	~Scene();
	virtual bool Initialize() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual STATE GetState() = 0;
    virtual	void KeyInput(unsigned char key) = 0;
	virtual void KeyUpInput(unsigned char key) = 0;
	virtual void MouseInput(int button, int state, int x, int y) = 0;

};

