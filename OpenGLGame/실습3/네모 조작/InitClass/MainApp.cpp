// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include"InputClass.h"
#include"Collision.h"

Transform g_direction[4]{
	{ 0,0,0 },
	{ 1,0,0 },
	{ 0,1,0 },
	{ 0,0,-1 }
};

struct Object
{
	Transform position;
	Transform rotation;
	float size;

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
Object* g_LeftObject;
Object* g_RightObject;
//----------------------------------------------------------------------

list<MousePosition> g_mousePosList;
int saveAmount = 2;



int g_rotation = ROTATION_NONE;
int g_rightshape = WIRE_CUBE;
int g_leftshape = CUBE;
Transform g_WorldDegree = { 0,0,0 };
Transform g_leftRotation = { 0,0,0 };
Transform g_rightRotation = { 0,0,0 };


int g_leftRotationDirection = ROTATION_NONE;
int g_rightRotationDirection = ROTATION_NONE;

void BaseLine()
{
	cout << g_WorldDegree.x << endl;

	switch (g_rotation)
	{
	case X_AXIS:
		glRotatef(10, 1,0,0);
		//cout << g_WorldDegree;
		break;
	case Y_AXIS:
		glRotatef(10,0,1,0);
		break;
	case Z_AXIS:
		glRotatef(10,0,0,1);
		break;
	}
	g_rotation = ROTATION_NONE;

	if (g_WorldDegree.x <= 180)
	{
		glPushMatrix();
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.9, -0.5, 0.9);
		glVertex3f(0.9, -0.5, -0.9);
		glVertex3f(-0.9, -0.5, -0.9);
		glVertex3f(-0.9, -0.5, 0.9);
		glEnd();
		glPopMatrix();
	}

	glPushMatrix();
	glColor3f(1, 1, 1);
	glLineWidth(6);
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0.2f ,0.0f, 0);
	glVertex3f(0.0f, 0.0f, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0);
	glVertex3f(0.0f, 0.2f, 0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(-0.5, 0, 0);
	switch (g_leftRotationDirection)
	{
	case X_AXIS:
		glRotatef(g_leftRotation.x, 1, 0, 0);
		g_leftRotation.x += 10;
		break;
	case Y_AXIS:
		glRotatef(g_leftRotation.y, 0, 1, 0);
		g_leftRotation.y += 10;
		break;
	case Z_AXIS:
		glRotatef(g_leftRotation.z, 0, 0, 1);
		g_leftRotation.z += 10;
		break;
	}
	Render(g_leftshape);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 1, 1);
	glLineWidth(2);
	glTranslatef(0.5, 0, 0);
	switch (g_rightRotationDirection)
	{
	case X_AXIS:
		glRotatef(g_rightRotation.x, 1, 0, 0);
		g_rightRotation.x += 10;
		break;
	case Y_AXIS:
		glRotatef(g_rightRotation.y, 0, 1, 0);
		g_rightRotation.y += 10;
		break;
	case Z_AXIS:
		glRotatef(g_rightRotation.z, 0, 0, 1);
		g_rightRotation.z += 10;
		break;
	}
	Render(g_rightshape);
	glPopMatrix();

	if (g_WorldDegree.x >180)
	{
		glPushMatrix();
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.9, -0.5, 0.9);
		glVertex3f(0.9, -0.5, -0.9);
		glVertex3f(-0.9, -0.5, -0.9);
		glVertex3f(-0.9, -0.5, 0.9);
		glEnd();
		glPopMatrix();
	}
}


void Lesson16()
{
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glMatrixMode(GL_MODELVIEW);
	BaseLine();
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
		g_WorldDegree.x += 10;
		g_WorldDegree.x > 360 ? g_WorldDegree.x = 0 : NULL;
	}
	if (key == 'y')
	{
		g_rotation = Y_AXIS;
		g_WorldDegree.y += 10;
		g_WorldDegree.y > 360 ? g_WorldDegree.y = 0 : NULL;
	}
	if (key == 'z')
	{
		g_rotation = Z_AXIS;
		g_WorldDegree.z += 10;
		g_WorldDegree.z > 360 ? g_WorldDegree.z = 0 : NULL;
	}
	if (key == 'i')
	{
		g_WorldDegree.x = 0;
		g_WorldDegree.y = 0;
		g_WorldDegree.z = 0;
		g_leftRotationDirection = ROTATION_NONE;
		glLoadIdentity();
	}
	if (key == 'l')
	{
		srand(time(NULL));
		g_leftRotationDirection = rand() % 3 + 1;	
	}
	if (key == 'r')
	{
		srand(time(NULL));
		g_rightRotationDirection = rand() % 3 + 1;
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
		g_leftshape = CUBE;
		g_rightshape = WIRE_CUBE;
		break;
	case 2:
		g_leftshape = SPHERE;
		g_rightshape = WIRE_SPHERE;
		break;
	case 3:
		g_leftshape = CONE;
		g_rightshape = WIRE_CONE;
		break;
	case 4:
		g_leftshape = TEAPOT;
		g_rightshape = WIRE_TEAPOT;
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
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Sphere", 2);
	glutAddMenuEntry("Cone", 3);
	glutAddMenuEntry("Teapot", 4);

	// 마우스의 오른쪽버튼에 메뉴를 연결합니다.
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}