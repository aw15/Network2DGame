// 실습24.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//


#include "stdafx.h"

int g_shape = WIRE_SPHERE;
Transform g_rotation = { 0,0,0 };



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
		position = { 0,0,0 };
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


int g_Menu;
bool culling = false, depth = false, shading = false, upAnimation = false, frontAnimation = false;


list<MousePosition> g_mousePosList;
int saveAmount = 2;


void WorldRotation()
{
	glRotatef(g_rotation.x, 1, 0, 0);
	glRotatef(g_rotation.y, 0, 1, 0);
	glRotatef(g_rotation.z, 0, 0, 1);
}
int g_y = 0;
void Floor()
{
	if (shading)
		glShadeModel(GL_SMOOTH); // 또는 glShadeModel (GL_FLAT)
	else
		glShadeModel(GL_FLAT);
	glPushMatrix();
		glBegin(GL_QUADS);
		//-------------------------밑면----------------------------------
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex3f(-300.0, -300.0, 100.0);
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(-300.0, -300.0, 300.0);
		glColor3f(0.0f, 1.0f, 1.0f); // Cyan
		glVertex3f(300.0, -300.0, 300.0);
		glColor3f(1.0f, 0.0, 1.0f); // Magenta
		glVertex3f(300.0, -300.0, 100.0);
		//-----------------------------------------------------------
		glEnd();
	glPopMatrix();
	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, -300.0, 200.0);
	glVertex3f(0.0, 0.0, 200.0);
	glEnd();
}
vector<Object*> g_donutList;
Transform g_LastPoint = {0,0,200};

void CreateDonut()
{
	auto newObject = new Object();
	newObject->position = g_LastPoint;
	g_donutList.push_back(newObject);
}

void DonutAnimation()
{
	static bool first = true;
	static int minY = -270;
	Object* activeDonut;
	if (first)
	{
		CreateDonut();
		first = false;
	}

	for (int i=0;i<g_donutList.size()-1;i++)
	{
		glPushMatrix();
		auto pos = g_donutList[i]->position;
		auto rot = g_donutList[i]->rotation;
		
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(-90, 1, 0, 0);
		glutWireTorus(10, 100, 10, 10);
		glPopMatrix();
	}
	activeDonut = g_donutList[g_donutList.size() - 1];
	auto pos = activeDonut->position;
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -30, 0);
	glRotatef(activeDonut->rotation.z, 0, 0, 1);
	glTranslatef(0, 30, 0);
	if (activeDonut->position.y >= minY)
	{
		activeDonut->rotation.z += 50;
		activeDonut->position.y -= 10;
	}
	else
	{
		if (minY >= 0)
		{
			g_donutList.clear();
			minY = -270;
		}
		else
		{
			minY += 20;
		}
		CreateDonut();
		
	}
	glutWireTorus(10, 100, 10, 10);
	glPopMatrix();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기
	glPushMatrix();
	WorldRotation();
	if (depth)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	if (culling)
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	glMatrixMode(GL_MODELVIEW);
	Floor();
	DonutAnimation();

	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}
int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 30); // 윈도우의 위치지정 
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 

	Initialize();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutSpecialFunc(KeyboardSpecialKey);
	glutMotionFunc(Motion);
	glutMainLoop();


	return 0;
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. 
	// . 클리핑 공간 설정: 원근 투영인 경우 
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	glTranslatef(0.0, 0.0, -1000); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
								   // 2. 클리핑 공간 설정: 직각 투영인 경우
								   // glOrtho (0, 800.0, 0.0, 600.0, -1.0, 00.0);
								   // 모델 뷰 행렬 스택 재설정 
								   //glOrtho(-500, 500, -500, 500, 0.0,1000 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0, 1, 0);
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
		if (g_mousePosList.size() >= saveAmount)
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
		g_rotation.x += 10;
	}
	if (key == 'y')
	{
		g_rotation.y += 10;
	}
	if (key == 'z')
	{
		g_rotation.z += 10;
	}
	if (key == 'X')
	{
		g_rotation.x -= 10;
	}
	if (key == 'Y')
	{
		g_rotation.y -= 10;
	}
	if (key == 'Z')
	{
		g_rotation.z -= 10;
	}
	if (key == 'i')
	{
		glLoadIdentity();
		g_rotation = { 0,0,0 };
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
	case 1://은면제거
		depth == true ? depth = false : depth = true;
		break;
	case 2://컬링
		culling == true ? culling = false : culling = true;
		break;
	case 3://쉐이딩
		shading == true ? shading = false : shading = true;
		break;
	case 4://윗면
		upAnimation == true ? upAnimation = false : upAnimation = true;
		break;
	case 5://앞면
		frontAnimation == true ? frontAnimation = false : frontAnimation = true;
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
		glutSolidCone(0.3, 0.3, 20, 20);
		break;
	case WIRE_CONE:
		glRotatef(270, 1, 0, 0);
		glutWireCone(0.3, 0.3, 20, 20);
		break;
	case SPHERE:
		glutSolidSphere(0.3, 20, 20);
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
	glutAddMenuEntry("depth", 1);
	glutAddMenuEntry("culling", 2);
	glutAddMenuEntry("shading", 3);
	glutAddMenuEntry("frontAnimation", 4);
	glutAddMenuEntry("upAnimation", 5);

	// 마우스의 오른쪽버튼에 메뉴를 연결합니다.
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

