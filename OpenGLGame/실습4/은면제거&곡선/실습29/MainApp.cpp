// 실습25.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//


#include "stdafx.h"
#include"snow.h"
#pragma warning(disable:4996)

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
void Robot();

Vector3 g_worldRotation = { 0,0,0 };//전체 죄표계 회전
Vector3 g_moving = { -400,0,0 };
bool culling = false, depth = false, shading = false, upAnimation = false, frontAnimation = false;
int g_mousePoint[2][2];
bool g_isClick=false;
bool light_0 = true;
bool light_1 = true;
bool light_2 = true;
bool light_3 = true;
bool All_Light = true;
vector<snow*> snowList;
vector<snow*> particleList;
float currentTime;
float totalTime=0;
bool normalOn = true;
bool animation = false;

bool isMove = false;
bool isOpen = false;
bool isJump = false;
int legDegree = 0;
int armDegree = 0;
int dir = 1;
int jumpdir = 1;
Vector3 movingSpeed = { 0,0,0 };
Vector3 position = { 0,160,-100 };//robot
int robotRotation = 0;
GLuint texture_object[3];
BITMAPINFO *texture;
GLubyte * TexBits;


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}


void Initialize()
{
	srand(time(NULL));
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glGenTextures(3, texture_object);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	TexBits = LoadDIBitmap("Rune_Fire.bmp", &texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR_EXT,GL_UNSIGNED_BYTE, TexBits);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 나머지 n-1개의 텍스처에도 (1) ~ (4)까지의 과정을 짂행하여 텍스처를 설정한다.
	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 홗성화
	glEnable(GL_TEXTURE_2D);



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
	Vector3 side1, side2, result;
	glShadeModel(GL_SMOOTH);
	glColor3f(0, 1, 0.3);
	glPushMatrix();
		//glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		glBegin(GL_POLYGON);//0~3
		//-----关-----
		side1 = verticies[1] - verticies[0];
		side2 = verticies[2] - verticies[0];
		result = side1.Cross(side2);
		glNormal3f(result.x,result.y,result.z);
		for (int i = 0; i < 4; i++)
		{
			glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
		}
		glEnd();
		glBegin(GL_TRIANGLES);//0~1
		//----哭率------
		side1 = verticies[0] - verticies[4];
		side2 = verticies[1] - verticies[4];
		result = side1.Cross(side2);
		glNormal3f(result.x, result.y, result.z);
		for (int i = 0; i < 2; i++)
		{
			glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
		}
		glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
		//----坷弗率-----
		side1 = verticies[2] - verticies[4];
		side2 = verticies[3] - verticies[4];
		result = side1.Cross(side2);
		glNormal3f(result.x, result.y, result.z);
		for (int i = 0; i < 2; i++)
		{
			glVertex3f(verticies[i + 2].x, verticies[i + 2].y, verticies[i + 2].z);
		}
		glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
		////---缔率------
		side1 = verticies[3] - verticies[4];
		side2 = verticies[0] - verticies[4];
		result = side1.Cross(side2);
		glNormal3f(result.x, result.y, result.z);
		for (int i = 0; i < 2; i++)
		{
			glVertex3f(verticies[(i + 3) % 4].x, verticies[(i + 3) % 4].y, verticies[(i + 3) % 4].z);
		}
		glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
		////------------菊率------------------
		side1 = verticies[1] - verticies[4];
		side2 = verticies[2] - verticies[4];
		result = side1.Cross(side2);
		glNormal3f(result.x, result.y, result.z);
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
		glColor3f(0, 0, 0.3);
		glTranslatef(0, -100, 0);
		for (int i = -300; i <= 300; i += 10)
		{
			for (int j = 300; j >= -300; j -= 10)
			{
				glPushMatrix();
				glTranslated(i, 0, j);
				glutSolidCube(10);
				glPopMatrix();
			}
		}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0f, 0, 0);
	Triangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200.0f, 0, 0);
	Triangle();
	glPopMatrix();

	totalTime += clock() - currentTime;
	if (totalTime > 0.5f)
	{
		auto newSnow = new snow();
		snowList.push_back(newSnow);

		auto newParticle = new snow();
		newParticle->position = { position.x, position.y + 100, position.z };

		particleList.push_back(newParticle);
	}
}

GLfloat qaAmbientLight[] = { 1, 1, 1, 1.0 };
GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };
// Light source position
GLfloat qaLightPosition[] = {0 , 100, 0 , 1 };
GLfloat dirVector0[] = { position.x, -180, position.z, 0.0 };

Vector3 lightRotation = { 0,0,0 };
bool lightAnimation = false;
Vector3 lightPosition = { 0,0,0 };

float lightIntensity = 20;

void Light()
{

	glEnable(GL_LIGHT0);

	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	////////////////////////////////////////////////


	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightIntensity);// set cutoff angle
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirVector0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1); // set focusing strength

}



void MainGame()
{
	WorldRender();
	Robot();
	for (auto snow : snowList)
	{
		snow->Draw();
	}
	for (auto particle : particleList)
	{
		particle->Update();
	}
	glPopMatrix();
		GLfloat dirVector0[] = { position.x, -180, position.z, 0.0 };
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightIntensity);// set cutoff angle
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirVector0);
	glPopMatrix();
}
Vector3 cameraPosition = {0,0,0};
Vector3 cameraRotation = {0,0,0};
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기

	if (animation)
	{
		if (cameraPosition.z < 150)
		{
			glTranslated(0, 0, 10);
			cameraPosition.z += 10;
		}
		else if (cameraRotation.y < 1080)
		{
			glRotatef(10, 0, 1, 0);
			cameraRotation.y += 10;
		}
		else
		{
			lightAnimation = true;
			glTranslatef(0, 0, -cameraPosition.z);
			animation = false;
		}
	}
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0, 1, 0);


	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);

	
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
	Light();
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
		bool g_isClick = false;
		bool light_0 = true;
		bool light_1 = true;
		bool light_2 = true;
		bool light_3 = true;
		bool All_Light = true;
	}
	if (key == '1')
	{
		light_0 == true ? light_0 = false : light_0 = true;
	}
	if (key == '2')
	{
		light_1 == true ? light_1 = false : light_1 = true;
	}
	if (key == '3')
	{
		light_2 == true ? light_2 = false : light_2 = true;
	}
	if (key == '4')
	{
		light_3 == true ? light_3 = false : light_3 = true;
	}
	if (key == 'A')
	{
		All_Light = true;
	}
	if (key == 'a')
	{
		All_Light = false;
	}
	if (key == 'N')
	{
		normalOn = true;
	}
	if (key == 'n')
	{
		normalOn = false;
	}
	if (key == 'Y')
	{
		animation = true;
	}
	if (key == 'y')
	{
		animation = false;
	}
	if (key == 'w')
	{
		movingSpeed.x = 0;
		movingSpeed.z = -10;

		robotRotation = 180;
	}
	if (key == 's')
	{
		movingSpeed.x = 0;
		movingSpeed.z = 10;
		robotRotation = 0;
	}
	if (key == 'd')
	{
		movingSpeed.z = 0;
		movingSpeed.x = 10;
		robotRotation = 90;
	}
	if (key == 'a')
	{
		movingSpeed.z = 0;
		movingSpeed.x = -10;
		robotRotation = 270;
	}
	if (key == 'j')
	{
		isJump = true;
		jumpdir = 1;
	}
	if (key == ' ')
	{
		isMove == true ? isMove = false : isMove = true;
		if (!isMove)
		{
			legDegree = 0;
			armDegree = 0;
		}
	}
	if (key == '+')
	{
		lightIntensity += 10;
	}
	if (key == '-')
	{
		lightIntensity -= 10;
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

void Robot()
{
	glPushMatrix();
	if (isMove)
	{
		legDegree += (dir * 5);
		armDegree += (dir * 5);
		if (legDegree>40)
		{
			dir *= -1;
		}
		else if (legDegree < -40)
		{
			dir *= -1;
		}
		if (position.x <-300 && movingSpeed.x<0)
		{
			movingSpeed.x = 0;
		}
		if (position.x > 300 && movingSpeed.x>0)
		{
			movingSpeed.x = 0;
		}
		if (position.z <-170 && movingSpeed.z<0)
		{
			movingSpeed.z = 0;
		}
		if (position.z > 300 && movingSpeed.z>0)
		{
			movingSpeed.z = 0;
		}
		position.x += movingSpeed.x;
		position.z += movingSpeed.z;
	}

	if (isJump)
	{
		position.y += 10 * jumpdir;
		if (position.y > 300)
		{
			jumpdir *= -1;
		}
		if (position.y < 0)
		{
			isJump = false;
			position.y = 0;
		}
	}
	glTranslatef(position.x, position.y, position.z);
	glRotatef(robotRotation, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidCube(100);
	glPushMatrix();
	glTranslatef(0, -100, 0);
	glColor3f(1, 1, 0);
	glScalef(1, 1.5, 1);
	glutSolidCube(70);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 50);
	glColor3f(1, 0, 0);
	glutSolidCube(30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -35, 0);
	glRotatef(360 - armDegree, 1, 0, 0);
	glTranslatef(0, +35, 0);
	glTranslatef(50, -70, 0);
	glColor3f(1, 0, 0);
	glScalef(1, 3, 1);
	glutSolidCube(30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -35, 0);
	glRotatef(armDegree, 1, 0, 0);
	glTranslatef(0, +35, 0);
	glTranslatef(-50, -70, 0);
	glColor3f(0, 1, 0);
	glScalef(1, 3, 1);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -150, 0);
	glRotatef(legDegree, 1, 0, 0);
	glTranslatef(0, +150, 0);
	glTranslatef(-20, -200, 0);
	glColor3f(0, 0.7, 0.3);
	glScalef(1, 3, 1);
	glutSolidCube(30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -150, 0);
	glRotatef(360 - legDegree, 1, 0, 0);
	glTranslatef(0, +150, 0);
	glTranslatef(20, -200, 0);
	glColor3f(0.5, 0.3, 0);
	glScalef(1, 3, 1);
	glutSolidCube(30);
	glPopMatrix();
	glPopMatrix();
}