// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include"InputClass.h"
#include"Collision.h"

int g_shape = WIRE_SPHERE;
bool light1On = true;
bool light2On = true;

Transform g_direction[4]{
	{ 0,0,0 },
	{ 1,0,0 },
	{ 0,1,0 },
	{ 0,0,-1 }
};


GLdouble rotateMatrix_XAxis[16] = {
	1.0 ,0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};
GLdouble rotateMatrix_YAxis[16] = {
	1.0 ,0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};
GLdouble rotateMatrix_ZAxis[16] = {
	1.0 ,0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
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

Collision g_collision;//물리엔진

int g_Menu;
//--------------------------------------------------------------------
Object g_Ball;
Object g_Floor;
Object g_Bottom;
Object g_Middle;
Object g_Top;
//----------------------------------------------------------------------

MousePosition g_mousePosList[2];
int saveAmount = 2;



Transform g_collider[5];
int g_rotation = ROTATION_NONE;
int g_ballRotation = ROTATION_NONE;
Transform g_WorldDegree = { 0,0,0 };

float g_parameter[5] = {0,0,1,0,1};

float controllPoint[4] = {-1.0f,-1.0f,-1.0f,-1.0f};


Transform ambient = {0.1f,0.1f,0.1f};
Transform diffuse = { 0.1f,0.1f,0.1f };
Transform specular = { 0.1f,0.1f,0.1f };

void Light()
{
	GLfloat AmbientLight[] = {	ambient.x, ambient.y, ambient.z, 1.0f }; // 백색조명
	GLfloat DiffuseLight[] = { diffuse.x, diffuse.y, diffuse.z, 1.0f }; // 적색조명
	GLfloat SpecularLight[] = { specular.x, specular.y, specular.z, 1.0 }; // 백색조명
	GLfloat lightPos[] = { -10.0, 0.0, 0.0, 1.0 }; // 위치: (1, 2, 3)

	// 조명 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	if (light1On)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);


	GLfloat AmbientLight2[] = { ambient.x, ambient.y, ambient.z, 1.0f }; // 백색조명
	GLfloat DiffuseLight2[] = { diffuse.x, diffuse.y, diffuse.z, 1.0f }; // 적색조명
	GLfloat SpecularLight2[] = { specular.x, specular.y, specular.z, 1.0 }; // 백색조명
	GLfloat lightPos2[] = { -10.0, 0.0, 0.0, 1.0 }; // 위치: (1, 2, 3)

	// 조명 설정
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	if (light2On)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
}


void Base()
{
	
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -1, 0);
	glScalef(6, 0.5, 6);
	glutSolidCube(1);
	glPopMatrix();

}
bool g_Ballstop = false;
Transform previous;

int moonRotation = 0;
int earthRotation = 0;

void Triangle()
{
	Transform verticies[5] =
	{
		{ -1.0, -1.0, -1.0 },
		{ -1.0, -1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ 1.0, -1.0, -1.0 },
		{ 0.0,1.0, 0.0 }
	};
	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	//-----关-----
	glColor3f(1, 0, 0);
	glNormal3f(0, 1, 0);
	for (int i = 0; i < 4; i++)
	{
		glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
	}
	glEnd();
	glBegin(GL_TRIANGLES);
	//----哭率------
	glColor3f(0, 1, 0.3);
	glNormal3f(0, 1, 0);
	for (int i = 0; i < 2; i++)
	{
		glVertex3f(verticies[i].x, verticies[i].y, verticies[i].z);
	}
	glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
	//----坷弗率------
	glColor3f(0, 0.5, 1);
	glNormal3f(0, 1, 0);
	for (int i = 0; i < 2; i++)
	{
		glVertex3f(verticies[i + 2].x, verticies[i + 2].y, verticies[i + 2].z);
	}
	glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
	////---缔率------
	glColor3f(1, 0, 1);
	glNormal3f(0, 1, 0);
	for (int i = 0; i < 2; i++)
	{
		glVertex3f(verticies[(i + 3) % 4].x, verticies[(i + 3) % 4].y, verticies[(i + 3) % 4].z);
	}
	glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
	////------------菊率------------------
	glColor3f(1, 0.5, 0.3);
	glNormal3f(0, 1, 0);
	for (int i = 0; i < 2; i++)
	{
		glVertex3f(verticies[i + 1].x, verticies[i + 1].y, verticies[i + 1].z);
	}
	glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
	glEnd();
	glPushMatrix();
	glColor3f(0, 1, 0.2);
	glRotatef(earthRotation, 0, 1, 0);
	earthRotation += 5;
	glTranslatef(0, 0, -1.5f);
	glutSolidSphere(0.3, 20, 20);
		glPushMatrix();
		glRotatef(moonRotation, 0, 1, 0);
		moonRotation += 10;
		glTranslatef(0, 0, -0.7f);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Ball()
{
	if (-2.2>g_Ball.position.x&&-2.2>g_Ball.position.z)
	{
		g_Ball.position = previous;
	}
	if (-2.2>g_Ball.position.x&&2.2<g_Ball.position.z)
	{
		g_Ball.position = previous;
	}
	if (2.2<g_Ball.position.x&&-2.2>g_Ball.position.z)
	{
		g_Ball.position = previous;
	}
	if (2.2<g_Ball.position.x&&2.2<g_Ball.position.z)
	{
		g_Ball.position = previous;
	}
	if (-2<g_Ball.position.x&&0.7>g_Ball.position.x&&-0.5<g_Ball.position.z&&0.5>g_Ball.position.z)
	{
		g_Ball.position = previous;
	}
	if (g_Bottom.position.x-1.f<g_Ball.position.x&&g_Bottom.position.x + 1.f>g_Ball.position.x&&g_Bottom.position.z - 0.8f<g_Ball.position.z&&g_Bottom.position.z + 0.8f>g_Ball.position.z)
	{
		g_Ball.position = previous;
	}


	glPushMatrix();
	glColor3f(1, 0, 0);
	if (g_Ball.position.x < -3)
	{
		g_Ball.position.x = -3;
	}
	if (g_Ball.position.z < -3)
	{
		g_Ball.position.z = -3;
	}
	if (g_Ball.position.x > 3)
	{
		g_Ball.position.x = 3;
	}
	if (g_Ball.position.z > 3)
	{
		g_Ball.position.z = 3;
	}
	previous = g_Ball.position;
	glTranslatef(g_Ball.position.x, g_Ball.position.y, g_Ball.position.z);
	switch (g_ballRotation)
	{
		rotateMatrix_ZAxis[0] = cos(g_Ball.rotation.z);
		rotateMatrix_ZAxis[1] = sin(g_Ball.rotation.z);
		rotateMatrix_ZAxis[4] = -sin(g_Ball.rotation.z);
		rotateMatrix_ZAxis[5] = cos(g_Ball.rotation.z);

		rotateMatrix_XAxis[5] = cos(g_Ball.rotation.x);
		rotateMatrix_XAxis[6] = sin(g_Ball.rotation.x);
		rotateMatrix_XAxis[9] = -sin(g_Ball.rotation.x);
		rotateMatrix_XAxis[10] = cos(g_Ball.rotation.x);

		rotateMatrix_YAxis[0] = cos(g_Ball.rotation.y);
		rotateMatrix_YAxis[2] = -sin(g_Ball.rotation.y);
		rotateMatrix_YAxis[8] = sin(g_Ball.rotation.y);
		rotateMatrix_YAxis[10] = cos(g_Ball.rotation.y);

	case Z_AXIS:
		glMultMatrixd(rotateMatrix_ZAxis);
		break;
	case X_AXIS:
		glMultMatrixd(rotateMatrix_XAxis);
		break;
	case Y_AXIS:
		glMultMatrixd(rotateMatrix_YAxis);
		break;
	}
	glutWireSphere(g_Ball.size,15,15);
	glPopMatrix();
	rotateMatrix_ZAxis[0] = 1;
	rotateMatrix_ZAxis[1] = 0;
	rotateMatrix_ZAxis[4] = 0;
	rotateMatrix_ZAxis[5] = 1;

	rotateMatrix_XAxis[5] = 1;
	rotateMatrix_XAxis[6] = 0;
	rotateMatrix_XAxis[9] = 0;
	rotateMatrix_XAxis[10] = 1;

	rotateMatrix_YAxis[0] = 1;
	rotateMatrix_YAxis[2] = 0;
	rotateMatrix_YAxis[8] = 0;
	rotateMatrix_YAxis[10] =1;
}
Transform crane_previous;
void Crane()
{

	if (-2.2>g_Bottom.position.x&&-2.2>g_Bottom.position.z)
	{
		g_Bottom.position = crane_previous;
	}
	if (-2.2>g_Bottom.position.x&&2.2<g_Bottom.position.z)
	{
		g_Bottom.position = crane_previous;
	}
	if (2.2<g_Bottom.position.x&&-2.2>g_Bottom.position.z)
	{
		g_Ball.position = crane_previous;
	}
	if (2.2<g_Bottom.position.x&&2.2<g_Bottom.position.z)
	{
		g_Bottom.position = crane_previous;
	}
	if (-2<g_Bottom.position.x&&0.7>g_Bottom.position.x&&-0.5<g_Bottom.position.z&&0.5>g_Bottom.position.z)
	{
		g_Bottom.position = crane_previous;
	}
	if (g_Bottom.position.x - 1.f<g_Ball.position.x&&g_Bottom.position.x + 1.f>g_Ball.position.x&&g_Bottom.position.z - 0.8f<g_Ball.position.z&&g_Bottom.position.z + 0.8f>g_Ball.position.z)
	{
		g_Bottom.position = crane_previous;
	}
	if (g_Bottom.position.x < -2)
	{
		g_Bottom.position.x = -2;
	}
	if (g_Bottom.position.z < -2.5)
	{
		g_Bottom.position.z = -2.5;
	}
	if (g_Bottom.position.x > 2)
	{
		g_Bottom.position.x = 2;
	}
	if (g_Bottom.position.z > 2.5)
	{
		g_Bottom.position.z = 2.5;
	}

	glPushMatrix();//맨밑에 부분
	glColor3f(1, 0.3, 0);
	crane_previous = g_Bottom.position;
	glTranslatef(g_Bottom.position.x, g_Bottom.position.y, g_Bottom.position.z);

	glScalef(g_Bottom.scale.x, g_Bottom.scale.y, g_Bottom.scale.z);
	glRotatef(g_Bottom.rotation.y, 0, 1, 0);
	glutSolidCube(g_Bottom.size);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(g_Bottom.position.x, 0, 0);
	glRotatef(g_Bottom.rotation.y, 0, 1, 0);
	glRotatef(g_Middle.rotation.x, 1, 0, 0);
	glTranslatef(0, g_Middle.position.y, g_Bottom.position.z);
	glRotatef(g_Middle.rotation.y, 0, 1, 0);
	glScalef(g_Middle.scale.x, g_Middle.scale.y, g_Middle.scale.z);
	glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(g_Bottom.position.x, 0, 0);
	glRotatef(g_Bottom.rotation.y, 0, 1, 0);
	glRotatef(g_Middle.rotation.x, 1, 0, 0);
	glTranslatef(0, g_Middle.position.y, g_Bottom.position.z);
	glRotatef(g_Middle.rotation.y, 0, 1, 0);
	glTranslatef(0, 0.6f, 0);
	glRotatef(g_Top.rotation.x, 1, 0, 0);
	glRotatef(g_Top.rotation.z, 0, 0, 1);
	glTranslatef(0, g_Top.position.y - 0.6f, 0);
	glScalef(g_Top.scale.x, g_Top.scale.y, g_Top.scale.z);
	glutSolidCube(0.3);
	glPopMatrix();
}



void Tree()
{
	glPushMatrix();
	glColor3f(1, 0.4, 0);
	glTranslatef(2.8, -0.3, 2.8);
	g_collider[0] = { 2.8f, -0.3f, 2.8f };
	glScalef(1, 5, 1);
	Render(CUBE);
	glColor3f(0, 1, 0);
	glTranslatef(0., 0.23, 0);
	glScalef(3, 0.5, 1);
	glRotatef(g_parameter[0], 0, 1, 0);
	g_parameter[0] += 10;
	Render(WIRE_CUBE);
	glPopMatrix();
}
void Tree2()
{
	glPushMatrix();
	glColor3f(1, 0.4, 0);
	glTranslatef(-2.8, -0.3, 2.8);
	g_collider[1] = { -2.8f, -0.3f, 2.8f };
	glScalef(1, 5, 1);
	Render(CUBE);
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(0, 0.2, 0);
		glScalef(1+g_parameter[1], 0.2+ (g_parameter[1]*0.2), 1 + g_parameter[1]);
		g_parameter[1] += 0.1;
		if (g_parameter[1] >= 0.7)
			g_parameter[1] = 0;
		Render(WIRE_SPHERE);
		glPopMatrix();
	glPopMatrix();
}
void Tree3()
{
	static float y = 0;
	glPushMatrix();
	glColor3f(1, 0.4, 0);
	glTranslatef(-2.8, -0.3, -2.8);
	g_collider[2] = { -2.8f, -0.3f, -2.8f };
	glScalef(1, 5, 1);
	Render(CUBE);
		glPushMatrix();
		glColor3f(0, 1, 0);
		glScalef(1, 0.4, 1);
		glTranslatef(0, 0.5+y, 0);
		glRotatef(90, 1, 0, 0);
		y += g_parameter[2] * 0.1;
		if (y < -0.5)
			g_parameter[2] = 1;
		else if (y > 0)
			g_parameter[2] = -1;
		Render(WIRE_TORUS);
		glPopMatrix();
	glPopMatrix();
}
void Tree4()
{
	glPushMatrix();
	glColor3f(1, 0.4, 0);
	glTranslatef(2.8, -0.9, -2.8);
	g_collider[3] = { 2.8f, -0.9f, -2.8f };
	glRotatef(-90, 1, 0, 0);
	glScalef(1 + g_parameter[3], 1+g_parameter[3], 1 + g_parameter[3]);
	g_parameter[3] += 0.1;
	if (g_parameter[3] >= 1.5)
		g_parameter[3] = 0;
	Render(WIRE_CONE);
		glColor3f(0, 1, 0);
		glTranslatef(0, 0, 0.5);
		glRotatef(-180, 1, 0, 0);
		Render(WIRE_CONE);
	glPopMatrix();
}


void Door()
{
	static float x = 0;
	glPushMatrix();
	glColor3f(0, 0, 1);
	glScalef(5, 1, 1);
	glTranslatef(-0.1, 0.6, 0);
	g_collider[4] = { -0.1f, 0.6f, 0 };
	Render(CUBE);
		glPushMatrix();
			glTranslatef(0.1+x, -0.6, 0);
			glScalef(0.4, 5, 1);
			Render(CUBE);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.1+(x*-1), -0.6, 0);
			glScalef(0.4, 5, 1);
			Render(CUBE);
		glPopMatrix();
		x += g_parameter[4] * 0.01;
		if (x < -0.08)
			g_parameter[4] = 1;
		else if (x > 0)
			g_parameter[4] = -1;
	glPopMatrix();
}
float g_wingDegree = 0;
float g_planeDegree = 0;
int g_planeIndex = 0;
int g_planeDir = 0;
void AirPlane()
{
	glPushMatrix();
	float x = cos(ANGLE*g_planeIndex) * 3;
	float y = sin(ANGLE*g_planeIndex) * 3;
	glTranslatef(x, 3, y);
	
	glRotatef(g_planeDir, 0, 1, 0);


	glRotatef(g_planeDegree, 0, 0, 1);
	g_planeDir -= 1;
	g_planeIndex += 1;
		glPushMatrix();
			glColor3f(0, 1, 0);
			glScalef(1, 1, 5);
			glutSolidCube(0.5);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0, 1, 1);
			glTranslatef(0.5, 0, 0);
			glutSolidCube(0.5);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0, 1, 1);
			glTranslatef(-0.5, 0, 0);
			glutSolidCube(0.5);
		glPopMatrix();
		glPushMatrix();
		glRotatef(g_wingDegree, 0, 0, 1);
			glColor3f(1, 1, 1);
			glTranslatef(0,0,1.4);
			glRotatef(90, 0, 1, 0);
			glutSolidCone(0.1, 0.3, 20, 20);
			glRotatef(180, 0, 1, 0);
			glutSolidCone(0.1, 0.3, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glRotatef(g_wingDegree, 0, 0, 1);
			glTranslatef(0, 0, 1.4);
			glRotatef(90, 1, 0, 0);
			glRotatef(180, 0, 1, 0);
			glutSolidCone(0.1, 0.3, 20, 20);
			glRotatef(180, 0, 1, 0);
			glutSolidCone(0.1, 0.3, 20, 20);
		glPopMatrix();
		g_wingDegree += 10;
		glPushMatrix();
		glTranslatef(0, 0.5, -1);
		glutSolidCube(0.5);
		glPopMatrix();
	glPopMatrix();

}
GLvoid drawScene(GLvoid)
{
	GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	Light();
	//Test();
	glPushMatrix();
	glRotatef(g_WorldDegree.x, 1, 0, 0);
	glRotatef(g_WorldDegree.y, 0, 1, 0);
	glRotatef(g_WorldDegree.z, 0, 0, 1);


	Base();
	AirPlane();
	Tree();
	Tree2();
	Tree3();
	Tree4();
	Triangle();
	//Door();
	//Crane();
	//Ball();
	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}
int main()
{
	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT,&MenuFunc);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	g_Floor.position = { 0,-1,0 };
	g_Floor.scale = { 30,1,30 };
	g_Floor.size = 0.2f;

	g_Ball.position = { 1,-0.45f,0 };
	g_Ball.size = 0.5f;

	g_Bottom.position = { -1,-0.45f,1 };
	g_Bottom.scale = { 3,1,2 };
	g_Bottom.size = 0.5f;

	g_Middle.position = { 0,0.3f,1 };
	g_Middle.scale = { 1,2,1 };

	g_Top.position = { 0,0.8f,1 };
	g_Top.scale = { 1,2,1 };

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
	gluPerspective(60.0f, w / h,1.0, 1000.0);
	glTranslatef(0.0, 0.0, -10); //투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
									// 2. 클리핑 공간 설정: 직각 투영인 경우
									// glOrtho (0, 800.0, 0.0, 600.0, -1.0, 00.0);
									// 모델 뷰 행렬 스택 재설정 
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

		cout << inputX << " " << inputY <<  "mouseregist" << endl;
		
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
		g_rotation = Z_AXIS;
		g_WorldDegree.z += -10;
	}
	if (key == '+')
	{
		glTranslatef(0, 0, 1);
	}
	if (key == '-')
	{
		glTranslatef(0, 0, -1);
	}
	if (key == '1')
	{
		light1On == true ? light1On = false : light1On = true;
		cout << light1On << endl;
	}
	if (key == '2')
	{
		light2On == true ? light2On = false : light2On = true;
	}
	if (key == 'A')
	{
		ambient.x += 0.1f;
		ambient.y += 0.1f;
		ambient.z += 0.1f;
	}
	if (key == 'a')
	{
		ambient.x -= 0.1f;
		ambient.y -= 0.1f;
		ambient.z -= 0.1f;
	}
	if (key == 'D')
	{
		diffuse.x += 0.1f;
		diffuse.y += 0.1f;
		diffuse.z += 0.1f;
	}
	if (key == 'd')
	{
		diffuse.x -= 0.1f;
		diffuse.y -= 0.1f;
		diffuse.z -= 0.1f;
	}
	if (key == 'S')
	{
		specular.x += 0.1f;
		specular.y += 0.1f;
		specular.z += 0.1f;
	}
	if (key == 's')
	{
		specular.x -= 0.1f;
		specular.y -= 0.1f;
		specular.z -= 0.1f;
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
	case 1:
		g_shape = WIRE_SPHERE;
		break;
	case 2:
		g_shape = SPHERE;
		break;
	}
	glutPostRedisplay();
}
void Render(int shape)
{
	switch (shape)
	{
	case WIRE_TORUS:
		glutWireTorus(0.1, 0.3, 20, 20);
		break;
	case CUBE:
		glutSolidCube(0.3);
		break;
	case WIRE_CUBE:
		glutWireCube(0.3);
		break;
	case CONE:
		glutSolidCone(0.3,0.3,20,20);
		break;
	case WIRE_CONE:
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
	glutAddMenuEntry("1controll", 1);
	glutAddMenuEntry("2controll", 2);
	glutAddMenuEntry("3controll", 3);
	// 마우스의 오른쪽버튼에 메뉴를 연결합니다.
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}