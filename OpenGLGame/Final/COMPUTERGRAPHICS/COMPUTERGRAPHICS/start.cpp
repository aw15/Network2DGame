

//png
#include "texture.h"
#include"Stage.h"

 //sound


FMOD_SYSTEM *g_System;
FMOD_SOUND *g_Sound[SOUND_NUM];
FMOD_CHANNEL *g_Channel[SOUND_NUM];


#define STAR_NUM 60
#define STAR3_NUM 500
coordi star3[STAR3_NUM];
float starColor[STAR3_NUM][3];


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int,int, int);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
///////////////////////////////////////////////////////////
//전체 회전
void WorldRotation();
GLvoid Light();
float xValue = 0;
float yValue = 0;
Vector3 g_worldRotation = { 0,0,0 };//전체 죄표계 회전
Vector3 g_worldPosition = { 0,0,0 };

int g_mousePoint[2][2];
bool g_isClick = false;
Stage stageManager;
bool open = false;
//////////////////////////////////////////////////
void SetupRC();
//시작화면
void Draw_Start_Background();
void Draw_Star();
void Draw_logo();
void Draw_Start();
void Draw_Howto();
void Draw_Select_Moon();
void Draw_Howto_image();
void DrawClear();
//스테이지
void Draw_stage1(); 
void Draw_stage2();
void Draw_stage3();
void Draw_stage4();
void Draw_stage5();
void Draw_stage6();
void Draw_stage7();
void Draw_stage8();
//하트 이펙트
void Draw_Heart(int);
//눈 이펙트
void Draw_Snow(int);
//별 이펙트
void Draw_Star2();
//별 2
void Christmas()
{
	for (int i = 0; i < STAR3_NUM; i++)
	{
		if (i % 31 == 0)
		{
			starColor[i][0] = rand() % 255 + 1;
			starColor[i][1] = rand() % 255 + 1;
			starColor[i][2] = rand() % 255 + 1;

			glColor3f(RGB_c(starColor[i][0]), RGB_c(starColor[i][1]), RGB_c(starColor[i][2]));
			glPointSize(5);
			glBegin(GL_POINTS);
			glVertex3f(star3[i].x, star3[i].y, 0);
			glEnd();
		}
		if (i % 23 == 0)
		{
			starColor[i][0] = rand() % 255 + 1;
			starColor[i][1] = rand() % 255 + 1;
			starColor[i][2] = rand() % 255 + 1;

			glColor3f(RGB_c(starColor[i][0]), RGB_c(starColor[i][1]), RGB_c(starColor[i][2]));
			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex3f(star3[i].x, star3[i].y, 0);
			glEnd();
		}
		if (i % 11 == 0)
		{
			starColor[i][0] = rand() % 255 + 1;
			starColor[i][1] = rand() % 255 + 1;
			starColor[i][2] = rand() % 255 + 1;

			glColor3f(RGB_c(starColor[i][0]), RGB_c(starColor[i][1]), RGB_c(starColor[i][2]));
			glPointSize(3);
			glBegin(GL_POINTS);
			glVertex3f(star3[i].x, star3[i].y, 0);
			glEnd();
		}
	}
}



//배경
void Draw_Background1();
void Draw_Background2();
void Draw_Background3();
void Draw_Background4();
void Draw_Background5();
void Draw_Background6();
void Draw_Background7();
void Draw_Background8();
//스테이지
void DrawStage_1();
void DrawStage_2();
void DrawStage_3();
void DrawStage_4();
void DrawStage_5();
void DrawStage_6();
void DrawStage_7();
void DrawStage_8();


coordi star[STAR_NUM]; 
coordi move_star;

int select_count = 0;
char ch = 0;

Texture *T[20];

bool howto_on = false;

//heart
#define HEART_NUM 20
coordi Heart[HEART_NUM];

//눈
#define SNOW_NUM 40
coordi Snow[SNOW_NUM];
//나뭇잎
void Draw_Leaf(int);
#define LEAF_NUM 20
coordi Leaf[LEAF_NUM];
/////////////////////////////////////////////
coordi star2[STAR_NUM];

clock_t totalTime=0;
clock_t prevTime= 0 ;

void main(int argc, char** argv)    
{   
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);    


	//////////////////////////////////////////
	for (int i = 0; i < STAR3_NUM; i++) //start 좌표값
	{
		star3[i].x = (rand() % 200 - 100) * 5;
		star3[i].y = rand() % 1000 - 500;
	}
	//////////////////////////////////////////
	glutInitWindowPosition(100, 100);   
	
	glutCreateWindow("start");   
	T[0] = new Texture("logo","logo_1.png");
	T[1] = new Texture("start", "gamestart_white.png");
	T[2] = new Texture("howto", "howto_white.png");
	T[3] = new Texture("moon", "crescent-moon.png");
	T[4] = new Texture("snow", "snowflake.png");
	T[5] = new Texture("heart1", "heart.png");
	T[6] = new Texture("howto_image", "howto.png");
	T[7] = new Texture("stage1", "stage1.png");
	T[8] = new Texture("stage2", "stage2.png");
	T[9] = new Texture("stage3", "stage3.png");
	T[10] = new Texture("stage4", "stage4.png");
	T[11] = new Texture("stage5", "stage5.png");
	T[12] = new Texture("stage6", "stage6.png");
	T[13] = new Texture("stage7", "stage7.png");
	T[14] = new Texture("stage8", "stage8.png");
	T[15] = new Texture("clover", "clover.png");
	T[16] = new Texture("clear", "clear.png");
	//////////////////////////////////////////////
	//7~14 스테이지 띄우기////////////////////////
	////////////////////////////////////////////////
	SetupRC();

	glutDisplayFunc(drawScene);   
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutSpecialFunc(SpecialKeyboard); // <-추가
	glutReshapeFunc(Reshape);  
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutMainLoop();    
}
void SetupRC() 
{

	for (int i = 0; i < STAR_NUM; i++) {
		star2[i].x = rand() % 1000 - 550;
		star2[i].y = rand() % 800 - 300;//별 좌표값
		star2[i].size = (rand() % 2 + 1);
		star2[i].alpha_c = rand() / 32768;
	}


	for (int i = 0; i < STAR_NUM; i++) {
		star[i].x = rand() % 1000 - 550;
		star[i].y = rand() % 800 - 100;//별 좌표값
		star[i].size = (rand() % 2 + 1);
		star[i].alpha_c = rand()/32768 ;
	}

	for (int i = 0; i < LEAF_NUM; i++) {
		Leaf[i].x = (rand() % 300 - 200) * 5;
		Leaf[i].y = rand() % 400 + 300;
		Leaf[i].size = rand() % 30 + 20;
		Leaf[i].speed = rand() % 4 + 2;
	}

	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_DEPTH_TEST);


	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 10, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(g_System, "BGM.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[0]);
	FMOD_System_CreateSound(g_System, "select_sound.wav", FMOD_DEFAULT, 0, &g_Sound[1]);
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
	FMOD_System_CreateSound(g_System, "wrong_sound.wav", FMOD_DEFAULT, 0, &g_Sound[12]);
	FMOD_System_CreateSound(g_System, "stage_change.mp3", FMOD_DEFAULT, 0, &g_Sound[13]);
	//stage_change.mp3
	//FMOD_System_CreateSound(~~~로 피아노 소리 추가
	stageManager.g_System = g_System;
	stageManager.g_Sound = g_Sound;
	stageManager.g_Channel = g_Channel;


	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]);


	//하트
	for (int i = 0; i < HEART_NUM; i++) {
		Heart[i].x = (rand() % 300 - 200) * 5;
		Heart[i].y = rand() % 400 + 300;
		Heart[i].size = rand() % 30 + 20;
		Heart[i].speed = rand() % 4 + 2;
	}
	//눈
	for (int i = 0; i < SNOW_NUM; i++) {
		Snow[i].x = (rand() % 300 - 200) * 5;
		Snow[i].y = rand() % 400 + 300;
		Snow[i].size = rand() % 20 + 10;
		Snow[i].speed = rand() % 4 + 2;
	}


}



void MainLoop()
{

	glPushMatrix();
	WorldRotation();//전체 좌표계 회전
	if(stageManager.lose)
	{
		static int count = 0;
		static int dir = 1;

		glTranslatef(g_worldPosition.x, g_worldPosition.y, g_worldPosition.z);
		g_worldPosition.x += dir*5;
		if (g_worldPosition.x > 20)
		{
			dir *= -1;
			count++;
		}
		else if (g_worldPosition.x < -20)
		{
			dir *= -1;
			count++;
		}
		if (count > 2)
		{
			stageManager.lose = false;
			count = 0;
		}
	}
	stageManager.Render();
	stageManager.Update();
	glPopMatrix();

	if (stageManager.activeStageNumber == 4 || stageManager.activeStageNumber == 8)
	{
		for (int i = 0; i < SNOW_NUM; i++) {
			Draw_Snow(i);
		}
	}
	else if (stageManager.activeStageNumber == 6)
	{
		for (int i = 0; i < HEART_NUM; i++) {
			Draw_Heart(i);
		}
	}
	else if (stageManager.activeStageNumber == 5)
	{
		for (int i = 0; i < LEAF_NUM; i++) {
			Draw_Leaf(i);
		}
	}
	else if (stageManager.activeStageNumber == 3)
	{
		Draw_Star2();
	}
	else if (stageManager.activeStageNumber == 7|| stageManager.activeStageNumber == 2)
	{
		Christmas();
	}
	if (stageManager.win)
	{
		g_worldRotation = { 0,0,0 };
		clock_t currentTime = clock()/CLOCKS_PER_SEC;
		totalTime += (currentTime - prevTime);
		prevTime = currentTime;
		switch (stageManager.activeStageNumber)
		{
		case 1:
			DrawStage_1();
			break;
		case 2:
			DrawStage_2();
			break;
		case 3:
			DrawStage_3();
			break;
		case 4:
			DrawStage_4();
			break;
		case 5:
			DrawStage_5();
			break;
		case 6:
			DrawStage_6();
			break;
		case 7:
			DrawStage_7();
			break;
		case 8:
			DrawStage_8();
			break;
		}
		if (totalTime>2)
		{
			stageManager.win = false;
			totalTime = 0;
		}
	}
}

float RGB_c(float num)  //RGB값 -> glcolor형태로 변환
{
	num = num / 255;

	return num;
}
GLvoid drawScene()   
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	if (stageManager.clear)
	{
		Draw_Start_Background();
		DrawClear();
	}
	else
	{
		if (open)
		{
			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_BLEND);
			Light();

			MainLoop();

		}
		//////////////////
		//초기화면
		else if (!open)
		{
			Draw_Start_Background();
			Draw_Star();
			Draw_logo();
			Draw_Start();
			Draw_Howto();
			Draw_Select_Moon();
			Draw_Howto_image();
		}
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0f, 1, 1.0, 2000.0);  //이걸 두번째 값인 aspect를 바꿔보자 나중에 다 풀고나서
	glTranslatef(0.0, 0.0, -1000.0); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0, 1, 0);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	stageManager.HandleEvent(key);
	if (key == 'q')
	{
		stageManager.clear = false;
		open = false;
	}
	if (key == 'n')
	{
		g_worldRotation = { 0,0,0 };
		totalTime = 0;
	}
	if (key == 'm')
	{
		g_worldRotation = { 0,0,0 };
		totalTime = 0;
	}
	if (key == 'i')
	{
		glLoadIdentity();
		g_worldRotation = { 0,0,0 };
	}

	if (!open)
	{
		if (key == ' ') {
			if (select_count % 2 == 0) {
				open = true;
				stageManager.win = true;
				stageManager.SetStage(1);
			}
			else if (select_count % 2 == 1) {
				howto_on = true;
			}
		}
	}
	
}
void SpecialKeyboard(int key, int x, int y) 
{ 
	if (key == GLUT_KEY_UP || key ==GLUT_KEY_DOWN || key==GLUT_KEY_RIGHT ||key ==GLUT_KEY_LEFT) {
		select_count++;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]);
		if (howto_on) {
			howto_on = false;
		}
		
	}

}

void Release()
{
	FMOD_Sound_Release(g_Sound[0]);
	FMOD_Sound_Release(g_Sound[1]);
	// 나중에 sound_Release에 추가
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void TimerFunction(int value)
{
	for (int i = 0; i < STAR_NUM; i++) {
		star2[i].alpha_c += 0.005*star2[i].alpha_sign;
		if (star2[i].alpha_c > 0.7) {
			star2[i].alpha_sign = -1;
		}
		else if (star2[i].alpha_c < 0) {
			star2[i].alpha_sign = 1;
		}
	}
	//별똥별값 증가
	/*move_star.x -= 2;
	move_star.y -= 2;*/
	////////////////////////////////////
	for (int i = 0; i < STAR_NUM; i++) {
		star[i].alpha_c += 0.005*star[i].alpha_sign;
		if (star[i].alpha_c > 0.1) {
			star[i].alpha_sign = -1;
		}
		else if (star[i].alpha_c < 0) {
			star[i].alpha_sign = 1;
		}
	}
	//별똥별값 증가
	move_star.x -= 2;
	move_star.y -= 2;

	//sound 볼륨

	FMOD_Channel_SetVolume(g_Channel[0], 0.3);
	FMOD_Channel_SetVolume(g_Channel[1], 0.9);




	//하트
	for (int i = 0; i < HEART_NUM; i++) {
		Heart[i].y -= 2 * Heart[i].speed;
		if (Heart[i].y <= -200) {
			Heart[i].y = 500;
		}
	}
	//눈
	for (int i = 0; i < SNOW_NUM; i++) {
		Snow[i].y -= 2 * Snow[i].speed;
		if (Snow[i].y <= -200) {
			Snow[i].y = 500;
		}
	}
	//나뭇잎
	for (int i = 0; i < LEAF_NUM; i++) {
		Leaf[i].y -= 2 * Leaf[i].speed;
		if (Leaf[i].y <= -200) {
			Leaf[i].y = 500;
		}
	}
	////////////////////////////////////////
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}

void Draw_Star2() {

	for (int i = 0; i < STAR_NUM; i++) {

		glPushMatrix();
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	

		//작은 별

		
		glTranslatef(star2[i].x, star2[i].y, 3);
		glColor4f(RGB_c(244), RGB_c(234), RGB_c(125), star2[i].alpha_c);
		glutSolidSphere(star2[i].size, 20, 20);
		glDisable(GL_BLEND);
		glPopMatrix();

	}
}

void Draw_Leaf(int i) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);

	T[15]->bind();
	glBegin(GL_QUADS); {
		glTexCoord2f(1, 1);
		glVertex3f(Leaf[i].x + Leaf[i].size / 1.5, Leaf[i].y + Leaf[i].size, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(Leaf[i].x, Leaf[i].y + Leaf[i].size, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(Leaf[i].x, Leaf[i].y, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(Leaf[i].x + Leaf[i].size / 1.5, Leaf[i].y, 0.0f);
	}
	glEnd();
	T[15]->unbind();
}

void Draw_Start_Background() {
	
	glBegin(GL_QUADS);
	glColor3f(RGB_c(74), RGB_c(11), RGB_c(163));
	glVertex3f(700.0, 700.0, -100.0);//1
	glColor3f(RGB_c(74), RGB_c(11), RGB_c(163));
	glVertex3f(-700.0, 700.0, -100.0);//2
	glColor3f(RGB_c(146), RGB_c(83), RGB_c(235));
	glVertex3f(-700.0, -700.0, -100.0);//3
	glColor3f(RGB_c(146), RGB_c(83), RGB_c(235));
	glVertex3f(700.0, -700.0, -100.0);//4
	glEnd();

}

void Draw_Star() {

	for (int i = 0; i < STAR_NUM; i++) {
		//별똥별
		if (i % 5==3) {
			glPushMatrix();
			glTranslatef(move_star.x, move_star.y, 0);
			glEnable(GL_BLEND);
			glPushMatrix();
			glTranslatef(star[i].x, star[i].y, 200);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor4f(RGB_c(255), RGB_c(178), RGB_c(217), star[i].alpha_c);
			glutSolidSphere(star[i].size * 2, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);

			//작은 별

			glPushMatrix();
			glTranslatef(star[i].x, star[i].y, 0);
			glColor4f(RGB_c(243), RGB_c(97), RGB_c(220), 1.0f);
			glutSolidSphere(star[i].size, 20, 20);
			glPopMatrix();
			glPopMatrix();
		}
		//고정된 별
		else {
			glEnable(GL_BLEND);
			glPushMatrix();
			glTranslatef(star[i].x, star[i].y, 0);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor4f(RGB_c(255), RGB_c(178), RGB_c(217), star[i].alpha_c);
			glutSolidSphere(star[i].size * 3, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);

			//작은 별

			glPushMatrix();
			glTranslatef(star[i].x, star[i].y, 0);
			glColor4f(RGB_c(243), RGB_c(97), RGB_c(220), 1.0f);
			glutSolidSphere(star[i].size, 20, 20);
			glPopMatrix();
		}
	}
	
} 
void Draw_logo() {

	
	if (howto_on == false) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		T[0]->bind();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1, 1);
			glVertex3f(320.0, 170.0, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-320.0, 170.0, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-320.0, -40.0, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(320.0, -40.0, 50.0f);
		}
		glEnd();
		T[0]->unbind();

	}

}
void Draw_Start() {
	if (howto_on == false) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		T[1]->bind();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1, 1);
			glVertex3f(-250.0, -200.0, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-450.0, -200.0, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-450.0, -300.0, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-250.0, -300.0, 50.0f);
		}
		glEnd();
		T[1]->unbind();
	}
}
void Draw_Howto() {
	if (howto_on == false) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		T[2]->bind();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1, 1);
			glVertex3f(-250.0, -350.0, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-450.0, -350.0, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-450.0, -450.0, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-250.0, -450.0, 50.0f);
		}
		glEnd();
		T[2]->unbind();
	}
}
void Draw_Select_Moon() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1 ,1.0);
	T[3]->bind();
	if (select_count % 2 == 0) {
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1, 1);
			glVertex3f(-190.0, -220.0, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-230.0, -220.0, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-230.0, -270.0, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-190.0, -270.0, 50.0f);
			printf("%d", select_count);
		}glEnd();
	}
	else if (select_count % 2 == 1) {
		glBegin(GL_QUADS); {
			glTexCoord2f(1, 1);
			glVertex3f(-190.0, -350.0, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-230.0, -350.0, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-230.0, -400.0, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-190.0, -400.0, 50.0f);
		}
		glEnd();
	}

	T[3]->unbind();
}
void Draw_Howto_image() {
	if (howto_on) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1, 1, 1, 1.0);
		T[6]->bind();

			glBegin(GL_QUADS);
			{
				glTexCoord2f(1, 1);
				glVertex3f(450.0, 300.0, 50.0f);
				glTexCoord2f(0, 1);
				glVertex3f(-450.0, 300.0, 50.0f);
				glTexCoord2f(0, 0);
				glVertex3f(-450.0, -300.0, 50.0f);
				glTexCoord2f(1, 0);
				glVertex3f(450.0, -300.0, 50.0f);

			}glEnd();
		


		T[6]->unbind();
	}
}
void Draw_stage1(){

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[7]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 500.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 500.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 500.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 500.0f);
	}
	glEnd();
	T[7]->unbind();

}
void Draw_stage2() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[8]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 50.0f);
	}
	glEnd();
	T[8]->unbind();

}
void Draw_stage3() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[9]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 50.0f);
	}
	glEnd();
	T[9]->unbind();

}
void Draw_stage4() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[10]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 50.0f);
	}
	glEnd();
	T[10]->unbind();

}
void Draw_stage5() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[11]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 50.0f);
	}
	glEnd();
	T[11]->unbind();

}
void Draw_stage6() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[12]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 50.0f);
	}
	glEnd();
	T[12]->unbind();

}
void Draw_stage7() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[13]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 50.0f);
	}
	glEnd();
	T[13]->unbind();

}
void Draw_stage8() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	T[14]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(90.0, 480.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-90.0, 480.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-90.0, 410.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(90.0, 410.0, 50.0f);
	}
	glEnd();
	T[14]->unbind();

}
void Draw_Heart(int i) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);

	T[5]->bind();
	glBegin(GL_QUADS); {
		glTexCoord2f(1, 1);
		glVertex3f(Heart[i].x + Heart[i].size / 1.5, Heart[i].y + Heart[i].size, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(Heart[i].x, Heart[i].y + Heart[i].size, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(Heart[i].x, Heart[i].y, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(Heart[i].x + Heart[i].size / 1.5, Heart[i].y, 50.0f);
	}
	glEnd();
	T[5]->unbind();
}
void Draw_Snow(int i) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(RGB_c(178), RGB_c(235), RGB_c(244), 1.0);
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
	// 조명 설정
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,spotPos );
	glEnable(GL_LIGHT1);
}
void DrawStage_1() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[7]->bind();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1, 1);
			glVertex3f(100.0, 100.0, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-100.0, 100.0, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-100.0, -100.0, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(100.0, -100.0, 50.0f);
		}glEnd();
	T[7]->unbind();
}
void DrawStage_2() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[8]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(100.0, 100.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-100.0, 100.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-100.0, -100.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(100.0, -100.0, 50.0f);
	}glEnd();
	T[8]->unbind();
}
void DrawStage_3() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[9]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(100.0, 100.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-100.0, 100.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-100.0, -100.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(100.0, -100.0, 50.0f);
	}glEnd();
	T[9]->unbind();
}
void DrawStage_4() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[10]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(70.0, 70.0, 550.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-70.0, 70.0, 550.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-70.0, -70.0, 550.0f);
		glTexCoord2f(1, 0);
		glVertex3f(70.0, -70.0, 550.0f);
	}glEnd();
	T[10]->unbind();
}



void DrawStage_5() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[11]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(100.0, 100.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-100.0, 100.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-100.0, -100.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(100.0, -100.0, 50.0f);
	}glEnd();
	T[11]->unbind();
}
void DrawStage_6() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[12]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(100.0, 100.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-100.0, 100.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-100.0, -100.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(100.0, -100.0, 50.0f);
	}glEnd();
	T[12]->unbind();
}
void DrawStage_7() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[13]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(100.0, 100.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-100.0, 100.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-100.0, -100.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(100.0, -100.0, 50.0f);
	}glEnd();
	T[13]->unbind();
}
void DrawStage_8() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1.0);
	T[14]->bind();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(100.0, 100.0, 50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-100.0, 100.0, 50.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-100.0, -100.0, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f(100.0, -100.0, 50.0f);
	}glEnd();
	T[14]->unbind();
}



void DrawClear() {


	if (howto_on == false) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		T[16]->bind();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1, 1);
			glVertex3f(320.0, 170.0, 50.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-320.0, 170.0, 50.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-320.0, -40.0, 50.0f);
			glTexCoord2f(1, 0);
			glVertex3f(320.0, -40.0, 50.0f);
		}
		glEnd();
		T[16]->unbind();

	}

}