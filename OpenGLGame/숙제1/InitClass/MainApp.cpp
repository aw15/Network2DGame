// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OpenGLClass.h"
#include"Collision.h"

#define ORIGINALRECT_SPEED 0.02
#define BASCKET_SPEED 0.01

Transform g_direction[4]{
	{ 0,0,0 },
	{ 1,0,0 },
	{ 0,1,0 },
	{ 0,0,-1 }
};


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void MenuFunc(int button);
void Motion(int x, int y);
void Clipping(bool usingMouse = true);


Collision g_collision;//물리엔진

//---------------------------------원본네모-----------------------------
struct Object
{
	vector<Transform> verticies;
	Transform position = {0,0,0};
	double speed = 0;
	Transform dir = {1,1,1};
	int degree=0;
};
Object g_originalRect;
Object g_clippedRect;
Object g_waterclippedRect;

//--------------------------------------------------------------------
Object g_waterRect;
Object g_basketRect;
double dir = 1;
double originRect_dir = 1;
//----------------------------------------------------------------------

vector<MousePosition> g_mousePosList;
int saveAmount = 2;

bool g_clipped=false;
bool g_paused =false;
bool g_inWater = false;
clock_t g_time;
bool g_quit=false;
bool g_boundary=false;

int g_collide = 0;
int g_rotation = Y_AXIS;
int g_shape = RECT;
int g_index = 0;

MousePosition g_dragPos;

void BaseLine()
{
	glColor3f(1, 1, 1);
	glLineWidth(3);
	glBegin(GL_LINES);
		glVertex3f(-1.0f, 0.0f, 0);
		glVertex3f(1.0f, 0.0f, 0);
		glVertex3f(0.0f, 1.0f, 0);
		glVertex3f(0.0f, -1.0f, 0);
		glColor3f(1, 1, 1);
		if (g_paused)
		{
			glVertex2f(g_mousePosList[0].x, g_mousePosList[0].y);
			cout << g_mousePosList[0].x << " " << g_mousePosList[0].y << endl;
			glVertex2f(g_dragPos.x, g_dragPos.y);
		}
		//auto current = clock();
		//if (current - g_time<(clock_t)400)
		//{
		//	for (auto data : g_mousePosList)
		//	{
		//		glVertex2f(data.x, data.y);
		//	}
		//}
	glEnd();


}
void Initialize()
{
	
	g_originalRect.verticies.push_back({ 0,0,0 });
	double x = rand() / double(RAND_MAX);
	double y = rand() / double(RAND_MAX);
	if (x < 0.3)x = 0.3;
	if (x > 0.6)x = 0.6;
	if (y > 0.5)y = 0.5;
	if (y < 0.2)y = 0.2;
	g_originalRect.verticies.push_back({x ,y,0 });
	g_originalRect.position = { 0,0.3,0 };
	g_originalRect.speed = ORIGINALRECT_SPEED;

	g_basketRect.verticies.push_back({0,0,0});
	g_basketRect.verticies.push_back({0.7,0.3,0});
	g_basketRect.position = { 0,-1,0 };
	g_basketRect.speed = BASCKET_SPEED;

	g_waterRect.verticies.push_back({0.0,0});
	g_waterRect.verticies.push_back({0.7,0.15,0});
	g_waterRect.position = { 0,-0.8,0 };

}
void MainMap()
{
	vector<Transform> pos;
	Transform min, max;
	Transform currentPosition;


	glPushMatrix();//오리지널 상자
		glColor3f(1, 0, 0);
			glTranslatef(g_originalRect.position.x, g_originalRect.position.y, 0);
		if (!g_paused)
		{
			if (!g_clipped)
			{
				if (g_originalRect.position.x + g_originalRect.verticies[1].x > 1)
				{
					g_originalRect.dir.x *= -1;
				}
				else if (g_originalRect.position.x < -0.9)
				{
					g_originalRect.dir.x *= -1;
				}
			}
			g_originalRect.position.x += (g_originalRect.speed*g_originalRect.dir.x);
		}
		if (!g_clipped)
		{
			glRectd(g_originalRect.verticies[0].x, g_originalRect.verticies[0].y, g_originalRect.verticies[1].x, g_originalRect.verticies[1].y);
		}
		else
		{
			glBegin(GL_POLYGON);
			for (auto data : g_originalRect.verticies)
			{
				glVertex2d(data.x, data.y);
			}
			glEnd();
		}
	glPopMatrix();

	glPushMatrix();//바구니와 물
		glColor3f(1, 1, 0);
			glTranslatef(g_basketRect.position.x, g_basketRect.position.y, 0);
		if (!g_paused)
		{
			if (g_basketRect.position.x + g_basketRect.verticies[1].x > 0.8)
				g_basketRect.dir.x *= -1;
			else if (g_basketRect.position.x < -0.95)
				g_basketRect.dir.x *= -1;
			g_basketRect.position.x += (g_basketRect.dir.x*g_basketRect.speed);
		}
		if (g_waterRect.verticies[1].y > 0.3)
			g_waterRect.dir.y *= -1;
		if (g_waterRect.verticies[1].y < 0.0)
			g_waterRect.dir.y *= -1;
		g_waterRect.verticies[1].y += g_waterRect.dir.y*0.01;
		glRectd(g_basketRect.verticies[0].x, g_basketRect.verticies[0].y, g_basketRect.verticies[1].x,  g_basketRect.verticies[1].y);
		glColor3f(0, 0, 1);
		glRectd(g_waterRect.verticies[0].x, g_waterRect.verticies[0].y, g_waterRect.verticies[1].x, g_waterRect.verticies[1].y);
	glPopMatrix();

	glPushMatrix();//잘린 사각형
		if (g_clipped)
		{
		g_waterclippedRect.position = g_clippedRect.position;
		cout << g_collide << endl;
			glColor3f(1, 1, 1);
			if(g_boundary)
			{
				glTranslatef(g_clippedRect.position.x, g_clippedRect.position.y, 0);
				glRotatef(g_clippedRect.degree, 0, 0, 1);
				g_clippedRect.degree += 20;
				g_clippedRect.position.x -= (0.2);
			}
			else if (g_collide==0)
			{
				if (g_inWater)
				{
					glTranslatef(g_clippedRect.position.x, g_clippedRect.position.y, 0);
					g_clippedRect.position.x += (g_basketRect.dir.x*g_basketRect.speed);
				}
				else
				{
					glTranslatef(g_clippedRect.position.x, g_clippedRect.position.y, 0);
					g_clippedRect.position.y -= g_clippedRect.speed;
				}
			}
			else if (g_collide == 1)
			{
				//g_clippedRect.position.x += (dir*g_basketRect.speed);
				glTranslatef(g_clippedRect.position.x, g_clippedRect.position.y, 0);
				g_boundary = true;
			}
			else
			{
				g_inWater = true;
				if (g_clippedRect.position.y > -1)
				{
					g_clippedRect.position.y -= g_clippedRect.speed;
				}
				glTranslatef(g_clippedRect.position.x, g_clippedRect.position.y, 0);
				g_clippedRect.position.x += (g_basketRect.dir.x*g_basketRect.speed);
			}
			//if(g_collide!=1)
			g_collide = 0;
			glBegin(GL_POLYGON);
			for (auto pos : g_clippedRect.verticies)
			{
					glVertex2f(pos.x, pos.y);
					if (g_collision.BoxCollision(g_basketRect.verticies[1].x + g_basketRect.position.x,
						g_basketRect.verticies[1].y + g_basketRect.position.y,
						g_basketRect.verticies[0].x + g_basketRect.position.x,
						g_basketRect.verticies[0].y + g_basketRect.position.y,
						pos.x+g_clippedRect.position.x, pos.y+g_clippedRect.position.y))
					{
						g_collide++;
						//cout << g_collide << endl;
					}
			}
			glEnd();
		}
	glPopMatrix();
	if (g_inWater)
	{

		g_clippedRect.speed = 0.03;
		glPushMatrix();


		glColor3f(0, 1, 0);
		Transform min = g_waterRect.verticies[0];
		Transform max = g_waterRect.verticies[1];
		max.y -= (1 + g_clippedRect.position.y);
		Transform newTop, newBottom;


		glBegin(GL_POLYGON);
		//glVertex2f(g_clippedRect.verticies[0].x, g_clippedRect.verticies[0].y );
		//glVertex2f(g_clippedRect.verticies[1].x, g_clippedRect.verticies[0].y);
		if (g_clippedRect.verticies[2].y + g_clippedRect.position.y > g_basketRect.position.y + g_waterRect.verticies[1].y)
		{

			glVertex2f(g_clippedRect.verticies[0].x + g_waterclippedRect.position.x, g_clippedRect.verticies[0].y + g_clippedRect.position.y);
			glVertex2f(g_clippedRect.verticies[1].x + g_waterclippedRect.position.x, g_clippedRect.verticies[0].y + g_clippedRect.position.y);
			//cout << "===========================================start===========================================================================" << endl;
			//printf("(%f , %f)\n", g_clippedRect.verticies[0].x + g_waterclippedRect.position.x, g_clippedRect.verticies[0].y + g_clippedRect.position.y);
			//printf("(%f , %f)\n", g_clippedRect.verticies[1].x + g_waterclippedRect.position.x, g_clippedRect.verticies[0].y + g_clippedRect.position.y);
			//resultX = m_lineStart.x + deltaX *(max.y - m_lineStart.y) / deltaY;
			//우측 위점 구하기-----------------------------------------------------------
			g_collision.SetLine(g_clippedRect.verticies[2], g_clippedRect.verticies[1]);

			g_collision.LineCollision(min, max, newTop, newBottom);
			//printf("(%f, %f), (%f, %f)\n", min.x, min.y, max.x,max.y);
			glVertex2f(newTop.x + g_waterclippedRect.position.x, g_basketRect.position.y + g_waterRect.verticies[1].y);
			//cout << newTop.x + g_waterclippedRect.position.x << " " << g_basketRect.position.y + g_waterRect.verticies[1].y << endl;
			//좌측 위점 구하기----------------------------------------------------------------------
			g_collision.SetLine(g_clippedRect.verticies[3], g_clippedRect.verticies[0]);
			g_collision.LineCollision(min, max, newTop, newBottom);
			glVertex2f(newTop.x + g_waterclippedRect.position.x, g_basketRect.position.y + g_waterRect.verticies[1].y);
			//cout << newTop.x + g_waterclippedRect.position.x << " " << g_basketRect.position.y + g_waterRect.verticies[1].y << endl;
			//cout << "===========================================end===========================================================================" << endl;
			//------------------------------------------------------------------------------
		}
		else {
			for (auto data : g_clippedRect.verticies)
			{
				glVertex2f(data.x + g_waterclippedRect.position.x, data.y + g_clippedRect.position.y);
			}
		}
		glEnd();
		glPopMatrix();
	}
	BaseLine();
}

//모양 기억
void Clipping(bool usingMouse)
{
	g_paused = false;
	static Transform start = {0,0,0};
	static Transform end = {0,0,0};
	Transform min, max,position;//원본 사각형 위치값

	min = g_originalRect.verticies[0];
	max = g_originalRect.verticies[1];
	position = g_originalRect.position;


	glColor3f(1, 0, 0);
	//glColor3f(1, 1, 1);
	//cout << start.x << " " << start.y << " " << end.x << " " << end.y<<endl

	if (usingMouse)
	{
		if (g_mousePosList.size() == 2 && !g_clipped)//마우스 입력을 두개 받았고 잘리지 않았다면
		{
			vector<MousePosition>::iterator iter = g_mousePosList.begin();
			Transform newStart, newEnd;

			MousePosition currentPos = *iter;

			
			start.x = currentPos.x - g_originalRect.position.x;
			start.y = currentPos.y - g_originalRect.position.y;
			++iter;

			currentPos = *iter;
			end.x = currentPos.x - g_originalRect.position.x;
			end.y = currentPos.y - g_originalRect.position.y;

			glColor3f(1, 1, 1);
			if (start.y >= g_originalRect.verticies[1].y)
			{
				g_collision.SetLine(start, end);//물리엔진이 체크할 선분 설정.
			}
			else if (start.y <= g_originalRect.verticies[0].y)
			{
				g_collision.SetLine(end, start);
			}
			else
			{
				g_collision.SetLine(start, end);
			}

			if (g_collision.LineCollision(min, max, newStart, newEnd))
			{
				bool isStartX = (newStart.x >= min.x && newStart.x <= max.x);
				bool isStartY = (newStart.y >= min.y && newStart.y <= max.y);
				bool isEndX = (newEnd.x >= min.x && newEnd.x <= max.x);
				bool isEndY = (newEnd.y >= min.y && newEnd.y <= max.y);
				if (isStartX&&isEndX)
				{
					g_originalRect.verticies.clear();
					if (newStart.x+end.x  < (max.x - newStart.x)+(max.x - newEnd.x))
					{
						g_clippedRect.verticies.push_back({ 0, 0,0 });
						g_clippedRect.verticies.push_back({ newEnd.x - min.x , 0,0 });
						g_clippedRect.verticies.push_back({ newStart.x - min.x , max.y - min.y,0 });
						g_clippedRect.verticies.push_back({ 0 , max.y - min.y,0 });

						g_originalRect.verticies.push_back({ newEnd.x - min.x , 0,0 });
						g_originalRect.verticies.push_back({ max.x - min.x , 0,0 });
						g_originalRect.verticies.push_back({ max.x - min.x ,max.y - min.y,0 });
						g_originalRect.verticies.push_back({ newStart.x - min.x , max.y - min.y,0 });
					}
					else
					{
						g_clippedRect.verticies.push_back({ newEnd.x - min.x , 0,0 });
						g_clippedRect.verticies.push_back({ max.x - min.x , 0,0 });
						g_clippedRect.verticies.push_back({ max.x - min.x ,max.y - min.y,0 });
						g_clippedRect.verticies.push_back({ newStart.x - min.x , max.y - min.y,0 });

						g_originalRect.verticies.push_back({ 0, 0,0 });
						g_originalRect.verticies.push_back({ newEnd.x - min.x , 0,0 });
						g_originalRect.verticies.push_back({ newStart.x - min.x , max.y - min.y,0 });
						g_originalRect.verticies.push_back({ 0 , max.y - min.y,0 });
					}
				}
				g_clippedRect.speed = 0.1;
				g_clippedRect.position = g_originalRect.position;
				//cout << min. x<< min.y << endl;
				/*glBegin(GL_LINES);
				glVertex2f(start.x, start.y);
				glVertex2f(end.x, end.y);
				glEnd();*/
				g_clipped = true;
				
			}
		}
	}

}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glMatrixMode(GL_MODELVIEW);
	MainMap();
	
	glutSwapBuffers(); // 화면에 출력하기
}
int main()
{
	srand((unsigned)time(NULL));
	OpenGLClass* glclass=new OpenGLClass(WINDOW_WIDTH, WINDOW_HEIGHT,&MenuFunc);

	Initialize();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutMotionFunc(Motion);
	
	glutMainLoop();

	delete glclass;
	return 0;
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w,h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	////-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. 
	//// . 클리핑 공간 설정: 원근 투영인 경우 
	//gluPerspective(60.0f, w / h, -1, 1);
	//glTranslatef(0.0, 0.0, -1.75); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
	//								// 2. 클리핑 공간 설정: 직각 투영인 경우
	//								// glOrtho (0, 800.0, 0.0, 600.0, -1.0, 00.0);
	//								// 모델 뷰 행렬 스택 재설정 
	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
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
		g_paused = true;
		inputY = 700 - y;

		inputX = (float)(x - (float)WINDOW_WIDTH / 2.0)*(float)(1.0 / (float)(WINDOW_WIDTH / 2.0));

		inputY = -(float)(y - (float)WINDOW_HEIGHT / 2.0)*(float)(1.0 / (float)(WINDOW_HEIGHT / 2.0));

		//cout << inputX << " " << inputY <<  "mouseregist" << endl;
		if (g_mousePosList.size()>=saveAmount)
		{
			g_mousePosList.clear();
		}
		g_mousePosList.push_back({ inputX,inputY });
	}
	else if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP)
	{
		inputY = 700 - y;

		inputX = (float)(x - (float)WINDOW_WIDTH / 2.0)*(float)(1.0 / (float)(WINDOW_WIDTH / 2.0));

		inputY = -(float)(y - (float)WINDOW_HEIGHT / 2.0)*(float)(1.0 / (float)(WINDOW_HEIGHT / 2.0));

		if (g_mousePosList.size() >= saveAmount)
		{
			g_mousePosList.clear();
		}
		g_mousePosList.push_back({ inputX,inputY });

		Clipping();
	}

}
void Motion(int x, int y)
{
	float inputX, inputY;

	inputY = 700 - y;

	inputX = (float)(x - (float)WINDOW_WIDTH / 2.0)*(float)(1.0 / (float)(WINDOW_WIDTH / 2.0));

	inputY = -(float)(y - (float)WINDOW_HEIGHT / 2.0)*(float)(1.0 / (float)(WINDOW_HEIGHT / 2.0));

	g_dragPos = { inputX, inputY };
	
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'c')
	{
		g_mousePosList.clear();
		saveAmount = 2;

		g_clipped = false;
		g_paused = false;
		g_inWater = false;
		g_boundary = false;
		g_collide = 0;
	}
	if (key == 'p'|| key == 'P')
	{
		
		//----------------------------------------------------------------------

		g_mousePosList.clear();

		saveAmount = 2;

		g_clipped = false;
		g_paused = false;
		g_inWater = false;
		g_boundary = false;
		g_collide = 0;

		g_originalRect.verticies.clear();
		g_originalRect.verticies.push_back({ 0 ,0,0 });
		g_originalRect.dir = { 1,1,1 };
		double x = rand() / double(RAND_MAX);
		double y = rand() / double(RAND_MAX);
		if (x < 0.3)x = 0.3;
		if (x > 0.6)x = 0.6;
		if (y > 0.5)y = 0.5;
		if (y < 0.2)y = 0.2;
		g_originalRect.verticies.push_back({ x ,y,0 });
		g_originalRect.position = { 0,0.3,0 };
		g_originalRect.speed = ORIGINALRECT_SPEED;

		g_basketRect.position = { 0,-1,0 };
		g_basketRect.speed = BASCKET_SPEED;
		g_basketRect.dir = { 1,1,1 };
		g_waterRect.position = { 0,-0.8,0 };

		g_clippedRect.position = { 0,0,0 };
		g_clippedRect.verticies.clear();
	}
	if (key == 'q' || key == 'Q')
	{
		exit(EXIT_FAILURE);
	}
}


void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		g_shape = TRIANGLE;
		break;
	case 2:
		g_shape = RECT;
		break;
	case 3:
		g_shape = CIRCLE;
		break;

	}
	glutPostRedisplay();
}