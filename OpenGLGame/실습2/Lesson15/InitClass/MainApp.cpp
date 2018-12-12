// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include "Object.h"
#include"InputClass.h"
#include"Collision.h"

Transform g_direction[4]{
	{ 0,0,0 },
	{ 1,0,0 },
	{ 0,1,0 },
	{ 0,0,-1 }
};


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecialKey(int key, int x, int y);
void MenuFunc(int button);
void Motion(int x, int y);

std::list<Object*> g_objectList;





int g_shape = RECT;
//모양 기억
bool quit = false;

Collision g_collision;

int saveAmount = 20;


bool g_animation = false;
float g_scaling = 0.8;



int g_rotation = Y_AXIS;
int g_degree=-10;
int g_target = 1;
int g_degreeForSmallTriangle = 0;

void Lesson15()
{
	//glutWireCube(0.5);//sets scale of wire cube
	list<Object*>::iterator iter;
	for (iter = g_objectList.begin(); iter != g_objectList.end();)
	{
		
		Object* currentObject = *iter;
		
		currentObject->Render();
		currentObject->Move(g_direction[Z_AXIS]);
		cout <<g_objectList.size()<<endl;
		if (currentObject->GetSize() >= 5.0)
		{
			iter = g_objectList.erase(iter);
			currentObject->Release();
			delete currentObject;
		}
		else
			++iter;
	}
}

int main()
{
	int rectcount = 0;
	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT,&MenuFunc);
	//glRotatef(90, 0, 1, 0);
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
	Lesson15();
	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. 
	// . 클리핑 공간 설정: 원근 투영인 경우 
	gluPerspective(60.0f, w / h, -1, 1);
	glTranslatef(0.0, 0.0, -3); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
									// 2. 클리핑 공간 설정: 직각 투영인 경우
									// glOrtho (0, 800.0, 0.0, 600.0, -1.0, 00.0);
									// 모델 뷰 행렬 스택 재설정 
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}

void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력, drawscene이 호출
	glutTimerFunc(500, TimerFunction, 1); // 타이머함수 재 설정
}

void Mouse(int button, int state, int x, int y)//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
{
	float inputX, inputY;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		inputY = 700 - y;

		inputX = (float)(x - (float)WINDOW_WIDTH / 2.0)*(float)(1.0 / (float)(WINDOW_WIDTH / 2.0));

		inputY = -(float)(y - (float)WINDOW_HEIGHT / 2.0)*(float)(1.0 / (float)(WINDOW_HEIGHT / 2.0));

		//cout << inputX << " " << inputY <<  "mouseregist" << endl;
		if (g_objectList.size()>saveAmount)
		{
			return;
		}
		Object* newObject = new Object({ inputX,inputY,1 }, 1);
		srand(time(NULL));
		int shape;
		switch (rand() % 5)
		{
		case 0:
			shape = CUBE;
			break;
		case 1:
			shape = CONE;
			break;
		case 2:
			shape = SPHERE;
			break;
		case 3:
			shape = TORUS;
			break;
		case 4:
			shape = TEAPOT;
			break;
		}
		int index = rand() % 3 + 1;
		newObject->SetRotation(g_direction[index],10);
		newObject->SetShape(shape);
		g_objectList.push_back(newObject);
	}
	//else if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	//{
	//	y = 600 - y;
	//}

}
void Motion(int x, int y)
{
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		g_objectList.clear();
		quit = true;
	}
}

void KeyboardSpecialKey(int key, int x, int y)
{
	//if (key == GLUT_KEY_F1)
	//{
	//	currentObject = new Object({ 0,0,0 }, 0.8);
	//	g_boundary->SetTransform({ 0, 0, 0 });
	//	g_boundaryShape = CIRCLE;
	//}
	//if (key == GLUT_KEY_F2)
	//{
	//	currentObject = new Object({ 0,0,0 }, 0.8);
	//	g_boundary->SetTransform({ -1, 0, 0 });
	//	g_boundaryShape = SIN;
	//}
	//if (key == GLUT_KEY_F3)
	//{
	//	currentObject = new Object({ 0,0,0 }, 0.8);
	//	g_boundary->SetTransform({ 0, 0, 0 });
	//	g_boundaryShape = LINE;
	//}
	//if (key == GLUT_KEY_F4)
	//{
	//	currentObject = new Object({ 0,0,0 }, 0.8);
	//	g_boundary->SetTransform({ 0, 0, 0 });
	//	g_boundaryShape = POINT_;
	//}
	//if (key == GLUT_KEY_F5)
	//{
	//	currentObject = new Object({ 0,0,0 }, 0.8);
	//	g_boundary->SetTransform({ 0, 0, 0 });
	//	g_boundaryShape = TONADO;
	//}
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