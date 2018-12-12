#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}
void Renderer::DrawShape(char shape, int x, int y, int size, const Color& color)
{
	glColor4f(color.r, color.g, color.b, color.a);


	if (shape & RECT)
		DrawRect(x, y, size);
	else if (shape&TRIANGLE)
		DrawTriangle(x, y, size);
	else if (shape&CIRCLE)
		DrawCircle(x, y, size);
}
void Renderer::DrawRect(int x, int y, int size)
{
	glRectf(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2));
}
void Renderer::DrawCircle(int x, int y, int size)
{
	float radius = size;
	float angle = 3.141592 / 180; // 라디안 = 파이(==180), 파이 / 180 = 1도
	int max_angle = 360;

	glBegin(GL_POLYGON);
	for (int i = 0; i < max_angle; i = i + 10)
	{
		float current = i*angle;
		glVertex2f((cos(current)*radius) + x, (sin(current)* radius) + y);
	}
	glEnd();
}

void Renderer::DrawTriangle(int x, int y, int size)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y + size / 2);
	glVertex2f(x - size / 2, y - size / 2);
	glVertex2f(x + size / 2, y - size / 2);
	glEnd();
}
Renderer::~Renderer()
{
}
