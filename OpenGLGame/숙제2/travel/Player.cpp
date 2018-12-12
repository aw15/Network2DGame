#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	color = { 1,0,1 };
	position = { -300,300,300 };
	rotation = { 0.0f,0.0f,0.0f };
	scale = { 1,1,1 };
	size = 10.0f;
}

Player::~Player()
{
}
int BezierRender(vector<Vector3>& vertexList)
{
	
	glLineWidth(5);

	glBegin(GL_LINES);
	for (int i = 0; i <vertexList.size()-1 ; ++i)
	{
		Vector3 x1 = vertexList[i];
		Vector3 x2 = { x1.x ,x1.y,x1.z };
		if (x1.y + 100 < 300)
			x2.y += 100;
		if (x1.x + 50 < 300)
			x2.x += 50;
		Vector3 x3 = { x2.x ,x2.y,x2.z };
		if (x2.x + 50 < 300)
			x3.x += 50;
		Vector3 x4 = vertexList[i+1];
		for (float detail = 0.0f; detail <= 1.0f; detail += (1.0f / 120.0f))
		{
			Vector3 result = _getBezier(x1, x2, x3, x4, detail);
			glVertex3f(result.x, result.y, result.z);
		}
	}
	glEnd();

	return 0;
}


void Player::Update()
{
	wingDegree += 10;// 프로펠러 돌기

	if(movingCount>0)
	{
		Vector3 x1 = movePoint[moveIndex];
		Vector3 x2 = { x1.x,x1.y,x1.z };
		if (x1.y + 100 < 300)
			x2.y += 100;
		if (x1.x + 50 < 300)
			x2.x += 50;
		Vector3 x3 = { x2.x,x2.y,x2.z };
		if (x2.x + 50 < 300)
			x3.x += 50;
		Vector3 x4 = movePoint[moveIndex + 1];

		Vector3 result = _getBezier(x1, x2, x3, x4, detail);
		//------------------비행기 각도계산--------------------------------
		float dx = result.x - position.x;
		float dy = result.y - position.y;
		float dz = result.z - position.z;
		
		auto degreeZ = atan(dy / dx)*TO_DEGREE;
		rotation.z =  degreeZ;


		auto degreeY = atan(dz / dx)*TO_DEGREE;
		rotation.y = -degreeY;

		//cout << rotation.z << endl;

		position.x = result.x;
		position.y = result.y;
		position.z = result.z;
		detail += (1.0f / 120.0f);
		lookAt = _getBezier(x1, x2, x3, x4, detail);

		if (detail >= 1.0f&& moveIndex+1 < movePoint.size() - 1)
		{
			moveIndex += 1;
			detail = 0.0f;
		}
		else if (detail >= 1.0f)
		{
			detail = 0.0f;
			movingCount -= 1;
			moveIndex = 0;
		}
	}
}
void Player::Render()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
		//glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glPushMatrix();
		{
			glColor3f(color.x, color.y, color.z);
			glScalef(3, 1, 1);
			glutSolidCube(size);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor3f(1, 1, 0);
			glTranslatef(0, 0,  15);
			glScalef(1, 0.5, 2);
			glutSolidCube(size);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor3f(1, 1, 0);
			glTranslatef(0,0,  - 15);
			glScalef(1, 0.5, 2);
			glutSolidCube(size);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor3f(1, 1, 0);
			glTranslatef( - 10,  + 10, 0);
			glScalef(0.5, 1, 0.5);
			glutSolidCube(size);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(+ 16, 0, 0);
			glRotatef(wingDegree, 1, 0, 0);
			glRotatef(90, 1, 0, 0);
			glutSolidCone(size - 7, size, 20, 20);
			glRotatef(180, 1, 0, 0);
			glutSolidCone(size - 7, size, 20, 20);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef( + 15, 0, 0);
			glRotatef(wingDegree, 1, 0, 0);
			glutSolidCone(size - 7, size, 20, 20);
			glRotatef(180, 1, 0, 0);
			glutSolidCone(size - 7, size, 20, 20);
		}
		glPopMatrix();
	}
	glPopMatrix();


		if (ready)
		{
			glPushMatrix();
			BezierRender(movePoint);
			glPopMatrix();
		}

}