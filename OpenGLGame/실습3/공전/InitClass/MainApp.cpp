// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include"InputClass.h"
#include"Collision.h"

int g_shape = WIRE_SPHERE;

Transform g_direction[4]{
	{ 0,0,0 },
	{ 1,0,0 },
	{ 0,1,0 },
	{ 0,0,-1 }
};

class Object
{
public:
	Object()
	{
		position = {0,0,0};
		rotation = { 0,0,0 };
		size = 0.0f;
		degree = 0;
		index = 0;
	}
	Transform position;
	Transform rotation;
	float size;
	int degree;
	int index;
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecialKey(int key, int x, int y);
void MenuFunc(int button);
void Motion(int x, int y);
//---------custom function
void Render(int shape);
void Initialize();

Collision g_collision;//물리엔진

int g_Menu;
//--------------------------------------------------------------------
Object g_first;
//----------------------------------------------------------------------

list<MousePosition> g_mousePosList;
int saveAmount = 2;



int g_rotation = ROTATION_NONE;
Transform g_WorldDegree = { 0,0,0 };


void Base()
{
	switch (g_rotation)
	{
	case X_AXIS:
		glRotatef(g_WorldDegree.x, 1,0,0);
		break;
	case Y_AXIS:
		glRotatef(g_WorldDegree.y,0,1,0);
		break;
	case Z_AXIS:
		glRotatef(g_WorldDegree.z,0,0,1);
		break;
	}
	g_rotation = ROTATION_NONE;
	

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(1.2f, 0.0f, 0);
	glVertex3f(0.0f, 0.0f, 0);
	glColor3f(1, 1, 0);
	glVertex3f(0.0f, 0.0f, 0);
	glVertex3f(0.0f, 1.2f, 0);
	glEnd();


	glColor3f(1, 0.2, 0);
	glTranslatef(0, 0, 0);
	Render(g_shape);
	glPopMatrix();
}

float firstIndex = 0;
float secondIndex = 0;
float thirdIndex = 40;

float firstMoonIndex = 60;
float secondMoonIndex = 120;
float thirdMoonIndex = 100;

void Lesson16()
{
	float x, y, moonX,moonY;
	glLineWidth(1);
	glPushMatrix();
		glPushMatrix();
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 360; i += 10)
		{
			x = cos(ANGLE*i) * 3;
			y = sin(ANGLE*i) * 3;;
			glVertex3f(x, 0, y);
		}
		glEnd();
	glPopMatrix();
	glColor3f(1, 1, 0);
	x=cos(ANGLE*firstIndex)*3;
	y =sin(ANGLE*firstIndex)*3;
	glTranslatef(x,0,y);
	Render(g_shape);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 360; i += 10)
		{
			x = cos(ANGLE*i) * 1;
			y = sin(ANGLE*i) * 1;
			glVertex3f(x, 0, y);
		}
		glEnd();
		moonX = cos(ANGLE*firstMoonIndex) * 1;
		moonY = sin(ANGLE*firstMoonIndex) * 1;
		glTranslatef(moonX, 0, moonY);
		glScalef(0.5, 0.5, 0.5);
		Render(g_shape);
		firstMoonIndex += 20;
	firstIndex += 10;
	glPopMatrix();

	glPushMatrix();
		glPushMatrix();
		glRotatef(45, 0, 0, 1);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 360; i += 10)
		{
			x = cos(ANGLE*i) * 3;
			y = sin(ANGLE*i) * 3;;
			glVertex3f(x, 0, y);
		}
		glEnd();
		glPopMatrix();
		glColor3f(0, 1, 0);
		x = cos(ANGLE*secondIndex) * 3;
		y = sin(ANGLE*secondIndex) * 3;
		glRotatef(45, 0, 0, 1);
		glTranslatef(x, 0, y);
		Render(g_shape);
		secondIndex += 5;
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 360; i += 10)
			{
				x = cos(ANGLE*i) * 1;
				y = sin(ANGLE*i) * 1;
				glVertex3f(x, 0, y);
			}
			glEnd();
			moonX = cos(ANGLE*secondMoonIndex) * 1;
			moonY = sin(ANGLE*secondMoonIndex) * 1;
			glTranslatef(moonX, 0, moonY);
			glScalef(0.5, 0.5, 0.5);
			Render(g_shape);
			secondMoonIndex += 20;
	glPopMatrix();

	glPushMatrix();
		glPushMatrix();
		glRotatef(-45, 0, 0, 1);
		glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 360; i+=10)
			{
				x = cos(ANGLE*i) * 3;
				y = sin(ANGLE*i) * 3;;
				glVertex3f(x, 0,y);
			}
			glEnd();
		glPopMatrix();
		glColor3f(0, 1, 1);
		x = cos(ANGLE*thirdIndex) * 3;
		y = sin(ANGLE*thirdIndex) * 3;
		glRotatef(-45, 0, 0, 1);
		glTranslatef(x, 0, y);
		Render(g_shape);
		thirdIndex += 2;
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 360; i += 10)
			{
				x = cos(ANGLE*i) * 1;
				y = sin(ANGLE*i) * 1;
				glVertex3f(x, 0, y);
			}
			glEnd();
			moonX = cos(ANGLE*thirdMoonIndex) * 1;
			moonY = sin(ANGLE*thirdMoonIndex) * 1;
			glTranslatef(moonX, 0, moonY);
			glScalef(0.5, 0.5, 0.5);
			Render(g_shape);
			thirdMoonIndex += 10;
	glPopMatrix();

}



GLvoid drawScene(GLvoid)
{
	static int i = 0;
	i += 10;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	Base();
	Lesson16();
	glutSwapBuffers(); // 화면에 출력하기
}
int main()
{
	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT,&MenuFunc);

	Initialize();

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
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. 
	// . 클리핑 공간 설정: 원근 투영인 경우 
	gluPerspective(60.0f, w / h,1.0, 1000.0);
	glTranslatef(0.0, 0.0, -10); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
									// 2. 클리핑 공간 설정: 직각 투영인 경우
									// glOrtho (0, 800.0, 0.0, 600.0, -1.0, 00.0);
									// 모델 뷰 행렬 스택 재설정 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0 , 0,1,0 );
}

void TimerFunction(int value)
{
	
	glutPostRedisplay(); // 화면 재 출력, drawscene이 호출
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
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
		if (g_mousePosList.size()>=saveAmount)
		{
			g_mousePosList.clear();
		}
		g_mousePosList.push_back({ inputX,inputY });
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
		g_rotation = X_AXIS;
		g_WorldDegree.x =10;
	}
	if (key == 'y')
	{
		g_rotation = Y_AXIS;
		g_WorldDegree.y =10;
	}
	if (key == 'z')
	{
		g_rotation = Z_AXIS;
		g_WorldDegree.z =10;
	}
	if (key == 'X')
	{
		g_rotation = X_AXIS;
		g_WorldDegree.x = -10;
	}
	if (key == 'Y')
	{
		g_rotation = Y_AXIS;
		g_WorldDegree.y = -10;
	}
	if (key == 'Z')
	{
		g_rotation = Z_AXIS;
		g_WorldDegree.z = -10;
	}
	if (key == 'i')
	{
		g_WorldDegree.x = 0;
		g_WorldDegree.y = 0;
		g_WorldDegree.z = 0;
		glLoadIdentity();
	}
	if (key == 'd')
	{
		glTranslatef(0.1, 0, 0);
	}
	if (key == 'a')
	{
		glTranslatef(-0.1, 0, 0);
	}
	if (key == 'w')
	{
		glTranslatef(0, 0.1, 0);
	}
	if (key == 's')
	{
		glTranslatef(0, -0.1, 0);
	}
	if (key == '+')
	{
		glTranslatef(0, 0, 10);
	}
	if (key == '-')
	{
		glTranslatef(0, 0, -10);
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
		g_shape = WIRE_SPHERE;
		break;
	case 2:
		g_shape = SPHERE;
		break;

	}
	glutPostRedisplay();
}
void Render(int shape)
{
	switch (shape)
	{
	case CUBE:
		glutSolidCube(0.3);
		break;
	case WIRE_CUBE:
		glutWireCube(0.3);
		break;
	case CONE:
		glRotatef(270, 1, 0, 0);
		glutSolidCone(0.3,0.3,20,20);
		break;
	case WIRE_CONE:
		glRotatef(270, 1, 0, 0);
		glutWireCone(0.3, 0.3, 20, 20);
		break;
	case SPHERE:
		glutSolidSphere(0.3,20,20);
		break;
	case WIRE_SPHERE:
		glutWireSphere(0.3, 20, 20);
		break;
	case TEAPOT:
		glutSolidTeapot(0.3);
		break;
	case WIRE_TEAPOT:
		glutWireTeapot(0.3);
		break;
	}
}
void Initialize()
{
	// 메뉴를 만들고 GLUT 에 processMenuEvents 함수가
	// 메뉴이벤트를 다룰 것이라고 알려줍니다.
	g_Menu = glutCreateMenu(MenuFunc);

	// 메뉴에 항목을 추가합니다.
	glutAddMenuEntry("Wire", 1);
	glutAddMenuEntry("Solid", 2);

	// 마우스의 오른쪽버튼에 메뉴를 연결합니다.
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}