// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"

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


int g_Menu;
bool culling = false, depth = false, shading = false, upAnimation=false,frontAnimation = false;


list<MousePosition> g_mousePosList;
int saveAmount = 2;



int g_rotation = ROTATION_NONE;

Transform g_WorldDegree = { 0,0,0 };


void WorldRotation()
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
}
int g_y = 0;
void Quad()
{
	glPushMatrix();
	glTranslatef(0, 0, 200);
	glRotatef(30, 1, 0, 0);
	glRotatef(45+g_y, 0, 1, 0);
	cout << g_y<<endl;
	glTranslatef(0, 0, -200);
	g_y += 1;
	if (shading)
	{
		glShadeModel(GL_SMOOTH); // 또는 glShadeModel (GL_FLAT)
	}
	else
	{
		glShadeModel(GL_FLAT);
	}
	glBegin(GL_QUADS);
	//----------------------왼쪽면-------------------------------------
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(-100.0, 100.0, 300.0);
	glColor3f(1.0f, 0.0, 1.0f); // Magenta
	glVertex3f(-100.0, 100.0, 100.0);
	glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glVertex3f(-100.0, -100.0, 100.0);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(-100.0, -100.0, 300.0);
	//------------------------오른쪽면-----------------------------------
	glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glVertex3f(100.0, 100.0, 100.0);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(100.0, 100.0, 300.0);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(100.0, -100.0, 300.0);
	glColor3f(1.0f, 0.0, 1.0f); // Magenta
	glVertex3f(100.0, -100.0, 100.0);
	//------------------------뒷면----------------------------------
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(100.0, -100.0, 100.0);
	glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glVertex3f(-100.0, -100.0, 100.0);
	glColor3f(1.0f, 0.0, 1.0f); // Magenta
	glVertex3f(-100.0, 100.0, 100.0);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(100.0, 100.0, 100.0);
	//-------------------------밑면----------------------------------
	glColor3f(1.0f, 0.0, 1.0f); // Magenta
	glVertex3f(100.0, -100.0, 100.0);
	glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glVertex3f(100.0, -100.0, 300.0);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(-100.0, -100.0, 300.0);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(-100.0, -100.0, 100.0);
	//-----------------------------------------------------------
	glEnd();

	static int front_x = 0;
	
	//-------------------------윗면----------------------------------
	static int frontAnimationDir = 1;
	
		glPushMatrix();
		glTranslatef(0, -100, 300);
		glRotatef(front_x, 1, 0, 0);
		glTranslatef(0, 100, -300);
		if(frontAnimation)
			front_x += frontAnimationDir * 5;
		if (front_x > 90)
			frontAnimationDir *= -1;
		if (front_x < 0 )
			frontAnimationDir *= -1;
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex3f(100.0, 100.0, 300.0);
		glColor3f(1.0f, 0.0, 1.0f); // Magenta
		glVertex3f(-100.0, 100.0, 300.0);
		glColor3f(0.0f, 1.0f, 1.0f); // Cyan
		glVertex3f(-100.0, -100.0, 300.0);
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(100.0, -100.0, 300.0);
		glEnd();
		glPopMatrix();
	//-----------------------------------------------------------
	//----------------------윗면----------------------------------
		static int upAnimationDir = 1, up_x =0;
		glPushMatrix();
		glTranslatef(0, 100, 100);
		glRotatef(up_x, 1, 0, 0);
		glTranslatef(0, -100, -100);

		if(upAnimation)
			up_x -= upAnimationDir * 5;
		if (up_x < -90)
			upAnimationDir *= -1;
		if (up_x > 0)
			upAnimationDir *= -1;
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex3f(-100.0, 100.0, 100.0);
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(-100.0, 100.0, 300.0);
		glColor3f(0.0f, 1.0f, 1.0f); // Cyan
		glVertex3f(100.0, 100.0, 300.0);
		glColor3f(1.0f, 0.0, 1.0f); // Magenta
		glVertex3f(100.0, 100.0, 100.0);
		glEnd();
		glPopMatrix();
	glPopMatrix();
}



GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기
	
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
	Quad();
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
	gluPerspective(60.0f, w / h,1.0, 2000.0);
	glTranslatef(0.0, 0.0, -1000); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
									// 2. 클리핑 공간 설정: 직각 투영인 경우
									// glOrtho (0, 800.0, 0.0, 600.0, -1.0, 00.0);
									// 모델 뷰 행렬 스택 재설정 
	//glOrtho(-500, 500, -500, 500, 0.0,1000 );
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
		g_WorldDegree.x +=10;
	}
	if (key == 'y')
	{
		g_rotation = Y_AXIS;
		g_WorldDegree.y +=10;
	}
	if (key == 'z')
	{
		g_rotation = Z_AXIS;
		g_WorldDegree.z +=10;
	}
	if (key == 'X')
	{
		g_rotation = X_AXIS;
		g_WorldDegree.x += -10;
	}
	if (key == 'Y')
	{
		g_rotation = Y_AXIS;
		g_WorldDegree.y += -10;
	}
	if (key == 'Z')
	{
		g_rotation += Z_AXIS;
		g_WorldDegree.z = -10;
	}
	if (key == 'i')
	{
		glLoadIdentity();
		g_y = 0;
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
	glutAddMenuEntry("depth", 1);
	glutAddMenuEntry("culling", 2);
	glutAddMenuEntry("shading", 3);
	glutAddMenuEntry("frontAnimation", 4);
	glutAddMenuEntry("upAnimation", 5);

	// 마우스의 오른쪽버튼에 메뉴를 연결합니다.
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}