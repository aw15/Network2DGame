// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include "Object.h"
#include"InputClass.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

std::vector<Object*> vObjects;
MousePosition currentPos;
list<MousePosition> mousePositions;
int mousePositionSaveAmount = 10;

void Lesson5()
{
	for (list<MousePosition>::iterator iter = mousePositions.begin(); iter != mousePositions.end(); iter++)
	{
		Object newObject({ float(iter->x),float(iter->y),0.0f }, {1.0f,1.0f,0.0f,1.0f},50);
		newObject.Render();
	}
}

int main()
{
	int rectcount = 0;
	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutDisplayFunc(drawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();



	delete glclass;
	return 0;
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	Lesson5();
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);
}

void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력, drawscene이 호출
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Mouse(int button, int state, int x, int y)//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mousePositions.size() > mousePositionSaveAmount) { mousePositions.pop_front(); }
		y = 600 - y;
		currentPos.x = x;
		currentPos.y = y;
		mousePositions.push_back(currentPos);
	}
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

