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
		scale = { 1,1,1 };
		size = 0.0f;
		degree = 0;
		index = 0;
	}
	Transform position;
	Transform rotation;
	Transform scale;
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
Object g_Bottom;
Object g_Middle;
Object g_Top;
Object g_Floor;
//----------------------------------------------------------------------

list<MousePosition> g_mousePosList;
int saveAmount = 2;



int g_rotation = ROTATION_NONE;
int g_ballRotation = ROTATION_NONE;
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
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(g_Floor.position.x, g_Floor.position.y, g_Floor.position.z);
	glScalef(g_Floor.scale.x, g_Floor.scale.y, g_Floor.scale.z);
	glutSolidCube(g_Floor.size);
	glPopMatrix();
	glPushMatrix();//맨밑에 부분
		glColor3f(0, 0, 1);
		glTranslatef(g_Bottom.position.x, g_Bottom.position.y, g_Bottom.position.z);
		glScalef(g_Bottom.scale.x, g_Bottom.scale.y, g_Bottom.scale.z);
		glRotatef(g_Bottom.rotation.y, 0, 1, 0);
		glutSolidCube(g_Bottom.size);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(g_Bottom.position.x, 0, 0);
		glRotatef(g_Bottom.rotation.y, 0, 1, 0);
		glRotatef(g_Middle.rotation.x, 1, 0, 0);
		glTranslatef(0, g_Middle.position.y, g_Bottom.position.z);
		glRotatef(g_Middle.rotation.y, 0, 1, 0);
		glScalef(g_Middle.scale.x, g_Middle.scale.y, g_Middle.scale.z);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(g_Bottom.position.x, 0, 0);
		glRotatef(g_Bottom.rotation.y, 0, 1, 0);
		glRotatef(g_Middle.rotation.x, 1, 0, 0);
		glTranslatef(0, g_Middle.position.y, g_Bottom.position.z);
		glRotatef(g_Middle.rotation.y, 0, 1, 0);
		glTranslatef(0, 0.6f, 0);
		glRotatef(g_Top.rotation.x, 1, 0, 0);
		glRotatef(g_Top.rotation.z, 0, 0, 1);
		glTranslatef(0, g_Top.position.y-0.6f, 0);
		glScalef(g_Top.scale.x, g_Top.scale.y, g_Top.scale.z);
		glutSolidCube(0.3);
	glPopMatrix();
}


void Lesson16()
{
	
}



GLvoid drawScene(GLvoid)
{
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

	g_Floor.position = { 0,-1,0 };
	g_Floor.scale = { 30,1,30 };
	g_Floor.size = 0.2f;

	g_Bottom.position = { 0,-0.45f,0 };
	g_Bottom.scale = { 3,1,2 };
	g_Bottom.size = 0.5f;

	g_Middle.position = { 0,0.3f,0 };
	g_Middle.scale = { 1,2,1 };

	g_Top.position = { 0,0.8f,0 };
	g_Top.scale = { 1,2,1 };

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
		g_Floor.position = { 0,-1,0 };
		g_Floor.scale = { 30,1,30 };
		g_Floor.size = 0.2f;

		g_Bottom.position = { 0,-0.45f,0 };
		
		g_Middle.rotation = { 0,0,0 };
		g_Top.rotation = { 0,0,0 };
		g_Bottom.rotation = { 0,0,0 };
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
	if (key == 'c')
	{
		g_Bottom.position.x += 0.1;
	}
	if (key == 'C')
	{
		g_Bottom.position.x -= 0.1;
	}

	if (key == 'v')
	{
		g_Bottom.rotation.y += -10;
	}
	if (key == 'V')
	{
		g_Bottom.rotation.y += 10;
	}
	if (key == 'M')
	{
		g_Middle.rotation.y += 10;
	}
	if (key == 'm')
	{
		
		g_Middle.rotation.y += -10;

	}
	if (key == 'N')
	{
		if (g_Middle.rotation.x < 90)
		{
			g_Middle.rotation.x += 10;
			//g_Middle.position.y += index*0.1;
			//g_Middle.scale.y += 0.1;
		}
	}
	if (key == 'n')
	{
		if (g_Middle.rotation.x > -90)
		{
			g_Middle.rotation.x -= 10;
			//g_Middle.position.y +=  dir*0.1;
			//g_Middle.scale.y -= 0.1;
		}
	}
	if (key == 'J')
	{
		if (g_Top.rotation.x < 90)
		{
			g_Top.rotation.x += 10;
			//g_Middle.position.y +=  dir*0.1;
			//g_Middle.scale.y -= 0.1;
		}
	}
	if (key == 'j')
	{
		if (g_Top.rotation.x > -90)
		{
			g_Top.rotation.x -= 10;
			//g_Middle.position.y +=  dir*0.1;
			//g_Middle.scale.y -= 0.1;
		}
	}
	if (key == 'K')
	{
		if (g_Top.rotation.z < 90)
		{
			g_Top.rotation.z += 10;
			//g_Middle.position.y +=  dir*0.1;
			//g_Middle.scale.y -= 0.1;
		}

	}
	if (key == 'k')
	{
		if (g_Top.rotation.z > -90)
		{
			g_Top.rotation.z -= 10;
			//g_Middle.position.y +=  dir*0.1;
			//g_Middle.scale.y -= 0.1;
		}

	}
}

void KeyboardSpecialKey(int key, int x, int y)
{
	//if (key == GLUT_KEY_F1)

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