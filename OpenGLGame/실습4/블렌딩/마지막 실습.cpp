#include"stdafx.h"


GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecialKey(int key, int x, int y);
void Motion(int x, int y);
//---------custom function
void Initialize();
void WorldRotation();
void Initialize();
void wavebottom();
GLvoid drawScene(GLvoid);

Vector3 g_worldRotation = { 0,0,0 };//전체 죄표계 회전
Vector3 g_moving = { -400,0,0 };
int g_mousePoint[2][2];
bool g_isClick = false;


GLfloat pyramid[4][3] = { { -100.0, -100.0, -100.0 },
{ 100.0, -100.0, -100.0 },
{ 0.0, -100.0,  73.2 },
{ 0.0,  100.0, -13.4 } };


double colors[1000] = { 0 };
int iterations = 0;
double zoom = 0;

int tick1 = 0;
int c = -1;

int xangle = 0;
int yangle = 0;
int zangle = 0;
int wheelangle = 0;


void WorldRender()//-300~300 까지 최대
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, -250, 0);
	glScalef(1, 0.1, 1);
	glutSolidCube(800);
	glPopMatrix();
}


void wavebottom()
{

	glPushMatrix(); // 연못 시작
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(200, -100, 200);
	GLfloat ctrlpoints[3][3][3] = { { { -100.0, -100, 100.0 },{ 0.0 + tick1, 0.0  , 100.0 },{ 100.0, -100.0 , 100.0 } },
	{ { -100.0, -100.0 , 0.0 },{ 0.0 + tick1, 0.0 , 0.0 },{ 100.0, -100.0 , 0.0 } },
	{ { -100.0, -100.0 , -100.0 },{ 0.0 + tick1, 0.0  , -100.0 },{ 100.0, -100.0 , -100.0 } } };
	// 곡면 제어점 설정
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);
	glPointSize(2.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints[i][j]);
	glEnd();
	glPushMatrix();   // 연못 주변1 시작
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(-100, -100, 0);
	glScalef(0.5, 0.5, 5.0);
	glutSolidCube(50);
	glPopMatrix();   // 연못 주변1 끝
	glPushMatrix();   // 연못 주변2 시작
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(100, -100, 0);
	glScalef(0.5, 0.5, 5.0);
	glutSolidCube(50);
	glPopMatrix();   // 연못 주변2 끝
	glPopMatrix(); // 연못 끝

}

void Diamond()
{
	static int big_y = 0;
	static int small_y = 0;
	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		glColor4f(1, 1, 0,0.1);
		glTranslatef(-300, -100, -300);
		glRotatef(big_y, 0, 1, 0);
		glRotatef(45, 0, 0, 1);
		big_y += 10;
		glutSolidCube(100);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glTranslatef(-300, -100, -300);
		glRotatef(small_y, 0, 1, 0);
		small_y -= 10;
		glRotatef(45, 0, 0, 1);
		glutSolidCube(50);
	}
	glPopMatrix();
}


void drawPyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d) {

	// bottom
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	//en este caso los vértices están dados en el sentido de las manecillas del reloj
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(d);
	glEnd();
	glColor3f(1, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void dividePyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int iteraciones) {
	GLfloat v[6][3];
	int j;
	if (iteraciones > 0) {
		//encontrar los puntos medios de cada arista del triángulo
		for (j = 0; j < 3; j++) {
			v[0][j] = (a[j] + b[j]) / 2;
		}
		for (j = 0; j < 3; j++) {
			v[1][j] = (a[j] + c[j]) / 2;
		}
		for (j = 0; j < 3; j++) {
			v[2][j] = (b[j] + c[j]) / 2;
		}
		for (j = 0; j < 3; j++) {
			v[3][j] = (a[j] + d[j]) / 2;
		}
		for (j = 0; j < 3; j++) {
			v[4][j] = (b[j] + d[j]) / 2;
		}
		for (j = 0; j < 3; j++) {
			v[5][j] = (c[j] + d[j]) / 2;
		}

		//por cada triángulo que entra, se crean 4 triángulos más pequeños y recursivamente estos se dividen a su vez
		dividePyramid(a, v[0], v[1], v[3], iteraciones - 1);
		dividePyramid(v[0], b, v[2], v[4], iteraciones - 1);
		dividePyramid(v[1], v[2], c, v[5], iteraciones - 1);
		dividePyramid(v[3], v[4], v[5], d, iteraciones - 1);
		// commenting this will create a Sierpinski Triangle
		//divideTriangle(v[0], v[1], v[2], iteraciones-1);

	}
	else {
		//dibujar el triángulo de la iteración 0
		drawPyramid(a, b, c, d);
	}
}


void SnowMan()
{
	glPushMatrix();
	{
		glTranslatef(0, -150, 0);
		glScalef(0.8, 0.8, 0.8);
		glColor3f(1, 1, 0);
		glutSolidSphere(50, 20, 20);
		glTranslatef(0, -100, 0);
		glScalef(1.3, 1.3, 1.3);
		glutSolidSphere(50, 20, 20);
	}
	glPopMatrix();
}

void Swing()
{
	static int angle=0;
	static int dir = 1;
	static int isFirst = 1;
	glPushMatrix();
	{
		
		glTranslatef(-200, 200, 0);
		glRotatef(angle, 0, 0, 1);
		if (isFirst == 1)
		{
			SnowMan();
		}
		glColor3f(1, 0, 0);
		glutSolidCube(20);
		glBegin(GL_LINES);
		{
			glVertex3f(0, 0, 0);
			glVertex3f(-70, -250, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(70, -250, 0);
		}
		glEnd();
		glColor3f(0, 0.3, 0.7);
		glTranslatef(0, -270, 0);
		glScalef(1.4, 0.3, 1.4);
		glutSolidCube(100);
	}
	glPopMatrix();
	glPushMatrix();
	{
		
		glTranslatef(200, 200, 0);
		glRotatef(-angle, 0, 0, 1);
		if (isFirst==2)
		{
			SnowMan();
		}
		glColor3f(1, 0, 0);
		glutSolidCube(20);
		glBegin(GL_LINES);
		{
			glVertex3f(0, 0, 0);
			glVertex3f(-70, -250, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(70, -250, 0);
		}
		glEnd();
		glColor3f(0, 0.3, 0.7);
		glTranslatef(0, -270, 0);
		glScalef(1.4, 0.3, 1.4);
		glutSolidCube(100);
	}
	glPopMatrix();
	angle += 10*dir;

	if (angle == 50)
	{
		dir *= -1;
		isFirst == 1 ? isFirst = 2 : isFirst = 1;
	}
	if (angle ==  -50)
	{
		dir *= -1;
	}
}

void FerrisWheel()
{
	glPushMatrix(); // 관람차 시작
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(200, 0, -200);
	glutSolidSphere(10, 10, 10);
	glPushMatrix();
	glRotatef(wheelangle, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(2.0, 2.0, 0.1);
	glutWireSphere(100, 10, 10);
	glPopMatrix();
	for (int i = 0; i < 10; ++i)
	{
		glPushMatrix();
		glRotatef(36 * i, 0.0, 0.0, 1.0);
		glTranslatef(0, 100, 0);
		glPushMatrix();
		glScalef(1.0, 8.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(20);
		glPopMatrix();
		glTranslatef(0, 120, 0);
		glColor3f(1.0, 1.0, 0.0);
		glutSolidCube(60);
		glPopMatrix();

	}
	glPopMatrix();
	glPopMatrix();
}



void MainGame()
{
	//Light();
	//Text();
	WorldRender();
	FerrisWheel();
	wavebottom();
	Diamond();
	Swing();
	glPushMatrix();
	glTranslatef(0, -100, 0);
	dividePyramid(pyramid[0], pyramid[1], pyramid[2], pyramid[3], int(iterations));
	glPopMatrix();
	iterations += 1;
	if (iterations > 5)
		iterations = 0;


}
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	WorldRotation();
	MainGame();
	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}


int main()
{
	srand((unsigned)time(NULL));
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
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	//glOrtho (-500, 500,-500, 500.0, -1000.0, 1000.0);
	glTranslatef(0.0, 0.0, -1000); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
								   // 2. 클리핑 공간 설정: 직각 투영인 경우
								   // 모델 뷰 행렬 스택 재설정 
								   //glOrtho(-500, 500, -500, 500, 0.0,1000 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0, 1, 0);
}

void TimerFunction(int value)
{

	wheelangle = (wheelangle + 5) % 360;

	if (tick1 >= 100)
		c *= -1;
	else if (tick1 <= -100)
		c *= -1;
	tick1 = (tick1 + 5 * c);

	glutPostRedisplay(); // 화면 재 출력, drawscene이 호출
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Mouse(int button, int state, int x, int y)//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
{
	float inputX, inputY;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x = x - (float)WINDOW_WIDTH / 2.0;
		y = (WINDOW_HEIGHT - y) - (float)WINDOW_HEIGHT / 2.0;
		//cout << x << " , " << y << endl;
		g_mousePoint[0][0] = x;
		g_mousePoint[0][1] = y;
		g_isClick = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		g_isClick = false;
	}

}
void Motion(int x, int y)
{
	x = x - (float)WINDOW_WIDTH / 2.0;
	y = (WINDOW_HEIGHT - y) - (float)WINDOW_HEIGHT / 2.0;
	g_mousePoint[1][0] = x;
	g_mousePoint[1][1] = y;
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'i')
	{
		glLoadIdentity();
		g_worldRotation = { 0,0,0 };
	}

}
void KeyboardSpecialKey(int key, int x, int y)
{
	//if (key == GLUT_KEY_F1)

}


void WorldRotation()
{
	if (g_isClick)
	{
		auto yValue = (g_mousePoint[0][0] - g_mousePoint[1][0])*0.05;
		auto xValue = (g_mousePoint[0][1] - g_mousePoint[1][1])*-0.05;
		g_worldRotation.x -= xValue;
		g_worldRotation.y -= yValue;
	}
	glRotatef(g_worldRotation.x, 1, 0, 0);
	glRotatef(g_worldRotation.y, 0, 1, 0);
	glRotatef(g_worldRotation.z, 0, 0, 1);
}
void Initialize()
{
	//GLfloat ambientLignt[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//glEnable(GL_LIGHTING);
	///*glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLignt);
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);*/

	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//glMateriali(GL_FRONT, GL_SHININESS, 128);
	glEnable(GL_DEPTH_TEST);
}