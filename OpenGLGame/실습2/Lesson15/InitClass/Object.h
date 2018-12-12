#pragma once
#include"Renderer.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Object
{
public:
	Object(const Transform& pos, const float size);
	Object(const Transform& pos, Transform& rotation, const int angle ,const float size);
	Object(const Transform& pos, Transform& rotation ,const Color& color,const float size, const int angle);
	void Release();
	void Init();
	~Object();
//------------------------------Set------------------------------------
	void SetTransform(const Transform& pos);
	void SetRotation(const Transform& pos, int angle);
	void SetColor(const Color& color);
	void SetSpeed(const float speed);
	void SetSize(const float size);
	void SetShape(const int shape);
//--------------------------------Get----------------------------------
	Transform GetTransform();
	Color GetColor();
	float GetSize() { return m_size; }
//---------------------------------------------------------------------------------
	virtual void Render();
	void Move(Transform& target);

private:
	Transform direction[4] = {
	{ 0.0f,1.0f,0.0f },
	{ 0.0f,-1.0f,0.0f },
	{ -1.0f,0.0f,0.0f },
	{ 1.0f,0.0f,0.0f }
	};
	//----------위치-----------
	Transform m_transform;
	Transform m_rotation;//방향전환을 위해
	int m_angle;
	Transform m_startPosition;

	//-----------------------------


	Renderer* m_renderer;
	Color m_color;
	float m_size;
	float m_speed;
	int m_shape;
	
};

