#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	Init();
}

void Object::Init()
{
	m_renderer = new Renderer;
	m_size = { 1,1,1 };
	m_position = { 0,0,0 };
	m_rotation = { 0,0,0 };
	m_color = { 1,1,1,1 };
	m_angle = 0;
	m_speed = {0,0,0};
}
void Object::Release()
{
	delete m_renderer;
}



Object::~Object()
{
}
//SET함수-----------------------------------------------------------------
void Object::SetTransform(const Transform& pos)
{
	m_transform.push_back(pos);
}
void Object::SetPosition(const Transform & pos)
{
	m_position = pos;
}
void Object::SetRotation(const Transform & pos, int angle)
{
	m_angle = angle;
	m_rotation = pos;
}

void Object::SetColor(const Color & color)
{
	m_color = color;
}

void Object::SetSpeed(const Transform& speed)
{
	m_speed = speed;
}
void Object::SetSize(const Transform& size)
{
	m_size = size;
}

void Object::SetShape(const int shape)
{
	m_shape = shape;
}
//SET함수-----------------------------------------------------------------
//----------------------------------GET함수---------------------------------------------
Color Object::GetColor()
{
	return m_color;
}
void Object::GetTransform(vector<Transform>& pos)
{
	pos =  m_transform;
}
void Object::GetPosition(Transform& pos)
{
	pos = m_position;
}
//----------------------------------GET함수---------------------------------------------


void Object::Render(int shape)										
{
	glPushMatrix();
	glColor3f(m_color.r, m_color.g, m_color.b);
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
	glScalef(m_size.x, m_size.y, m_size.z);
	switch (shape)
	{
	case RECT:
		glutSolidCube(0.5);
		break;
	default:
		glBegin(GL_POLYGON);
		for (vector<Transform>::iterator iter = m_transform.begin();iter != m_transform.end();++iter)
		{
			glVertex2f(iter->x, iter->y);
		}
		glEnd();

	}
	glPopMatrix();
}

void Object::Move()
{
	m_position = m_position + m_speed;
}


																	
														

Rect::Rect()
{
	m_max = { 0,0,0 };
	m_min = { 0,0,0 };

}

//----------------------------------사각형 클래스--------------------------------------------------------------
void Rect::SetTransform(const Transform& max, const Transform& min)
{
	m_max = max;
	m_min = min;
}

void Rect::GetTransform(Transform& max, Transform& min)
{
	max = m_max+m_position;
	min = m_min+m_position;
}

void Rect::Move()
{
	
	Object::Move();
	if (m_position.x >= 0.8)
	{
		m_speed = m_speed*-1;
	}
	else if (m_position.x <= -0.8)
	{
		m_speed = m_speed*-1;
	}
}

void Rect::Render()
{
	glPushMatrix();
	glColor3f(m_color.r, m_color.g, m_color.b);
	glTranslatef(m_position.x,m_position.y,m_position.z);
	glRotatef(m_angle,m_rotation.x, m_rotation.y, m_rotation.z);
	glScalef(m_size.x, m_size.y, m_size.z);
	glRectf(m_min.x, m_min.y, m_max.x, m_max.y);
	glPopMatrix();
}
