#include "stdafx.h"
#include "Object.h"


Object::Object():m_shape(RECT)
{
	srand(time(NULL));
	m_color = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,1.0f };
	m_transform = {0.0f,0.0f,0.0f};
	m_size = 50;
	m_renderer = new Renderer;

}

Object::Object(const Transform& pos ,const float size) :m_shape(RECT)
{
	srand((unsigned)time(NULL));
	m_color = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,1.0f };
	m_transform = pos;
	m_size = size;
	m_renderer = new Renderer;

}

Object::Object(const Transform& pos, const Color& color, const float size) :m_shape(RECT)
{
	m_transform = pos;
	m_color = color;
	m_size = size;
	m_renderer = new Renderer;

}


void Object::SetTransform(const Transform& pos)
{
	m_transform = pos;
}

void Object::SetCurrentDir(const Transform & pos)
{
	m_currentMoveDir = pos;
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

void Object::SetSize(const int size)
{
	if (m_size > 0)
		m_size += size;
	else
		m_size = 0;
}

void Object::ColorLesser(const float color)
{
	m_color.a -= color;
}

void Object::Render(const char shape)										
{
	m_shape = shape;
	m_renderer->DrawShape(m_shape,m_transform.x,m_transform.y,m_size,m_color);
}

void Object::Start(const float& speed)
{
	m_speed = speed;
	m_currentMoveDir = direction[RIGHT];
	m_startPosition = m_transform;
}
																	
																	
																	
																	
void Object::Move(Transform & direction)				
{																	
	m_transform.x += direction.x*m_speed;								
	m_transform.y += direction.y*m_speed;								
}		
void Object::Move()
{
	m_transform.x += m_currentMoveDir.x*m_speed;
	m_transform.y += m_currentMoveDir.y*m_speed;
}
					
void Object::Release()																							
{
	delete m_renderer;
}

Object::~Object()
{
}
