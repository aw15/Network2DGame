// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include "Object.h"
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
int mouseX, mouseY;
bool boxbox;
list<pair<int, int>> mousePos;
void DrawRect(int x = 0, int y = 0, int size = 100, char color = 'R');
void Lesson1(list<pair<int, int>> &mousePos)
{
	list<pair<int, int>>::iterator iter;
	for (iter = mousePos.begin(); iter != mousePos.end(); ++iter)
	{
		pair<int, int> pos = *iter;
		DrawRect(pos.first, pos.second);
	}
}
int main()
{
	int rectcount = 0;
	OpenGLClass glclass(800, 600);
	glutDisplayFunc(drawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
	return 0;
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	Lesson1(mousePos);
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{

	}
	else if (key = 's')
	{

	}
}
void Mouse(int button, int state, int x, int y)//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		y = 600 - y;
		pair<int, int> pos = { x,y };
		if (mousePos.size()>10)
		{
			mousePos.pop_front();
			mousePos.push_back(pos);
		}
		else
		{
			mousePos.push_back(pos);
		}
	}
}
void TimerFunction(int value)
{
	boxbox == true ? boxbox = false : boxbox = true;
	glutPostRedisplay(); // 화면 재 출력, drawscene이 호출
	glutTimerFunc(500, TimerFunction, 1); // 타이머함수 재 설정
}


void DrawRect(int x, int y, int size, char color)
{
	switch (color)
	{
	case 'R':
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 'G':
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 'B':
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}
	if (boxbox)
	{
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
		glRectf(x - (size / 2), y - (size/2), x + (size / 2), y + (size));
	}
	else
	{
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		glRectf(x - (size / 2), y - (size / 2), x + size, y + size - (size / 2));
	}
}
