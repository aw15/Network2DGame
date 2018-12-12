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
	void Release();
	void Init();
	~Object();
//------------------------------Set------------------------------------
	void SetTransform(const Transform& pos);
	void SetPosition(const Transform& pos);
	void SetRotation(const Transform& pos, int angle);
	void SetColor(const Color& color);
	void SetSpeed(const Transform& speed);
	void SetSize(const Transform& size);
	void SetShape(const int shape);
//--------------------------------Get----------------------------------
	void GetTransform(vector<Transform>& pos);
	Color GetColor();
	void GetPosition(Transform& pos);
	Transform GetSize() { return m_size; }
//---------------------------------------------------------------------------------
	virtual void Render(int shape);
	virtual void Move();

protected:
	Transform direction[4] = {
	{ 0.0f,1.0f,0.0f },
	{ 0.0f,-1.0f,0.0f },
	{ -1.0f,0.0f,0.0f },
	{ 1.0f,0.0f,0.0f }
	};
	//----------위치-----------
	vector<Transform> m_transform;
	Transform m_position;
	Transform m_rotation;//방향전환을 위해
	int m_angle;
	//-----------------------------
	Renderer* m_renderer;
	Color m_color;
	Transform m_size;
	Transform m_speed;
	int m_shape;

};

class Rect:public Object
{
	public:
		Rect();
		void SetTransform(const Transform& max, const Transform& min);
		void GetTransform(Transform& max, Transform& min);
		void Move();
		void Render();
	private:
		Transform m_max;
		Transform m_min;
};

