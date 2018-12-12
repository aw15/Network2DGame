
#include "Player.h"


Player::Player()
{
	color = { 1,0,0 };
	position = { 0,350,0 };
	scale = { 1,1,1 };
	size = 30.0f;
	radius = 300;
}

Player::~Player()
{
}

void Player::Shoot()
{
	Bullet* newBullet = new Bullet(position, rotation);
	bulletList.push_back(newBullet);
	//LOG_3("position", position.x, position.z, position.z);
}

void Player::RotateZ(int degree)
{
	float radian = degree * RADIAN;
	Vector3 temp;
	temp.x = (cos(radian)*position.x) - (sin(radian)*position.y);
	temp.y = (sin(radian)*position.x) + (cos(radian)*position.y);
	temp.z = position.z;
	position.Copy(temp);
	//LOG_3("position", position.x, position.y, position.z);
}
void Player::RotateY(int degree)
{
	float radian = degree * RADIAN;
	Vector3 temp;
	temp.x = (cos(radian)*position.x) + (sin(radian)*position.z);
	temp.z = -(sin(radian)*position.x) + (cos(radian)*position.z);
	temp.y = position.y;
	position.Copy(temp);
	//LOG_3("position", position.x, position.y, position.z);
}
void Player::Move(Vector3 & move)
{
	position.x += move.x;
	position.y += move.y;
	position.z += move.z;
}
void Player::RotateX(int degree)
{
	float radian = degree * RADIAN;
	Vector3 temp;
	temp.y = (cos(radian)*position.y) - (sin(radian)*position.z);
	temp.z = (sin(radian)*position.y) + (cos(radian)*position.z);
	temp.x = position.x;
	position.Copy(temp);
}




void Player::Update()
{
	for (auto bullet : bulletList)
	{
		bullet->Update();
	}
}




void Player::Render()
{
	if (helpingLine)
	{
		glPushMatrix();
		glColor3f(1, 1, 1);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex3f(position.x, position.y, position.z);
		glVertex3f(0, 0, 0);
		glEnd();
		glPopMatrix();
	}
	glPushMatrix();
	//LOG_3("color", color.x, color.y, color.z);
	RotateZ(rotation.z);
	RotateX(rotation.x);
	glTranslatef(position.x, position.y, position.z);
	glRotatef(90, 1, 0, 0);
	glRotatef(degree, 0, 1, 0);
		glPushMatrix();
		{
			glColor3ub(color.x, color.y, color.z);	
			glutSolidCone(20, 50,20,20);
			
		}
		glPopMatrix();
	glPopMatrix();

	degree += rotation.z;
	for (auto iter = bulletList.begin(); iter!= bulletList.end();)
	{
		auto bullet = *iter;
		bullet->Render();
		if (abs(bullet->position.x) < 10 && abs(bullet->position.y) < 10)
		{
			iter = bulletList.erase(iter);
		}
		else
			iter++;
	}
}