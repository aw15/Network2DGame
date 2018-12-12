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
void Light();

Vector3 g_worldRotation = { 0,0,0 };//전체 죄표계 회전
Vector3 g_moving = { -400,0,0 };
int g_mousePoint[2][2];
bool g_isClick = false;



const int COL = 3;
const int ROW = 3;

int col = 0;
int row = 0;
int index = 0;
int x = 0;
int y = 0;


float alpha1[9] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
float alpha2[9] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
float alpha3[9] = { 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25 };

int mode = 0;

void fontRender(string str, int x, int y)
{
	glRasterPos2f(x, y);
	glColor3f(0, 1, 0);
	int len = str.length();

	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
}

void WorldRender()//-300~300 까지 최대
{
	
	glLoadIdentity();
	

	glEnable(GL_BLEND);


	for (int x = 0; x < COL; ++x)
	{
		for (int y = 0; y < ROW; ++y)
		{
			int i = y * COL + x;


			switch (i)
			{
			case 0: glBlendFunc(GL_ONE, GL_ZERO);
				break;
			case 1: glBlendFunc(GL_ZERO, GL_ONE);
				break;
			case 2: glBlendFunc(GL_ONE, GL_ONE);
				break;
			case 3: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			case 4: glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				break;
			case 5: glBlendFunc(GL_ZERO, GL_SRC_COLOR);
				break;
			case 6: glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
				break;
			case 7: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
				break;
			case 8: glBlendFunc(GL_ONE, GL_ONE);
				break;
			}



			glPushMatrix();
			{
				glTranslatef(x * 200 + 100, y * 200 + 120, -50);
				glColor4f(0, 0, 1, alpha1[i]);
				glutSolidSphere(50, 150, 150);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(x * 200 + 70, y * 200 + 120, 0);
				glRotatef(180, 0, 0, 1);
				glRotatef(180, 0, 1, 0);
				glColor4f(1, 0, 1, alpha2[i]);
				glutSolidTeapot(50);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(x * 200 + 140, y * 200 + 110, -70);
				glRotatef(90, 1, 0, 0);
				glColor4f(0, 1, 0, alpha3[i]);
				glutSolidCone(50, 50, 100, 100);
			}
			glPopMatrix();
		}
	}


	glDisable(GL_BLEND);

	glColor4f(0, 1, 0, 1);
	glTranslatef(0, 0, 40);
	fontRender("<GL_ONE, GL_ZERO>", 15, 200);
	fontRender("<GL_ZERO, GL_ONE>", 235, 200);
	fontRender("<GL_ONE, GL_ONE>", 435, 200);
	fontRender("<GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA>", 0, 400);
	fontRender("<GL_SRC_ALPHA, GL_ONE>", 255, 400);
	fontRender("<GL_ZERO, GL_SRC_COLOR>", 435, 400);
	fontRender("<GL_ONE_MINUS_DST_COLOR, GL_ZERO>", 0, 600);
	fontRender("<GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR>", 225, 600);
	fontRender("<GL_ONE, GL_ONE>", 445, 600);


	glPushMatrix();
	{
		glTranslatef(0, 0, -99);
		glColor3f(0, 0, 0);
		glRectd(col * 200 + 10, row * 200 + 10, col * 200 + 200 - 10, row * 200 + 200 - 10);
		glColor3f(1, 1, 1);
		glRectd(col * 200, row * 200, col * 200 + 200, row * 200 + 200);
	}
	glPopMatrix();
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
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. 
	// . 클리핑 공간 설정: 원근 투영인 경우 
	//gluPerspective(60.0f, w / h, 1.0, 2000.0);
	//glOrtho (-500, 500,-500, 500.0, -1000.0, 1000.0);
	glOrtho(0, 700, 700, 0, -100, 100);
	//glTranslatef(0.0, 0.0, -1000); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
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

void Keyboard(unsigned char key, int keyx, int keyy)
{
	
	if (key == 'I')
	{
		glLoadIdentity();
		g_worldRotation = { 0,0,0 };
	}
	if (key == 'q')
	{
		exit(1);
	}

	if (key == 'a')
	{
		alpha1[index] += 0.1;
		alpha1[index] = fminf(1, alpha1[index]);
	}

	if (key == 'A')
	{
		alpha1[index] -= 0.1;
		alpha1[index] = fmaxf(0.1, alpha1[index]);
	}

	if (key == 's')
	{
		alpha2[index] += 0.1;
		alpha2[index] = fminf(1, alpha2[index]);
	}

	if (key == 'S')
	{
		alpha2[index] -= 0.1;
		alpha2[index] = fmaxf(0.1, alpha2[index]);
	}

	if (key == 'd')
	{
		alpha3[index] += 0.1;
		alpha3[index] = fminf(1, alpha3[index]);
	}

	if (key == 'D')
	{
		alpha3[index] -= 0.1;
		alpha3[index] = fmaxf(0.1, alpha3[index]);
	}

	if (key == 'j')
	{
		x += -1;
		cout << col << endl;
		x = fmaxf(0, x);
		index = x + (y * 3);
		col = x;
		row = y;
	}
	if (key == 'l')
	{
		x += 1;
		x = fminf(2, x);
		index = x + (y * 3);
		col = x;
		row = y;
	}
	if (key == 'k')
	{
		y += 1;
		y = fminf(2, y);
		index = x + (y*3);
		col = x;
		row = y;

	}
	if (key == 'i')
	{
		y += -1;
		y = fmaxf(0, y);
		index = x + (y*3);
		col = x;
		row = y;
	}
	cout << index << " " << col << " " << row << endl;
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
//
//
//class Game : public Adun
//{
//private:
//	Window* window;
//
//	const int COL = 3;
//	const int ROW = 3;
//
//	int col = 0;
//	int row = 0;
//	int index = 0;
//
//	float alpha1[9] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
//	float alpha2[9] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
//	float alpha3[9] = { 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25 };
//
//public:
//	~Game()
//	{
//	};
//
//	void init() override
//	{
//
//		window = createWindow("AdunGL Test Game", 600, 600);
//		Camera camera = Camera::instance();
//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_BLEND);
//		//glEnable (GL_CULL_FACE);
//	}
//
//	void tick() override
//	{
//		if (Window::isKeyPressed("right"))
//		{
//			index++;
//			if (index == 9)
//				index = 0;
//			col = index % COL;
//			row = index / ROW;
//		}
//	}
//
//	void update() override // frame마다 실행
//	{
//
//		cout << index << endl;
//
//		if (Window::isKeyPressed('q'))
//			exit(1);
//
//		if (Window::isKeyPressed('a'))
//		{
//			alpha1[index] += 0.1;
//			alpha1[index] = fminf(1, alpha1[index]);
//		}
//
//		if (Window::isKeyPressed('A'))
//		{
//			alpha1[index] -= 0.1;
//			alpha1[index] = fmaxf(0.1, alpha1[index]);
//		}
//
//		if (Window::isKeyPressed('s'))
//		{
//			alpha2[index] += 0.1;
//			alpha2[index] = fminf(1, alpha2[index]);
//		}
//
//		if (Window::isKeyPressed('S'))
//		{
//			alpha2[index] -= 0.1;
//			alpha2[index] = fmaxf(0.1, alpha2[index]);
//		}
//
//		if (Window::isKeyPressed('d'))
//		{
//			alpha3[index] += 0.1;
//			alpha3[index] = fminf(1, alpha3[index]);
//		}
//
//		if (Window::isKeyPressed('D'))
//		{
//			alpha3[index] -= 0.1;
//			alpha3[index] = fmaxf(0.1, alpha3[index]);
//		}
//
//		glutPostRedisplay();
//
//	}
//
//
//	void render() override
//	{
//		glLoadIdentity();
//		glOrtho(0, window->getWidth(), window->getHeight(), 0, -100, 100);
//
//		glEnable(GL_BLEND);
//
//
//		for (int x = 0; x < COL; ++x)
//		{
//			for (int y = 0; y < ROW; ++y)
//			{
//				int i = y * COL + x;
//
//
//				switch (i)
//				{
//				case 0: glBlendFunc(GL_ONE, GL_ZERO);
//					break;
//				case 1: glBlendFunc(GL_ZERO, GL_ONE);
//					break;
//				case 2: glBlendFunc(GL_ONE, GL_ONE);
//					break;
//				case 3: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//					break;
//				case 4: glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//					break;
//				case 5: glBlendFunc(GL_ZERO, GL_SRC_COLOR);
//					break;
//				case 6: glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
//					break;
//				case 7: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
//					break;
//				case 8: glBlendFunc(GL_ONE, GL_ONE);
//					break;
//
//				}
//
//
//				glPushMatrix();
//				{
//					glTranslatef(x * 200 + 100, y * 200 + 120, -50);
//					glColor4f(0, 0, 1, alpha1[i]);
//					glutSolidSphere(50, 150, 150);
//				}
//				glPopMatrix();
//
//				glPushMatrix();
//				{
//					glTranslatef(x * 200 + 70, y * 200 + 120, 0);
//					glRotatef(180, 0, 0, 1);
//					glRotatef(180, 0, 1, 0);
//					glColor4f(1, 0, 1, alpha2[i]);
//					glutSolidTeapot(50);
//				}
//				glPopMatrix();
//
//				glPushMatrix();
//				{
//					glTranslatef(x * 200 + 140, y * 200 + 110, -70);
//					glRotatef(90, 1, 0, 0);
//					glColor4f(0, 1, 0, alpha3[i]);
//					glutSolidCone(50, 50, 100, 100);
//				}
//				glPopMatrix();
//			}
//		}
//
//
//		glDisable(GL_BLEND);
//
//		glColor4f(0, 1, 0, 1);
//		glTranslatef(0, 0, 40);
//		fontRender("<GL_ONE, GL_ZERO>", 15, 200);
//		fontRender("<GL_ZERO, GL_ONE>", 235, 200);
//		fontRender("<GL_ONE, GL_ONE>", 435, 200);
//		fontRender("<GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA>", 0, 400);
//		fontRender("<GL_SRC_ALPHA, GL_ONE>", 255, 400);
//		fontRender("<GL_ZERO, GL_SRC_COLOR>", 435, 400);
//		fontRender("<GL_ONE_MINUS_DST_COLOR, GL_ZERO>", 0, 600);
//		fontRender("<GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR>", 225, 600);
//		fontRender("<GL_ONE, GL_ONE>", 445, 600);
//
//
//		glPushMatrix();
//		{
//			glTranslatef(0, 0, -99);
//			glColor3f(0, 0, 0);
//			glRectd(col * 200 + 10, row * 200 + 10, col * 200 + 200 - 10, row * 200 + 200 - 10);
//			glColor3f(1, 1, 1);
//			glRectd(col * 200, row * 200, col * 200 + 200, row * 200 + 200);
//		}
//		glPopMatrix();
//	}
//
//
//	void fontRender(string str, int x, int y)
//	{
//		glRasterPos2f(x, y);
//		glColor3f(0, 1, 0);
//		int len = str.length();
//
//		for (int i = 0; i < len; i++)
//			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
//	}
//};
//
//
//int main()
//{
//	Game game;
//
//	game.start();
//
//
//	return 1;
//}