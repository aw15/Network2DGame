#pragma once
#include"Renderer.h"

class Object
{
public:
	Object(const Transform& pos ,const Color& color,const float size);
	void SetTransform(const Transform& pos, const float size);
	void GetTransform(Transform & pos);
	void SetColor(const Color& color);
	void GetColor(Color& color);
	float GetSize() { return m_size; }
	virtual void Render();

	virtual void Move(float speed, Transform& direction);
	void Release();
	~Object();

private:
	Transform m_transform;
	Renderer* m_renderer;
	Color m_color;
	float m_size;
	
};

