#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}
void Renderer::DrawShape(int shape,Transform& position , Transform& rotation, const int angle, float size,const Color& color)
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	glTranslatef(position.x, position.y, position.z);
	glScalef(size, size, size);
	glRotatef(angle, rotation.x, rotation.y, rotation.z);
	
	glColor4f(color.r,color.g,color.b,color.a);

	if (shape & RECT)
		DrawRect();
	else if (shape&TRIANGLE)
		DrawTriangle();
	else if (shape&CIRCLE)
		DrawCircle();
	else if (shape&LINE)
		DrawLine();
	else if (shape&POINT_)
		DrawPoint();
	else if (shape&SIN)
		DrawSin();
	else if (shape&TONADO)
		DrawTonado();
	else if (shape&WIRE_TRIANGLE)
		DrawWireTriangle();
	else if (shape&SPHERE)
		glutWireSphere(0.2, 20, 20);
	else if (shape&CONE)
		glutWireCone(0.2, 0.2, 20, 20);
	else if (shape&TORUS)
		glutWireTorus(0.1,0.2,20,20);
	else if (shape&CUBE)
		glutWireCube(0.2);
	else if (shape&TEAPOT)
		glutWireTeapot(0.2);

	glPopMatrix();

}
void Renderer::DrawRect()
{
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.1);
	glVertex2f(-0.1, -0.1);
	glVertex2f(+0.1, -0.1);
	glVertex2f(+0.1, +0.1);
	glEnd();
}
void Renderer::DrawCircle()
{
	float radius = 0.05;
	float angle = 3.141592 / 180; // 라디안 = 파이(==180), 파이 / 180 = 1도
	float max_angle = 360;
	
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < max_angle; i = i + 5)
	{
		float current = i*angle;
		glVertex2f((cos(current)*radius), (sin(current)* radius));
	}
	glEnd();
}
void Renderer::DrawLine()//지그제그
{
	float y = 0;
	glBegin(GL_LINE_STRIP);
	for (float i = -0.1; i < 0.1; i += 0.03)
	{
		glVertex2f(i,y );
		y == 0 ? y = 0.05 : y = 0;
		//cout << i << " " << y << endl;
	}
	glEnd();
}
void Renderer::DrawPoint()
{
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2f(0, 0);
	glEnd();
}
void Renderer::DrawTonado()
{
	float radius = 0.0005;
	float max_angle = 1080;
	static int index = 0;
	glBegin(GL_LINE_STRIP);
	for (float i = 0; i < max_angle; i = i + 5)
	{
		float current = i*ANGLE;
		glVertex2f((cos(current)*radius), (sin(current)* radius));
		radius += 0.0005;
	}
	glEnd();
}
void Renderer::DrawSin()
{
	glBegin(GL_LINE_STRIP);
	double rad = 0.5;
	double angle = 3.141592 / 180;
	float pivotX = 0;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i <= 360; ++i)
		{
			double y = rad*sin(i*angle);
			glVertex2f(pivotX, y*0.05);
			pivotX += 0.00013;
		}
	}
	glEnd();
}
void Renderer::DrawTriangle()
{
	glBegin(GL_TRIANGLES);
		glVertex2f(0, 0.1);
		glVertex2f(-0.1, -0.1);
		glVertex2f(+0.1, -0.1);
	glEnd();
}
void Renderer::DrawWireTriangle()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(+0.5, -0.5);
	glEnd();
}

Renderer::~Renderer()
{
}
