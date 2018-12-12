#include <GL/glut.h>     // 또는 <GL/feeeglut.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "fmod.h"
//png

#include "texture.h"

//sound

#define SOUND_NUM 20

FMOD_SYSTEM *g_System;
FMOD_SOUND *g_Sound[SOUND_NUM];
FMOD_CHANNEL *g_Channel[SOUND_NUM];







#define STAR_NUM 50

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int, int, int);



//////////////////////////////////////////////////
void SetupRC();
void Draw_Background();
void Draw_Star();
void Draw_logo();
void Draw_Start();
void Draw_Howto();
void Draw_Select_Moon();

struct coordi {
	float x;
	float y;
	float z;

	float size;
	float alpha_c = 0;
	float alpha_sign = 1;
};

coordi star[STAR_NUM];
coordi move_star;

int select_count = 0;
char ch = 0;

#define MUSIC_NUM 20



Texture *T[8];

/////////////////////////////////////////////



void main(int argc, char** argv)
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);


	//////////////////////////////////////////
	SetupRC();





	//////////////////////////////////////////
	glutInitWindowPosition(100, 100);

	glutCreateWindow("start");
	T[0] = new Texture("logo", "logo_1.png");
	T[1] = new Texture("start", "gamestart_white.png");
	T[2] = new Texture("howto", "howto_white2.png");
	T[3] = new Texture("moon", "crescent-moon.png");
	//////////////////////////////////////////////

	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]);

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutSpecialFunc(SpecialKeyboard); // <-추가
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
void SetupRC()
{

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


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
float RGB_c(float num)  //RGB값 -> glcolor형태로 변환
{
	num = num / 255;

	return num;
}
GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();



	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0f, 1, 1.0, 1200.0);  //이걸 두번째 값인 aspect를 바꿔보자 나중에 다 풀고나서
	glTranslatef(0.0, 0.0, -700.0); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]);
		break;
	case '2':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
		break;
	case '3':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]);
		break;
	case '4':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]);
		break;
	case '5':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]);
		break;
	case '6':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[7], 0, &g_Channel[7]);
		break;
	case '7':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[8], 0, &g_Channel[8]);
		break;
	case '8':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[9], 0, &g_Channel[9]);
		break;
	case '9':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[10], 0, &g_Channel[10]);
		break;
	case '0':
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[11], 0, &g_Channel[11]);
		break;
	}

}
void SpecialKeyboard(int key, int x, int y)
{

}

void Release()
{
	for (int i = 0; i < MUSIC_NUM; i++) {
		FMOD_Sound_Release(g_Sound[i]);
	}
	// 나중에 sound_Release에 추가
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void TimerFunction(int value)
{
	////////////////////////////////////

	//sound 볼륨


	////////////////////////////////////////



	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
