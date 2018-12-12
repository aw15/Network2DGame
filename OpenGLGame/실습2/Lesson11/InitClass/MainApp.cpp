// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include "Object.h"
#include"InputClass.h"
#include"Collision.h"



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecialKey(int key, int x, int y);
void MenuFunc(int button);
void Motion(int x, int y);

std::list<Object*> g_vObjects;
Collision g_collision;

MousePosition currentMousePos;
int saveAmount = 20;
char g_shape=RECT;

bool g_animation = false;
int g_sinIndex = 0;
float g_rectIndex = 0;
int g_springIndex = 0;
int g_frustrum = 0;


float g_scaling = 1;
float g_degree = 0;
enum class Rotation {none,x,y,z};
Rotation g_rotation = Rotation::none;
float g_movement = 0;

void DrawSin()
{
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	double rad = 0.5;
	double angle = 3.141592 / 180;
	float pivotX = 0;
	for (int j = 0; j <= 3; j++)
	{
		for (int i = g_sinIndex; i <= 360+g_sinIndex; ++i)
		{
			double y = rad*sin(i*angle);
			glVertex2f(pivotX, y*0.2 );
			pivotX += 0.001;
		}
	}
	glEnd();

}

void DrawCos()
{
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	double rad = 0.5;
	double angle = 3.141592 / 180;
	float pivotX = 0;
	for (int j = 0; j <= 3; j++)
	{
		for (int i = g_sinIndex; i <= 360 + g_sinIndex; ++i)
		{
			double y = rad*cos(i*angle);
			glVertex2f(pivotX, y*0.2);
			pivotX += 0.001;
		}
	}
	glEnd();
}
void DrawSpring()
{
	glBegin(GL_LINE_STRIP);
	double rad = 0.1;
	double angle = 3.141592 / 180;
	float pivotX = 0;
	float gradiationfactor = 1.0f;

	cout << g_springIndex << endl;
	if (g_animation)
		g_springIndex += 10;

	if (g_springIndex >= 360)
	{
		g_frustrum = 0;
		g_springIndex = 0;
	}
	for (int j = 0; j <= 6; j++)
	{
		glColor3f(gradiationfactor, 0, 1.0 - gradiationfactor);
		if (j == 0)
		{
				for (int i = g_springIndex; i <= 360; ++i)
				{
					
					/*if (g_springIndex > 40 && i > 240-g_frustrum &&i<300+g_frustrum)
					{
						glColor3f(0,0, 0);
						
					}*/
					float x = rad*sin(i*angle);
					double y = -rad*cos(i*angle);
					glVertex2f(x + pivotX, y);
					pivotX += 0.001;
					if (i > 180)pivotX -= 0.001;
				}
				/*if (g_springIndex > 40)
					g_frustrum < 60 ? g_frustrum += 10 : g_frustrum = 60;*/
				
		}
		if (j == 6)
		{
			for (int i = 0; i <= g_springIndex; ++i)
			{
				//glColor3f(gradiationfactor, 0, 1.0 - gradiationfactor);
				float x = rad*sin(i*angle);
				double y = -rad*cos(i*angle);
				glVertex2f(x + pivotX, y);
				pivotX += 0.001;
				if (i > 180)pivotX -= 0.001;
			}
		}
		else 
		{
			for (int i = 0; i <= 360; ++i)
			{
				//glColor3f(gradiationfactor, 0, 1.0 - gradiationfactor);
				float x = rad*sin(i*angle);
				double y = -rad*cos(i*angle);
				glVertex2f(x + pivotX, y);
				pivotX += 0.001;
				if (i > 180)pivotX -= 0.001;
			}
		}
		gradiationfactor -= 0.2;
	}
	glEnd();
}
void DrawRect()
{
	if (g_animation)
	{
		g_rectIndex += 0.02;
		if (g_rectIndex >= 0.1)
			g_rectIndex = 0;
	}
	glRectf(0 , 0, 0.1 - g_rectIndex, 0.1);
	for (int i = 1; i < 10; ++i)
	{
		glRectf(0 + (i*0.15)-g_rectIndex, 0, 0.1 + (i * 0.15) - g_rectIndex, 0.1);
	}
	glRectf(0 + (10*0.15) - g_rectIndex, 0, 0 + (10 * 0.15), 0.1);
}

void Lesson11()
{
	if (g_animation)
		g_sinIndex += 10;
	else
		g_sinIndex = 0;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		if (g_rotation == Rotation::y)
		{
			glRotatef(g_degree, 0, 1, 0);
			g_degree += 10;
		}
		if (g_rotation == Rotation::z)
		{
			glRotatef(g_degree, 0, 0, 1);
			g_degree += 10;
		}
		glTranslatef(-0.7, 0.3, 0);
		//월드좌표 기준 회전
		if (g_rotation == Rotation::x)
		{
			glRotatef(g_degree, 1, 0, 0);
			g_degree += 10;
		}
		glScalef(g_scaling, g_scaling, g_scaling);
		DrawCos();
	glPopMatrix();
	glPushMatrix();
		if (g_rotation == Rotation::y)
		{
			glRotatef(g_degree, 0, 1, 0);
			g_degree += 10;
		}
		if (g_rotation == Rotation::z)
		{
			glRotatef(g_degree, 0, 0, 1);
			g_degree += 10;
		}
		glTranslatef(-0.7, 0.7, 0);
		//월드좌표 기준 회전
		if (g_rotation == Rotation::x)
		{
			glRotatef(g_degree, 1, 0, 0);
			g_degree += 10;
		}
		glScalef(g_scaling, g_scaling, g_scaling);
		DrawSin();
	glPopMatrix();
	glPushMatrix();
		if (g_rotation == Rotation::y)
		{
			glRotatef(g_degree, 0, 1, 0);
			g_degree += 10;
		}
		if (g_rotation == Rotation::z)
		{
			glRotatef(g_degree, 0, 0, 1);
			g_degree += 10;
		}
		glTranslatef(-0.7, -0.5, 0);
		//월드좌표 기준 회전
		if (g_rotation == Rotation::x)
		{
			glRotatef(g_degree, 1, 0, 0);
			g_degree += 10;
		}
		//-----------------------회전
		glScalef(g_scaling, g_scaling, g_scaling);
		//-------------------------크기
		DrawRect();
	glPopMatrix();
	glPushMatrix();
		if (g_rotation == Rotation::y)
		{
			glRotatef(g_degree, 0, 1, 0);
			g_degree += 10;
		}
		if (g_rotation == Rotation::z)
		{
			glRotatef(g_degree, 0, 0, 1);
			g_degree += 10;
		}
		glTranslatef(-0.7, -0.1, 0);
		//월드좌표 기준 회전
		if (g_rotation == Rotation::x)
		{
			glRotatef(g_degree, 1, 0, 0);
			g_degree += 10;
		}
		//-----------------------회전
		glScalef(g_scaling, g_scaling, g_scaling);
		//-------------------------크기
		DrawSpring();
	glPopMatrix();

	//g_rotation = Rotation::none;
	
	
}

int main()
{
	int rectcount = 0;
	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT,&MenuFunc);

	

	//glclass->MenuLayout();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutSpecialFunc(KeyboardSpecialKey);
	glutMotionFunc(Motion);
	glutMainLoop();


	delete glclass;
	return 0;
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(0, -1);
	glVertex2f(0, 1);
	glEnd();
	Lesson11();
	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w,h);
	
}

void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력, drawscene이 호출
	glutTimerFunc(1000, TimerFunction, 1); // 타이머함수 재 설정
}

void Mouse(int button, int state, int x, int y)//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
{
	currentMousePos.x = x;
	currentMousePos.y = y;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		y = 600 - y;
		cout << "mouseregist" << endl;
		Object* newObject = new Object({ float(x),float(y),0.0f }, 50);
		if (g_vObjects.size() >= saveAmount)
		{
			g_vObjects.pop_front();
		}
		g_vObjects.push_back(newObject);
	}
	else if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		y = 600 - y;
	}

}
void Motion(int x, int y)
{
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		g_rotation = Rotation::x;
	}
	else if (key == 'y')
	{
		g_rotation = Rotation::y;
	}
	else if (key == 'z')
	{
		g_rotation = Rotation::z;
	}
	else if (key == 'i')
	{
		glLoadIdentity();
		g_animation = false;
		g_sinIndex = 0;
		g_rectIndex = 0;
		g_springIndex = 0;
		g_frustrum = 0;


		g_scaling = 1;
		g_degree = 0;
		g_rotation = Rotation::none;
		g_movement = 0;
	}
	else if (key == 'S')
	{
		
		g_scaling +=0.1;
		//glScaled(1.2, 1.2, 1.2);
	}
	else if (key == 's')
	{
		g_scaling -= 0.1;
		//glScaled(0.9, 0.9, 0.9);
	}
	else if (key == 'a')
	{
		g_animation = false;
		g_sinIndex = 0;
		g_rectIndex = 0;
		g_springIndex = 0;
		g_frustrum = 0;
	}
	else if (key == 'A')
	{
		g_animation = true;
	}
}

void KeyboardSpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		g_movement = -0.1;
		glTranslatef(g_movement, 0, 0);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		g_movement  = +0.1;
		glTranslatef(g_movement, 0, 0);
	}
}

void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		g_shape = TRIANGLE;
		break;
	case 2:
		g_shape = RECT;
		break;
	case 3:
		g_shape = CIRCLE;
		break;

	}
	glutPostRedisplay();
}