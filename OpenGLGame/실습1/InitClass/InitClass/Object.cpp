#include "stdafx.h"
#include "Object.h"


Object::Object(const Transform& pos, const Color& color, const float size)
{
	m_transform = pos;
	m_color = color;
	m_size = size;
	m_renderer = new Renderer;
}


void Object::SetTransform(const Transform& pos, const float size)
{
	m_transform = pos;
	m_size = size;
}

void Object::GetTransform(Transform & pos)
{
	pos = m_transform;
}

void Object::SetColor(const Color & color)
{
	m_color = color;
}

void Object::GetColor(Color & color)
{
	color = m_color;
}																	
																	
void Object::Render()												
{																
	glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
	m_renderer->DrawRect(m_transform.x, m_transform.y, m_size);
}																	
																	
																	
																	
																	
void Object::Move(float speed, Transform & direction)				
{																	
	m_transform.x += direction.x*speed;								
	m_transform.y += direction.y*speed;								
	m_transform.z += direction.z*speed;								
}																	
																	
void Object::Release()
{
	delete m_renderer;
}

Object::~Object()
{
}
