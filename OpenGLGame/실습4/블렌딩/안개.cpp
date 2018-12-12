#include"stdafx.h"


GLvoid drawScene(GLvoid);
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

Vector3 g_worldRotation = { 0,0,0 };//전체 죄표계 회전
Vector3 g_moving = { -400,0,0 };
int g_mousePoint[2][2];
bool g_isClick = false;



GLfloat g_density = 0.7;
GLfloat g_start = -55.0;
GLfloat g_end = 100.0;
GLfloat g_fog_color[4] = { 0.1, 0.1, 0.1, 1.0 };
int mode = 0;


void WorldRender()//-300~300 까지 최대
{
	
	switch (mode)
	{
	case 0:
		glFogf(GL_FOG_MODE, GL_LINEAR);
		break;
	case 1:
		glFogf(GL_FOG_MODE, GL_EXP);
		break;
	case 2:
		glFogf(GL_FOG_MODE, GL_EXP2);
		break;
	}
	glFogfv(GL_FOG_COLOR, g_fog_color); // fog_color는 안개의 색을 의미한다.
	glFogf(GL_FOG_START, g_start); // start는 world coordinate상에서 안개 시작 위치를 의미한다.
	glFogf(GL_FOG_END, g_end); // end는 world coordinate상에서 안개 끝 위치를 의미한다.
	glFogf(GL_FOG_DENSITY, g_density); // fog mode가 GL_EXP, GL_EXP2일 경우 밀도의 설정이 가능
	cout << g_density << endl;

	glPushMatrix();
	glRotatef(-50, 0, 1, 0);
	glPushMatrix();
	glTranslatef(100, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	glColor3f(0, 0, 1);
	glutSolidCube(100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, 0, 0);
	glColor3f(1, 0, 0);
	glutSolidCube(100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-55, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 1, 0);
	glutSolidCube(100);
	glPopMatrix();
	glPopMatrix();
}


void Light()
{

	GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명
	GLfloat lightPos[] = { -350.0f, 50.0f, -350.0f, 1.0 }; // 위치: (1, 2, 3)

														   // 조명 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	GLfloat lightPos1[] = { -350.0, 50.0f, 350.0, 1.0 }; // 위치: (1, 2, 3)

														 // 조명 설정
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glEnable(GL_LIGHT1);

	GLfloat lightPos2[] = { 350.0, 50.0f, -350.0, 1.0 }; // 위치: (1, 2, 3)

														 // 조명 설정
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glEnable(GL_LIGHT2);

	GLfloat lightPos3[] = { 350.0, 50.0f, 350.0, 1.0 }; // 위치: (1, 2, 3)

														// 조명 설정
	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
	glEnable(GL_LIGHT3);


}

void Text()
{
	char *string = "string sample";
	glRasterPos2f(0, 0); // 문자 출력할 위치 설정
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
}

void MainGame()
{
	//Light();
	//Text();
	WorldRender();

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
	if (key == 'd')
	{
		g_density -= 0.01;
	}
	if (key == 'D')
	{
		g_density += 0.01;
	}
	if (key == 's')
	{
		g_start -= 10;
	}
	if (key == 'S')
	{
		g_start += 10;
	}
	if (key == 'e')
	{
		g_end -= 10;
	}
	if (key == 'E')
	{
		g_end += 10;
	}
	if (key == 'm')
	{
		mode = (mode + 1) % 3;
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
	glEnable(GL_FOG);
	glEnable(GL_DEPTH_TEST);
}