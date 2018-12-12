#include "stdafx.h"
#include "Object.h"


Object::Object():m_shape(RECT)
{
	srand((unsigned)time(NULL));
	m_color = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,1.0f };
	m_transform = {0.0f,0.0f,0.0f};
	m_size = 50;
	m_renderer = new Renderer;
	m_count = rand() % 20;
	save_count = m_count;
	cout << m_count << endl;
}

Object::Object(const Transform& pos ,const float size) :m_shape(RECT)
{
	srand((unsigned)time(NULL));
	m_color = { 1,1,1,1.0f };
	float random = rand() / float(RAND_MAX);
	random = rand() / float(RAND_MAX);
	cout << random << endl;
	if (rand() / float(RAND_MAX) < 0.4)
	{
		m_isBacktobegin = false;
	}
	else
		m_isBacktobegin = true;
	m_transform = pos;
	m_size = size;
	m_renderer = new Renderer;
	m_count = rand() % 20;
	save_count = m_count;
	save_size = size;
	cout << m_count << endl;
}

Object::Object(const Transform& pos, const Color& color, const float size) :m_shape(RECT)
{
	srand((unsigned)time(NULL));
	m_transform = pos;
	m_color = color;
	m_size = size;
	m_renderer = new Renderer;
	m_count = rand() % 20;
	save_count = m_count;
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
}
																	
void Object::Render(const char shape)												
{
	m_shape = shape;
	if(m_noRender==false)
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
	cout << m_isBacktobegin << endl;
	if (m_count>0)
	{
		m_size += 10;
		m_count--;
	}
	else if (m_count <= 0 && m_isBacktobegin == false)
	{
		m_size = 0;
		m_noRender = true;
	}
	else if (m_count <= 0&&m_isBacktobegin==true)
	{
		m_size = 1;
		m_count = save_count;
	}
	cout << m_size<<endl;
}
					
void Object::Release()																							
{
	delete m_renderer;
}

Object::~Object()
{
}
