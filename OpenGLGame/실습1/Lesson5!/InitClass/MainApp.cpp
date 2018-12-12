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

std::list<Object*> vObjects;
MousePosition currentPos;
list<MousePosition> mousePositions;
int mousePositionSaveAmount = 10;
char g_shape = RECT;


void MenuFunc(int button)
{
	switch (button) {
	case 1:
		g_shape = RECT;
		break;
	case 2:
		g_shape=TRIANGLE;
		break;
	case 3:
		g_shape=CIRCLE;
		break;
	}
	glutPostRedisplay();
}




void Lesson5()
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
	int menu;
	// 메뉴를 만들고 GLUT 에 processMenuEvents 함수가
	// 메뉴이벤트를 다룰 것이라고 알려줍니다.
	menu = glutCreateMenu(MenuFunc);

	// 메뉴에 항목을 추가합니다.
	glutAddMenuEntry("RECT", 1);
	glutAddMenuEntry("TRIANGLE", 2);
	glutAddMenuEntry("CIRCLE", 3);

	// 마우스의 오른쪽버튼에 메뉴를 연결합니다.
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT);
	

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	

	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
		if (mousePositions.size() >= mousePositionSaveAmount) { mousePositions.pop_front(); }
		y = 600 - y;
		currentPos.x = x;
		currentPos.y = y;
		mousePositions.push_back(currentPos);
		cout << "mouseregist" << endl;
		Object* newObject = new Object({ float(x),float(y),0.0f }, 30);
		if (vObjects.size() >= mousePositionSaveAmount)
		{
			list<Object*>::iterator delObject = vObjects.begin();
			delete *delObject;
			vObjects.pop_front();
			cout << "remove" << endl;
		}
		//newObject->SetSpeed(10.0f);
		vObjects.push_back(newObject);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

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
	else if (key = 's')
	{
		for (list<Object*>::iterator iter = vObjects.begin(); iter != vObjects.end(); ++iter)
		{
			Object* object = *iter;
			object->SetSpeed(-5);
		}
	}
}

