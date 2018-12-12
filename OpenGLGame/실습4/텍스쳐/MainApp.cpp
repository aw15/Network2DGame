// 실습25.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//


#include "stdafx.h"




GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecialKey(int key, int x, int y);
void MenuFunc(int button);
void Motion(int x, int y);
//---------custom function
void Initialize();
void WorldRotation();
void Initialize();

Vector3 g_worldRotation = { 0,0,0 };//전체 죄표계 회전
Vector3 g_moving = { -400,0,0 };
bool culling = false, depth = false, shading = false, upAnimation = false, frontAnimation = false;
int g_mousePoint[2][2];
bool g_isClick=false;





void Initialize()
{
	
}

int moonRotation = 0;
int earthRotation = 0;
Vector3 verticies[5] =
{
	{ -100.0, -100.0, -100.0 },
	{ -100.0, -100.0, 100.0 },
	{ 100.0, -100.0, 100.0 },
	{ 100.0, -100.0, -100.0 },
	{ 0.0,100.0, 0.0 }
};
void Triangle()
{
	glShadeModel(GL_SMOOTH);
	glColor3f(0, 1, 0.3);
	glPushMatrix();
		glBegin(GL_POLYGON);
		//-----关-----
		glNormal3f(0, 1, 0);
		for (int i = 0; i < 4; i++)
		{
			glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
		}
		glEnd();
		glBegin(GL_TRIANGLES);
		//----哭率------
		glNormal3f(0, 1, 0);
		for (int i = 0; i < 2; i++)
		{
			glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
		}
		glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
		//----坷弗率-----
		glNormal3f(0, 1, 0);
		for (int i = 0; i < 2; i++)
		{
			glVertex3f(verticies[i + 2].x, verticies[i + 2].y, verticies[i + 2].z);
		}
		glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
		////---缔率------
		glNormal3f(0, 1, 0);
		for (int i = 0; i < 2; i++)
		{
			glVertex3f(verticies[(i + 3) % 4].x, verticies[(i + 3) % 4].y, verticies[(i + 3) % 4].z);
		}
		glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
		////------------菊率------------------
		glNormal3f(0, 1, 0);
		for (int i = 0; i < 2; i++)
		{
			glVertex3f(verticies[i + 1].x, verticies[i + 1].y, verticies[i + 1].z);
		}
		glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
		glEnd();
	//행성 공전--------------------------------------
		glPushMatrix();
		glColor3f(0, 1, 0.2);
		glRotatef(earthRotation, 0, 1, 0);
		earthRotation += 5;
		glTranslatef(0, 0, -150.0f);
		glutSolidSphere(30, 20, 20);
			glPushMatrix();
				glRotatef(moonRotation, 0, 1, 0);
				moonRotation += 10;
				glTranslatef(0, 0, -70.0f);
				glutSolidSphere(20, 20, 20);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void WorldRender()//-300~300 까지 최대
{
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0, -100, 0);
		glScalef(7, 0.5, 7);
		glutSolidCube(100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-200.0f, 0, 0);
	Triangle();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(200.0f, 0, 0);
	Triangle();
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


void MainGame()
{
	Light();
	WorldRender();
	
}
GLvoid drawScene(GLvoid)
{
	GLfloat ambientLignt[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glEnable(GL_LIGHTING);
	/*glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLignt);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);*/

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);



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
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
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
void Render(int Planet)
{
	switch (Planet)
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

