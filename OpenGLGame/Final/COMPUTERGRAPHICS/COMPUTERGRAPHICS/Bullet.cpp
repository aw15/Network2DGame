
#include "Bullet.h"



Bullet::Bullet(Vector3 position,Vector3 rotation)
{
	srand((unsigned)time(NULL));
	color = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX ,rand() / (float)RAND_MAX };
	this->position = position;
	this->rotation = rotation;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	float distance = sqrt(pow(position.x, 2) + pow(position.y, 2) + pow(position.z, 2));
	if (distance > 10)
	{
		position.x -= (position.x / distance) * 20;
		position.y -= (position.y / distance) * 20;
		position.z -= (position.z / distance) * 20;
	}
}

void Bullet::Render()
{
	glPushMatrix();
	glColor3f(color.x, color.y, color.z);
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(10,20,20);
	glPopMatrix();
}

Vector3 Bullet::GetCollider()
{
	return position;
}
