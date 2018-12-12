#include "effect.h"





Effect::Effect(Vector3 position, Vector3 color)
{
	srand(time(NULL));

	effectColor.x = rand() / (float)RAND_MAX;
	effectColor.y = rand() / (float)RAND_MAX;
	effectColor.z = rand() / (float)RAND_MAX;

	for (int i = 0; i < 20; i++) {
		dir[i].x = rand() / (float)RAND_MAX * 2 - 1;
		dir[i].y = rand() / (float)RAND_MAX * 2 - 1;
		dir[i].z = rand() / (float)RAND_MAX * 2 - 1;
		speed[i] = rand() / (float)RAND_MAX * 2 - 1;
		effectPos[i] = { 0,0,0 };
	}

	max = rand() % 80 + 30;
	rotation.y = rand() % 360;
	this->position.x = position.x+ ((rand() % 800) - 400);
	this->position.y = position.y + ((rand() % 800) - 400);
	this->position.z = position.z + ((rand() % 800) - 400);
	position2.x = position.x + ((rand() % 400) - 200);
	position2.y =  position.y + ((rand() % 400) - 200);
	position2.z = position.z + ((rand() % 400) - 200);
	this->color = color;
	defaultPosition = position;
}

void Effect::Render()
{

	glColor3ub(color.x, color.y, color.z);
	glPushMatrix();
	//glTranslatef(-100, 0, 0);
	glTranslatef(position.x, position.y, position.z);
	for (int i = 0; i < 360; i+=15)
	{
		glPushMatrix();
		glRotatef(rotation.y, 0, 1,0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 0);
		glutSolidCube(8);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(position2.x, position2.y, position2.z);
		glRotatef(rotation.y, 0, 1, 0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 0);
		glutSolidCube(8);
		glPopMatrix();
		/*glPushMatrix();
		glRotatef(60, 0, 1, 0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 500);
		glRotatef(rotation.y, 0, 1, 0);
		glutSolidCube(7);
		glPopMatrix();
		glPushMatrix();
		glRotatef(120, 0, 1, 0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 500);
		glRotatef(rotation.y, 0, 1, 0);
		glutSolidCube(7);
		glPopMatrix();
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 500);
		glRotatef(rotation.y, 0, 1, 0);
		glutSolidCube(7);
		glPopMatrix();
		glPushMatrix();
		glRotatef(240, 0, 1, 0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 500);
		glRotatef(rotation.y, 0, 1, 0);
		glutSolidCube(7);
		glPopMatrix();
		glPushMatrix();
		glRotatef(300, 0, 1, 0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 500);
		glRotatef(rotation.y, 0, 1, 0);
		glutSolidCube(7);
		glPopMatrix();
		glPushMatrix();
		glRotatef(360, 0, 1, 0);
		glTranslatef(cos(i*RADIAN)*radius, sin(i*RADIAN)*radius, 500);
		glRotatef(rotation.y, 0, 1, 0);
		glutSolidCube(7);
		glPopMatrix();*/
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(defaultPosition.x, defaultPosition.y, defaultPosition.z);
	for (int i = 0; i < 10; i++)
	{
		glColor3f(effectColor.x, effectColor.y, effectColor.z);
		glTranslatef(effectPos[i].x, effectPos[i].y, effectPos[i].z);
		effectPos[i].x += dir[i].x*speed[i];
		effectPos[i].y += dir[i].y*speed[i];
		effectPos[i].z += dir[i].z*speed[i];
		glutSolidCube(10);
	}
	glPopMatrix();

	radius += 0.3;
	if (radius >max)
		end = true;
}
