#pragma once
#include"Renderer.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Object
{
public:
	Object();
	Object(const Transform& pos, const float size);
	Object(const Transform& pos ,const Color& color,const float size);
	void SetTransform(const Transform& pos, const float size);
	void GetTransform(Transform & pos);
	void SetColor(const Color& color);
	void GetColor(Color& color);
	void SetSpeed(const float speed);
	float GetSize() { return m_size; }
	virtual void Render(char shape);

	void Move();
	virtual void Move(Transform& direction);
	void Release();
	~Object();

private:
	Transform direction[4] = {
	{ 1.0f,2.0f,0.0f },
	{ -1.0f,-2.0f,0.0f },
	{ 2.0f,-1.0f,0.0f },
	{ -2.0f,1.0f,0.0f }
	};
	Transform m_transform;
	Transform currentMoveDir;
	Renderer* m_renderer;
	Color m_color;
	float m_size;
	float m_speed;
};

