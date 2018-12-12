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
	Object(const Transform& pos, Transform& rotation ,const Color& color,const float size, const int angle);
	void Release();
	~Object();
//------------------------------Set------------------------------------
	void SetTransform(const Transform& pos);
	void SetRotation(const Transform& pos, int angle);
	void SetColor(const Color& color);
	void SetSpeed(const float speed);
	void SetSize(const float size);
//--------------------------------Get----------------------------------
	Transform GetTransform();
	Color GetColor();
	float GetSize() { return m_size; }
//---------------------------------------------------------------------------------
	virtual void Render(char shape);
	virtual void Move(Transform& direction);
	void Move(char shape, MousePosition* mouseposList, int size);
	void Move(char shape);

private:
	Transform direction[4] = {
	{ 0.0f,1.0f,0.0f },
	{ 0.0f,-1.0f,0.0f },
	{ -1.0f,0.0f,0.0f },
	{ 1.0f,0.0f,0.0f }
	};
	//----------��ġ-----------
	Transform m_transform;
	Transform m_rotation;//������ȯ�� ����
	Transform m_startPosition;
	int m_angle;
	//-----------------------------

	char m_shape;
	Renderer* m_renderer;
	Color m_color;
	float m_size;
	float m_speed;
	int m_circleMoving;//�� �̵�
	float m_pivotX = 0;//���� �̵�
	float m_lineDist = 0.05;
	float m_lineX = -1.0f;
	float m_lineY = 0.0f;//�������
	Transform m_target;
	int m_currentIndex = 1;//�����̵�
	
	float m_tonadoRadius=0.005;
};

