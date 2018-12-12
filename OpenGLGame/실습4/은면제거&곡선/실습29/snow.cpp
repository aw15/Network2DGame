#include "stdafx.h"
#include "snow.h"


snow::snow()
{
	position = { float(rand() % 1000 - 500), 500 ,float(rand() % 1000 - 500) };
}


snow::~snow()
{
}

void snow::Draw()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(position.x, position.y, position.z);
	glutSolidCube(10);
	glPopMatrix();
	position.y -= 20;
}

void snow::Update()
{
	if (position.y < 400)
	{
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(position.x, position.y, position.z);
		glutSolidCube(10);
		glPopMatrix();
		position.y += rand() % 10;
		position.x += rand() % 10-5;
		position.z += rand() % 10-5;
	}
}
