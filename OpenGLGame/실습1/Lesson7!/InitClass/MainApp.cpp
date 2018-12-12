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
void KeyboardSpecialKey(int key, int x, int y);
void MenuFunc(int button);

std::list<Object*> vObjects;
MousePosition currentMousePos;
int saveAmount = 20;
char g_shape=CIRCLE;


void Lesson7()
{
	for (list<Object*>::iterator iter = vObjects.begin(); iter != vObjects.end(); ++iter)
	{
		Object* object = *iter;
		object->Move();
		object->Render(g_shape);
	}

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
	glutMainLoop();
	glutSpecialFunc(KeyboardSpecialKey);


	delete glclass;
	return 0;
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	Lesson7();
	
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
		y = 600 - y;
		currentMousePos.x = x;
		currentMousePos.y = y;
		cout << "mouseregist" << endl;
		Object* newObject = new Object({ float(x),float(y),0.0f }, 1);
		if (vObjects.size() >= saveAmount)
		{
			return;
		}
		vObjects.push_back(newObject);
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		for (list<Object*>::iterator iter = vObjects.begin(); iter != vObjects.end(); ++iter)
		{
			Object* object = *iter;
			object->SetSpeed(5);
		}
	}
	else if (key == 's')
	{
		for (list<Object*>::iterator iter = vObjects.begin(); iter != vObjects.end(); ++iter)
		{
			Object* object = *iter;
			object->SetSpeed(-5);
		}
	}
	else if (key == 'd')
	{
		for (list<Object*>::iterator iter = vObjects.begin(); iter != vObjects.end(); ++iter)
		{
			Object* object = *iter;
			object->Start(10.f);
		}
	}
}

void KeyboardSpecialKey(int key, int x, int y)
{

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