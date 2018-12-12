
#include "Pyramid.h"


Pyramid::Pyramid()
{
}


void Pyramid::Render()
{
	
	glPushMatrix();
	{
		glPushMatrix();
		{
		glColor3ub( color[BOTTOM].x,color[BOTTOM].y,color[BOTTOM].z);
		glTranslatef(position.x, position.y, position.z);
		RotateZ(rotation.z);
		RotateX(rotation.x);
		RotateY(rotation.y);
			glBegin(GL_POLYGON);
			//-----关-----
			glNormal3f(0, 0, 1);
			for (int i = 0; i < 4; i++)
			{
				glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
			}
			glEnd();
			glBegin(GL_TRIANGLES);
			//----哭率------
			glColor3ub(color[LEFT].x, color[LEFT].y, color[LEFT].z);
			glNormal3f(-1, 0, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
			}
			glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			//----坷弗率------
			glColor3ub(color[RIGHT].x, color[RIGHT].y, color[RIGHT].z);
			glNormal3f(1, 0, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[i + 2].x, verticies[i + 2].y, verticies[i + 2].z);
			}
			glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			////---缔率------
			glColor3ub(color[BACK].x, color[BACK].y, color[BACK].z);
			glNormal3f(0, -1, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[(i + 3) % 4].x, verticies[(i + 3) % 4].y, verticies[(i + 3) % 4].z);
			}
			glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			////------------菊率------------------
			glColor3ub(color[FRONT].x, color[FRONT].y, color[FRONT].z);
			glNormal3f(0, 1, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[i + 1].x, verticies[i + 1].y, verticies[i + 1].z);
			}
			glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			glEnd();
			/*glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
			glColor3f(0, 0, 0);
			glTranslatef(position.x, position.y, position.z);
			RotateZ(rotation.z);
			RotateX(rotation.x);
			RotateY(rotation.y);
			glBegin(GL_LINES);
			//-----关-----
			glNormal3f(0, 0, 1);
			for (int i = 0; i < 4; i++)
			{
				glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
				if (i + 1 == 4)
				{
					glVertex3f(verticies[0].x, verticies[0].y, verticies[0].z);
				}
				else
					glVertex3f(verticies[i + 1].x, verticies[i + 1].y, verticies[i + 1].z);
			}
			glEnd();
			glLineWidth(5);
			glBegin(GL_LINES);

			//----哭率------
			glNormal3f(-1, 0, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
				glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			}
			//----坷弗率------
			glNormal3f(1, 0, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[i + 2].x, verticies[i + 2].y, verticies[i + 2].z);
				glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			}
			////---缔率------
			glNormal3f(0, -1, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[(i + 3) % 4].x, verticies[(i + 3) % 4].y, verticies[(i + 3) % 4].z);
				glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			}
			////------------菊率------------------
			glNormal3f(0, 1, 0);
			for (int i = 0; i < 2; i++)
			{
				glVertex3f(verticies[i + 1].x, verticies[i + 1].y, verticies[i + 1].z);
				glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Pyramid::Move(Vector3 direction)
{
	for (int i = 0; i < 5; i++)
	{
		verticies[i].x += direction.x;
		verticies[i].y += direction.y;
		verticies[i].z += direction.z;
	}
}

void Pyramid::ChangeColor(Vector3 param, int index)
{
	color[index].x = param.x;
	color[index].y = param.y;
	color[index].z = param.z;

}


TriangleList* Pyramid::GetCollider()
{
	for (int i = 0; i < 4; i++)
	{
		colliderPlane.bottom[i] = verticies[i];
	}
	for (int i = 0; i <= 1; i++)
	{
		colliderPlane.left[i] = verticies[i];
		colliderPlane.front[i] = verticies[i + 1];
		colliderPlane.right[i] = verticies[i + 2];
		colliderPlane.back[i] = verticies[(i + 3) % 4];
	}
	colliderPlane.left[2] = verticies[4];
	colliderPlane.right[2] = verticies[4];
	colliderPlane.front[2] = verticies[4];
	colliderPlane.back[2] = verticies[4];
	return &colliderPlane;
}



void Pyramid::RotateZ(int degree)
{
	float radian = degree * RADIAN;
	for (int i = 0; i < 5; i++)
	{
		Vector3 temp;
		temp.x = (cos(radian)*verticies[i].x) - (sin(radian)*verticies[i].y);
		temp.y = (sin(radian)*verticies[i].x) + (cos(radian)*verticies[i].y);
		temp.z = verticies[i].z;
		verticies[i].Copy(temp);
	}
}

void Pyramid::RotateY(int degree)
{
	float radian = degree * RADIAN;
	for (int i = 0; i < 5; i++)
	{
		Vector3 temp;
		temp.x = (cos(radian)*verticies[i].x) + (sin(radian)*verticies[i].z);
		temp.z = -(sin(radian)*verticies[i].x) + (cos(radian)*verticies[i].z);
		temp.y = verticies[i].y;
		verticies[i].Copy(temp);
	}
}

void Pyramid::RotateX(int degree)
{
	float radian = degree * RADIAN;
	for (int i = 0; i < 5; i++)
	{
		Vector3 temp;
		temp.y = (cos(radian)*verticies[i].y) - (sin(radian)*verticies[i].z);
		temp.z = (sin(radian)*verticies[i].y) + (cos(radian)*verticies[i].z);
		temp.x = verticies[i].x;
		verticies[i].Copy(temp);
	}
}