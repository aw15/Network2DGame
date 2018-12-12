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
void Motion(int x, int y);

std::list<Object*> vObjects;
std::list<Object*> vSubObjects;

MousePosition currentMousePos;
int saveAmount = 5;
char g_shape=RECT;
int g_renderCount;
float g_radius = 10;




void Lesson9()
{
	
	float angle = 3.141592 / 180; // 라디안 = 파이(==180), 파이 / 180 = 1도
	int max_angle = 360;

	for (list<Object*>::iterator iter = vObjects.begin(); iter != vObjects.end(); ++iter)
	{
		Object* object = *iter;
		Transform currentPos = object->GetTransform();
		
		if (object->GetColor().b>0.6)
		{
			if (object->m_renderCount < 18.8)
			{
				object->Render(RECT);
				object->m_renderCount += 0.3;
				object->m_radius += 1;

				currentPos.x -= cos(object->m_renderCount)*object->m_radius;
				currentPos.y += sin(object->m_renderCount)*object->m_radius;
				w << currentPos.x << endl;
				Object* newobject = new Object(currentPos, 3);
				vSubObjects.push_back(newobject);
				cout << object->m_renderCount << endl;
			}
			else if (object->m_renderCount < 36.6)
			{
				object->m_renderCount += 0.3;
				object->m_radius -= 1;

				currentPos = object->GetTransform();
				currentPos.x += cos(object->m_renderCount)*object->m_radius - 150;
				currentPos.y += sin(object->m_renderCount)*object->m_radius;
				Object* newobject = new Object(currentPos, 3);
				vSubObjects.push_back(newobject);

			}
		}
		else
		{
			if (object->m_renderCount < 18.8)
			{
				object->Render(RECT);
				object->m_renderCount += 0.3;
				object->m_radius += 1;

				currentPos.x += cos(object->m_renderCount)*object->m_radius;
				currentPos.y += sin(object->m_renderCount)*object->m_radius;
				cout << currentPos.x << endl;
				Object* newobject = new Object(currentPos, 3);
				vSubObjects.push_back(newobject);
				cout << object->m_renderCount << endl;
			}
			else if (object->m_renderCount < 36.6)
			{
				object->m_renderCount += 0.3;
				object->m_radius -= 1;

				currentPos = object->GetTransform();
				currentPos.x += cos(object->m_renderCount + 3)*object->m_radius + 150;
				currentPos.y -= sin(object->m_renderCount + 3)*object->m_radius;
				Object* newobject = new Object(currentPos, 3);
				vSubObjects.push_back(newobject);


			}
		}

	}
	for (list<Object*>::iterator iter = vSubObjects.begin(); iter != vSubObjects.end(); ++iter)
	{
		Object* object = *iter;
		object->Render(RECT);
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
	glutTimerFunc(10, TimerFunction, 1);
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
	Lesson9();
	
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
	glutTimerFunc(50, TimerFunction, 1); // 타이머함수 재 설정
}

void Mouse(int button, int state, int x, int y)//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
{
	currentMousePos.x = x;
	currentMousePos.y = y;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		y = 600 - y;
		cout << "mouseregist" << endl;
		Object* newObject = new Object({ float(x),float(y),0.0f }, 3);
		if (vObjects.size() >= saveAmount)
		{
			return;
		}
		vObjects.push_back(newObject);
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