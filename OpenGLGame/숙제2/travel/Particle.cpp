#include "stdafx.h"
#include "Particle.h"



Particle::Particle(Vector3 param)
{
	for (int i = 0; i < 100; i++)
	{
		position[i] = param;
	}
}

Particle::~Particle()
{
}

void Particle::Update()
{
	totalTime += clock() - currentTime;
	for (int i = 0; i < 100; i++)
	{
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(position[i].x, position[i].y, position[i].z);
		glutSolidCube(10);
		glPopMatrix();
		if (i % 2 == 0)
		{
			position[i].y += rand() % 20;
			position[i].x += rand() % 20;
			position[i].z += rand() % 20;
		}
		else
		{
			position[i].y -= rand() % 20;
			position[i].x -= rand() % 20;
			position[i].z -= rand() % 20;
		}
	}
}
