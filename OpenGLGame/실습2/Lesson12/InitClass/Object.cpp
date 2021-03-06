#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	srand(time(NULL));
	m_color = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,1.0f };
	m_transform = {0.0f,0.0f,0.0f};
	m_rotation = { 0,0,0 };
	m_angle = 0;
	m_size = 1;
	m_renderer = new Renderer;
	m_circleMoving = 0;
}

Object::Object(const Transform& pos ,const float size)
{
	srand((unsigned)time(NULL));
	m_color = { 1,1,1,1};
	m_transform = pos;
	m_rotation = { 0,0,0 };
	m_angle = 0;
	m_size = size;
	m_renderer = new Renderer;
	m_circleMoving = 0;
}

Object::Object(const Transform & pos, Transform & rotation, const Color & color, const float size, const int angle)
{
	m_transform = pos;
	m_rotation = rotation;
	m_color = color;
	m_size = size;
	m_angle = angle;
	m_renderer = new Renderer;
	m_circleMoving = 0;
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

void Object::Render(const char shape)										
{
	m_shape = shape;
	m_renderer->DrawShape(m_shape,m_transform,m_rotation,m_angle,m_size,m_color);
}

																	
														
																	
																	
void Object::Move(Transform & direction)				
{	//																
	//m_transform.x += direction.x*m_speed;								
	//m_transform.y += direction.y*m_speed;								
}

void Object::Move(char shape, MousePosition* mouseposList,int size)
{
	m_startPosition.x = mouseposList[0].x;
	m_startPosition.y = mouseposList[0].y;
	

	if (m_transform.x == 0 && m_transform.y == 0|| m_currentIndex >= size)
	{
		//cout << "tes" << endl;
		m_transform.x = m_startPosition.x;
		m_transform.y = m_startPosition.y;
		m_currentIndex = 1;
	}
	m_target.x = mouseposList[m_currentIndex].x;
	m_target.y = mouseposList[m_currentIndex].y;

	Transform direction = m_target - m_transform;
	direction.Normalize();
	m_transform.x += direction.x*0.1;
	m_transform.y += direction.y*0.1;

	//cout << abs(m_transform.x - m_target.x) << " " << abs(m_transform.y - m_target.y) << endl;
	if (abs(m_transform.x - m_target.x)<=0.05&&abs(m_transform.y - m_target.y)<=0.05)
	{
		//cout << abs(m_transform.x - m_target.x) << " " << abs(m_transform.y - m_target.y) << endl;
		m_currentIndex++;
	}
	//cout << m_currentIndex << endl;
}

void Object::Move(char shape)
{
	float x, y;
	float radius = 0.5;

	switch (shape)
	{
	case CIRCLE:

		x = cos(m_circleMoving*ANGLE)*radius;
		y = sin(m_circleMoving*ANGLE)*radius;

		//cout << x << " " << y << endl;
		m_transform.x = x;
		m_transform.y = y;
		//cout << m_circleMoving << endl;
		m_circleMoving <= 360 ? m_circleMoving+=5 : m_circleMoving = 0;
		break;
	case SIN:
		m_pivotX += 0.013;
		y = radius*sin(m_circleMoving*ANGLE)*0.5;

		m_transform.x = -1+m_pivotX;
		m_transform.y = y;

		if (m_circleMoving > 1080)
		{
			m_circleMoving = 0;
			m_pivotX = 0;
		}
		else
			m_circleMoving += 10;
		break;
	case LINE:
		m_transform.x = m_lineX;
		m_transform.y = m_lineY;
		//cout << m_transform.x << " " << m_transform.y << endl;
		if (m_lineY < 0.0)
			m_lineDist = 0.05;
		else if (m_lineY > 0.5)
			m_lineDist = -0.05;
		m_lineY +=m_lineDist;
		if (m_lineX < 0.7)
			m_lineX += 0.028;
		else
		{
			m_lineX = -1;
			m_lineDist = 0.05;
		}
		break;
	case TONADO:
		x = cos(m_circleMoving*ANGLE)*m_tonadoRadius;
		y = sin(m_circleMoving*ANGLE)*m_tonadoRadius;
		//cout << x << " " << y << endl;
		m_transform.x = x;
		m_transform.y = y;
		//cout << m_circleMoving << endl;
		if (m_circleMoving <= 1080)
		{
			m_circleMoving += 5;
			m_tonadoRadius += 0.005;
		}
		else
		{
			m_circleMoving = 0;
			m_tonadoRadius =0.005;
		}
		
		glEnd();
	}
}

					
void Object::Release()																							
{
	delete m_renderer;
}

Object::~Object()
{
}
