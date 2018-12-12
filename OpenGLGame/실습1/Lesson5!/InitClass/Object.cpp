#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	switch (rand() % 5)
	{
	case 0:
		m_color = { 1.0f,0.0f,0.0f,1.0f };
		break;
	case 1:
		m_color = { 0.0f,1.0f,0.0f,1.0f };
		break;
	case 2:
		m_color = { 1.0f,1.0f,0.0f,1.0f };
		break;
	case 3:
		m_color = { 0.0f,0.0f,1.0f,1.0f };
		break;
	case 4:
		m_color = { 0.0f,1.0f,1.0f,1.0f };
		break;
	}

	m_transform = {0.0f,0.0f,0.0f};
	m_size = 50;
	m_renderer = new Renderer;

	currentMoveDir = direction[rand() % 4];
	m_speed = rand() % 20+3;
}

Object::Object(const Transform& pos ,const float size)
{
	srand(time(NULL));
	switch (rand() % 5)
	{
	case 0:
		m_color = { 1.0f,0.0f,0.0f,1.0f };
		break;
	case 1:
		m_color = { 0.0f,1.0f,0.0f,1.0f };
		break;
	case 2:
		m_color = { 1.0f,1.0f,0.0f,1.0f };
		break;
	case 3:
		m_color = { 0.0f,0.0f,1.0f,1.0f };
		break;
	case 4:
		m_color = { 0.0f,1.0f,1.0f,1.0f };
		break;
	}

	m_transform = pos;
	m_size = size;
	m_renderer = new Renderer;

	currentMoveDir = direction[rand() % 4];
	m_speed = rand() % 20+3;
}

Object::Object(const Transform& pos, const Color& color, const float size)
{
	m_transform = pos;
	m_color = color;
	m_size = size;
	m_renderer = new Renderer;

	currentMoveDir = direction[rand() % 4];
	m_speed = rand() % 20+3;
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

void Object::SetSpeed(const float speed)
{
	m_speed += speed;
	if (m_speed <= 0)
		m_speed = 0;
}
																	
void Object::Render(char shape)												
{
	m_renderer->DrawShape(shape,m_transform.x, m_transform.y, m_size,m_color);
}																	
																	
																	
																	
																	
void Object::Move(Transform & direction)				
{																	
	m_transform.x += direction.x*m_speed;								
	m_transform.y += direction.y*m_speed;								
}		
void Object::Move()
{
	
	if (m_transform.y >= 580)
	{
		currentMoveDir = direction[LEFT];
	}
	else if (m_transform.y<=20)
	{
		currentMoveDir = direction[RIGHT];
	}
	else if (m_transform.x >= 780)
	{
		currentMoveDir = direction[DOWN];
	}
	if (m_transform.x <= 20)
	{
		currentMoveDir = direction[UP];
	}
	m_transform.x += currentMoveDir.x*m_speed;
	m_transform.y += currentMoveDir.y*m_speed;
}
					
void Object::Release()																							
{
	delete m_renderer;
}

Object::~Object()
{
}
