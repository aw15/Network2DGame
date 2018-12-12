#include "stdafx.h"
#include "Object.h"



Object::Object(const Transform& pos ,const float size)
{
	m_color = { 1,1,1,1 };
	m_transform = pos;
	m_rotation = { 0,0,0 };
	m_angle = 0;
	m_size = size;
	Init();
}

Object::Object(const Transform & pos, Transform & rotation, const int angle, const float size)
{
	m_color = { 1,1,1,1 };
	m_transform = pos;
	m_rotation = rotation;
	m_angle = angle;
	m_size = size;
	Init();
}

Object::Object(const Transform & pos, Transform & rotation, const Color & color, const float size, const int angle)
{
	m_transform = pos;
	m_rotation = rotation;
	m_color = color;
	m_size = size;
	m_angle = angle;
	Init();
}

void Object::Init()
{
	
	m_renderer = new Renderer;
	m_startPosition.x = m_transform.x;
	m_startPosition.y = m_transform.y;
	
}

void Object::SetTransform(const Transform& pos)
{
	m_transform = pos;
}

void Object::SetRotation(const Transform & pos, int angle)
{
	m_angle = angle;
	m_rotation = pos;
}

Transform Object::GetTransform()
{
	return m_transform;
}

void Object::SetColor(const Color & color)
{
	m_color = color;
}

Color Object::GetColor()
{
	return m_color;
}

void Object::SetSpeed(const float speed)
{
	m_speed += speed;
}

void Object::SetSize(const float size)
{
	if (m_size > 0)
		m_size = size;
	else
		m_size = 0;
}

void Object::SetShape(const int shape)
{
	m_shape = shape;
}

void Object::Render()										
{
	m_renderer->DrawShape(m_shape,m_transform,m_rotation,m_angle,m_size,m_color);
}

void Object::Move(Transform & target)
{
	m_angle += 30;
	Transform direction = target - m_transform;
	direction.Normalize();
	//m_transform.x += direction.x*0.1;
	//m_transform.y += direction.y*0.1;
	m_transform.z += 0.1;
	m_size += 0.3;

}

																	
														


					
void Object::Release()																							
{
	delete m_renderer;
}



Object::~Object()
{
}
