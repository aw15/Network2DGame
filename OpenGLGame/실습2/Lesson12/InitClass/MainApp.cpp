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
Object* g_boundary = new Object({ 0,0,0 }, 10);
Object* currentObject;
char g_boundaryShape=TONADO;
int g_shape = RECT;
//모양 기억


Collision g_collision;

MousePosition currentMousePos;
int saveAmount = 0;
MousePosition g_MousePos[5];


bool g_animation = false;

float g_scaling = 0.8;



int g_rotation = ROTATION_NONE;
int g_degree=0;

int g_smalldegree = 0;

Transform g_direction[4]{
	{ 0,0,0 },
	{ 1,0,0 },
	{ 0,1,0 },
	{ 0,0,1 }
};

void Lesson12()
{
	
	
		currentObject->SetRotation(g_direction[g_rotation], g_degree);
		currentObject->SetSize(g_scaling);


		switch (g_boundaryShape)//움직이는 형태
		{
		case CIRCLE:
			currentObject->Move(CIRCLE);
			break;
		case SIN:
			currentObject->Move(SIN);
			break;
		case TONADO:
			currentObject->Move(TONADO);
			break;
		case LINE:
			currentObject->Move(LINE);
			break;
		case POINT_:
			if(g_animation)
				currentObject->Move(POINT_, g_MousePos,saveAmount);
			break;
		}


		// 기본 도형 그리기
		if (g_shape == TRIANGLE)
		{
			currentObject->Render(TRIANGLE);
		}
		else
		{
			currentObject->Render(RECT);
		}
}

int main()
{
	int rectcount = 0;
	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT,&MenuFunc);
	currentObject = new Object({ 0,0,0 }, 0.8);
	

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
	switch (g_boundaryShape)
	{
		glLoadIdentity();
	case CIRCLE:
		g_boundary->Render(CIRCLE);
		break;
	case SIN:
		g_boundary->Render(SIN);
		
		break;
	case TONADO:
		g_boundary->Render(TONADO);
		break;
	case LINE:
		g_boundary->Render(LINE);
		break;
	case POINT_:
		glBegin(GL_LINE_STRIP);
		for (int i = 0;i<saveAmount;++i)
		{
			glVertex2f(g_MousePos[i].x, g_MousePos[i].y);
		}
		glEnd();
		break;
	}



	Lesson12();
	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w,h);
	
}

void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력, drawscene이 호출
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Mouse(int button, int state, int x, int y)//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
{
	currentMousePos.x = x;
	currentMousePos.y = y;
	float inputX, inputY;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& g_boundaryShape ==POINT_)
	{
		inputY = 700 - y;

		inputX = (float)(x - (float)WINDOW_WIDTH / 2.0)*(float)(1.0 / (float)(WINDOW_WIDTH / 2.0));

		inputY = -(float)(y - (float)WINDOW_HEIGHT / 2.0)*(float)(1.0 / (float)(WINDOW_HEIGHT / 2.0));

		//cout << inputX << " " << inputY <<  "mouseregist" << endl;
		if (saveAmount>4)
		{
			return;
		}
		g_MousePos[saveAmount].x = inputX;
		g_MousePos[saveAmount].y = inputY;
		saveAmount++;
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
		g_rotation = ROTATION_X;
		g_degree += 10;
	}
	else if (key == 'y')
	{
		g_rotation = ROTATION_Y;
		g_degree += 10;
	}
	else if (key == 'z')
	{
		g_rotation = ROTATION_Z;
		g_degree += 10;  
	}
	else if (key == 'i')
	{
		g_scaling = 0.8;
		g_degree = 0;
		g_animation = false;
		saveAmount = 0;
		currentObject = new Object({ 0,0,0 }, 0.8);
		//g_boundary->SetTransform({ 0, 0, 0 });
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
	else if (key == 'r')
	{
		glLoadIdentity();
		g_shape = RECT;
		//glScaled(0.9, 0.9, 0.9);
	}
	else if (key == 't')
	{
		glLoadIdentity();
		g_shape = TRIANGLE;
		//glScaled(0.9, 0.9, 0.9);
	}
	else if (key == 'a')
	{
		g_degree = 0;
		
	}
	else if (key == 'A')
	{
		g_animation = true;
	}
}

void KeyboardSpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		currentObject = new Object({ 0,0,0 }, 0.8);
		g_boundary->SetTransform({ 0, 0, 0 });
		g_boundaryShape = CIRCLE;
	}
	if (key == GLUT_KEY_F2)
	{
		currentObject = new Object({ 0,0,0 }, 0.8);
		g_boundary->SetTransform({ -1, 0, 0 });
		g_boundaryShape = SIN;
	}
	if (key == GLUT_KEY_F3)
	{
		currentObject = new Object({ 0,0,0 }, 0.8);
		g_boundary->SetTransform({ 0, 0, 0 });
		g_boundaryShape = LINE;
	}
	if (key == GLUT_KEY_F4)
	{
		currentObject = new Object({ 0,0,0 }, 0.8);
		g_boundary->SetTransform({ 0, 0, 0 });
		g_boundaryShape = POINT_;
	}
	if (key == GLUT_KEY_F5)
	{
		currentObject = new Object({ 0,0,0 }, 0.8);
		g_boundary->SetTransform({ 0, 0, 0 });
		g_boundaryShape = TONADO;
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