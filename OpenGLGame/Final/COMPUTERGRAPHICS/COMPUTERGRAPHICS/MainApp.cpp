// 실습25.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include"Pyramid.h"
#include"Stage.h"
#include"texture.h"



#define STAR_NUM 50


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecialKey(int key, int x, int y);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
//---------custom function
GLvoid Light();
void Initialize();
void WorldRotation();
void Initialize();

Vector3 g_worldRotation = { 0,0,0 };//전체 죄표계 회전

int g_mousePoint[2][2];
bool g_isClick = false;
float xValue=0;
float yValue=0;
//----------------------------사운드--------------------------------
#define SOUND_NUM 20

FMOD_SYSTEM *g_System;
FMOD_SOUND *g_Sound[SOUND_NUM];
FMOD_CHANNEL *g_Channel[SOUND_NUM];
//----------------------------------------------------------------------

coordi star[STAR_NUM];
coordi move_star;

int select_count = 0;
Stage stageManager;


void SetupRC();
void Draw_Snow(int);

#define SNOW_NUM 40
Texture *T[8];
coordi Snow[SNOW_NUM];



void SetupRC()
{

	for (int i = 0; i < SNOW_NUM; i++) {
		Snow[i].x = (rand() % 156 - 70) * 5;
		Snow[i].y = rand() % 200 + 400;
		Snow[i].size = rand() % 20 + 10;
		Snow[i].speed = rand() % 4 + 2;
	}

	for (int i = 0; i < STAR_NUM; i++) {
		star[i].x = rand() % 780 - 350;
		star[i].y = rand() % 400 - 50;//별 좌표값
		star[i].size = (rand() % 2 + 1);
		star[i].alpha_c = rand() / 32768;
	}
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 10, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(g_System, "BGM.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[0]);
	FMOD_System_CreateSound(g_System, "select_sound.wav", FMOD_DEFAULT, 0, &g_Sound[1]);
	/////////////////
	FMOD_System_CreateSound(g_System, "a1.wav", FMOD_DEFAULT, 0, &g_Sound[2]);
	FMOD_System_CreateSound(g_System, "a1s.wav", FMOD_DEFAULT, 0, &g_Sound[3]);
	FMOD_System_CreateSound(g_System, "b1.wav", FMOD_DEFAULT, 0, &g_Sound[4]);
	FMOD_System_CreateSound(g_System, "c2.wav", FMOD_DEFAULT, 0, &g_Sound[5]);
	FMOD_System_CreateSound(g_System, "d1.wav", FMOD_DEFAULT, 0, &g_Sound[6]);
	FMOD_System_CreateSound(g_System, "e1.wav", FMOD_DEFAULT, 0, &g_Sound[7]);
	FMOD_System_CreateSound(g_System, "f1.wav", FMOD_DEFAULT, 0, &g_Sound[8]);
	FMOD_System_CreateSound(g_System, "f1s.wav", FMOD_DEFAULT, 0, &g_Sound[9]);
	FMOD_System_CreateSound(g_System, "g1.wav", FMOD_DEFAULT, 0, &g_Sound[10]);
	FMOD_System_CreateSound(g_System, "g1s.wav", FMOD_DEFAULT, 0, &g_Sound[11]);
	//
	//FMOD_System_CreateSound(~~~로 피아노 소리 추가

}


void Release()
{
	for (int i = 0; i <SOUND_NUM; i++) {
		FMOD_Sound_Release(g_Sound[i]);
	}
	// 나중에 sound_Release에 추가
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void Initialize()
{
	
	glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	stageManager.SetStage(1);
	SetupRC();
}
void ShakeScreen()
{
	
	

}

void MainLoop()
{
	glPushMatrix();
	WorldRotation();//전체 좌표계 회전
	stageManager.Update();
	stageManager.Render();
	glPopMatrix();
}



GLvoid drawScene(GLvoid)
{
	static bool opening = false;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기
	glMatrixMode(GL_MODELVIEW);
	Light();


	//MainLoop();

	glutSwapBuffers(); // 화면에 출력하기
}
int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 30); // 윈도우의 위치지정 
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 
	T[4] = new Texture("snow", "snowflake.png");
	Initialize();


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutSpecialFunc(KeyboardSpecialKey);
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
	stageManager.HandleEvent(key);

	
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
		yValue = (g_mousePoint[0][0] - g_mousePoint[1][0])*0.05;
		xValue = (g_mousePoint[0][1] - g_mousePoint[1][1])*-0.05;
		g_worldRotation.x -= xValue;
		g_worldRotation.y -= yValue;
	}
	glRotatef(g_worldRotation.x, 1, 0, 0);
	glRotatef(g_worldRotation.y, 0, 1, 0);
	glRotatef(g_worldRotation.z, 0, 0, 1);
}

GLvoid Light()
{
	GLfloat AmbientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // 
	GLfloat DiffuseLight[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // 적색조명
	GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명
	GLfloat lightPos[] = { -100.0, 250.0, 300.0, 1.0 }; // 위치: (1, 2, 3)

														//GLfloat spotPos[] = { 0.0, 0.0, 0.0, 1.0 };

														// 조명을 사용하도록 설정
	glEnable(GL_LIGHTING);
	// 조명 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,spotPos );
	glEnable(GL_LIGHT0);

	GLfloat lightPos1[] = { 0.0, 0.0, -300.0, 1.0 }; // 위치: (1, 2, 3)

													 //GLfloat spotPos[] = { 0.0, 0.0, 0.0, 1.0 };

													 // 조명을 사용하도록 설정
	glEnable(GL_LIGHTING);
	// 조명 설정
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,spotPos );
	glEnable(GL_LIGHT1);
}

void Draw_Snow(int i) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1, 0.7);
	T[4]->bind();
	glBegin(GL_QUADS); {
		glTexCoord2f(1, 1);
		glVertex3f(Snow[i].x + Snow[i].size, Snow[i].y + Snow[i].size, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(Snow[i].x, Snow[i].y + Snow[i].size, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(Snow[i].x, Snow[i].y, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(Snow[i].x + Snow[i].size, Snow[i].y, 50.0f);
	}
	glEnd();
	T[4]->unbind();

}