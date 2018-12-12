#include "stdafx.h"



int g_shape = WIRE_SPHERE;
Vector3 g_worldRotation = { 0,0,0 };



Vector3 g_direction[4]{
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
	}
	void Move(float speed)
	{
		if (position.x > -80 && direction.x == -100)
		{
			position.x += direction.x * speed;
		}
		if (position.x < 80 && direction.x == 100)
		{
			position.x += direction.x * speed;
		}
		if (position.y >= -80 && direction.y == -100)
		{
			position.y += direction.y * speed;
		}
		if (position.y <= 80 && direction.y == 100)
		{

			position.y += direction.y * speed;
		}

	}
	void RandomMove(float speed)
	{
		if (position.x <= -80)
		{
			direction.x *= -1;
		}
		if (position.x >= 80)
		{
			direction.x *= -1;
		}
		if (position.y <= -80)
		{
			direction.y *= -1;
		}
		if (position.y >= 80)
		{
			direction.y *= -1;
		}
		position.x += direction.x * speed;
		position.y += direction.y * speed;
	}
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Vector3 direction;
	float size;
	int degree;
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
vector<Vector2> g_mousePoints;
bool isSetting = false;


void WorldRotation()
{
	glRotatef(g_worldRotation.x, 1, 0, 0);
	glRotatef(g_worldRotation.y, 0, 1, 0);
	glRotatef(g_worldRotation.z, 0, 0, 1);
}
void Quad()
{
	glPushMatrix();
	glTranslatef(0, 0, 200);
	glTranslatef(0, 0, -200);
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
	glColor3f(0.6f, 0.3f, 1.0f); // Yellow
	glVertex3f(-100.0, 100.0, 300.0);
	glVertex3f(-100.0, 100.0, 100.0);
	glVertex3f(-100.0, -100.0, 100.0);
	glVertex3f(-100.0, -100.0, 300.0);
	//------------------------오른쪽면-----------------------------------
	glColor3f(0.6f, 0.3f, 1.0f); // Yellow
	glVertex3f(100.0, 100.0, 100.0);
	glVertex3f(100.0, 100.0, 300.0);
	glVertex3f(100.0, -100.0, 300.0);
	glVertex3f(100.0, -100.0, 100.0);
	//------------------------뒷면----------------------------------
	glColor3f(0.0f, 0.0f, 0.3f); // Blue
	glVertex3f(100.0, -100.0, 100.0);
	glVertex3f(-100.0, -100.0, 100.0);
	glVertex3f(-100.0, 100.0, 100.0);
	glVertex3f(100.0, 100.0, 100.0);
	//-------------------------밑면----------------------------------
	glColor3f(0.4f, 0.0f, 1.0f); // Yellow
	glVertex3f(100.0, -100.0, 100.0);
	glVertex3f(100.0, -100.0, 300.0);
	glVertex3f(-100.0, -100.0, 300.0);
	glVertex3f(-100.0, -100.0, 100.0);
	//----------------------윗면-------------------------------------
	glColor3f(0.4f, 0.0f, 1.0f); // Yellow
	glVertex3f(-100.0, 100.0, 100.0);
	glVertex3f(-100.0, 100.0, 300.0);
	glVertex3f(100.0, 100.0, 300.0);
	glVertex3f(100.0, 100.0, 100.0);
	glEnd();
	glPopMatrix();
}
void DrawLine()
{
	glPointSize(10);
	glColor3f(1, 0, 0);
	for (auto data : g_mousePoints)
	{
		LOG(data.x, data.y);
		glBegin(GL_POINTS);
		glVertex2f(data.x, data.y);
		glEnd();
	}
	
	if (isSetting)
	{
		GLfloat ctrlpoints[4][3];
		for (int i = 0; i < g_mousePoints.size(); i++)
		{
			ctrlpoints[i][0] = g_mousePoints[i].x;
			ctrlpoints[i][1] = g_mousePoints[i].y;
			ctrlpoints[i][2] = 0;
		}
		

		// 곡선 제어점 설정: 매개변수 u의 최소값은 0, 최대값은 1,
		// 제어점간의 데이터 개수는 3, 제어점은 4개를 사용
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
		glEnable(GL_MAP1_VERTEX_3);
		// 제어점 사이의 곡선위의 점들을 계산한다. 제어점 사이를 10개로 나누어 그 점들을 연결한다.  곡선위의 점 계산
		glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔
		glEvalMesh1(GL_LINE, 0, 10); // 선분으로 나눈 부분 0~10까지 선으로 그림
		glDisable(GL_MAP1_VERTEX_3);
		// 제어점에 점을 그린다.
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 4; i++)
			glVertex3fv(&ctrlpoints[i][0]);
		glEnd();
	}
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
		glFrontFace(GL_CW);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
	glMatrixMode(GL_MODELVIEW);
	DrawLine();
	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}
int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
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
	//gluPerspective(60.0f, w / h, 1.0, 2000.0);
	//glTranslatef(0.0, 0.0, -700); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
								  // 2. 클리핑 공간 설정: 직각 투영인 경우
								  // glOrtho (0, 800.0, 0.0, 600.0, -1.0, 00.0);
								  // 모델 뷰 행렬 스택 재설정
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1000.0, 1000);
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
		x = x;//- (float)WINDOW_WIDTH / 2.0;
		y = (WINDOW_HEIGHT - y); //- (float)WINDOW_HEIGHT / 2.0;
		cout << x << " , " << y << endl;
		if (g_mousePoints.size()<4)
		{
			g_mousePoints.push_back({ float(x), float(y) });
			if (g_mousePoints.size() == 4)
			{
				isSetting = true;
			}
		}
		else
		{
			isSetting = false;
			g_mousePoints.clear();
			g_mousePoints.push_back({ float(x), float(y) });
		}
	}

}
void Motion(int x, int y)
{

}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		g_worldRotation.x += 10;
	}
	if (key == 'y')
	{
		g_worldRotation.y += 10;
	}
	if (key == 'z')
	{
		g_worldRotation.z += 10;
	}
	if (key == 'X')
	{
		g_worldRotation.x -= 10;
	}
	if (key == 'Y')
	{
		g_worldRotation.y -= 10;
	}
	if (key == 'Z')
	{
		g_worldRotation.z -= 10;
	}
	if (key == 'i')
	{
		glLoadIdentity();
		g_worldRotation = { 0,0,0 };
	}
	if (key == 'r' || key == 'R')
	{
		g_mousePoints.clear();
		isSetting = false;
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