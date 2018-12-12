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
	void Release();
	~Object();
//------------------------------Set------------------------------------
	void SetTransform(const Transform& pos);
	void SetCurrentDir(const Transform& pos);
	void SetColor(const Color& color);
	void SetSpeed(const float speed);
	void SetSize(const int size);
	void ColorLesser(const float color);
//--------------------------------Get----------------------------------
	Transform GetTransform();
	Color GetColor();
	float GetSize() { return m_size; }
//---------------------------------------------------------------------------------
	virtual void Render(char shape);
	virtual void Start(const float& speed);


	void Move();
	virtual void Move(Transform& direction);

private:
	Transform direction[4] = {
	{ 0.0f,1.0f,0.0f },
	{ 0.0f,-1.0f,0.0f },
	{ -1.0f,0.0f,0.0f },
	{ 1.0f,0.0f,0.0f }
	};
	//----------위치-----------
	Transform m_transform;
	Transform m_currentMoveDir;//방향전환을 위해
	Transform m_startPosition;
	//-----------------------------


	char m_shape;
	Renderer* m_renderer;
	Color m_color;
	float m_size;
	float m_speed;
};

