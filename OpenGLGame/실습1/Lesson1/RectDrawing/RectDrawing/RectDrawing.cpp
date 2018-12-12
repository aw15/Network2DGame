// RectDrawing.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

	void MakeLog(char* str)
	{
		ofstream outFile;
		outFile.open("C:\\Users\didxo\Desktop\Log.txt", std::ios::app);
		outFile << str << std::endl;
		outFile.close();
	}

void Training1()
{
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glRectf(-1, 0.5, -0.5, 1);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glRectf(1, 0.5, 0.5, 1);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRectf(-1, -1, -0.5, -0.5);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRectf(0.5, -1, 1, -0.5);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRectf(-0.3, -0.3, 0.3, 0.3);
}
void Training2()
{
	glOrtho(-400, 400, -300, 300, -1.0, 1.0);
	srand(time(NULL));

	int xCount = rand()%10+6;
	int yCount = rand()%10+6;

	int xAmount=800/xCount;
	int yAmount=600/yCount;



	bool isRed;
	for (int i = 1; i <= yCount; i++)
	{
		if (i % 2 != 0)isRed = true;
		else if (i %2==0 )isRed = false;
		for (int j = 0; j < xCount; j++)
		{
			if (isRed)
			{
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				isRed = false;
			}
			else
			{
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				isRed = true;
			}
			glRectf(-400 + (xAmount*(j-1)), 300-(yAmount*i), -400+(xAmount*j), 300 - (yAmount*(i-1)));
			//glRectf(-400, 300-yAmount, -400-xAmount, 300);
			
		}
		
	}
}
void Training3()
{
	glOrtho(-450, 450, -450, 450, -1.0, 1.0);
	srand(time(NULL));
	int current = rand() % 4;
	pair<int, int> MinPoint = { -450,150 };
	pair<int, int> MaxPoint = { -150,450 };

	GLint p1[2], p2[2], p3[2], p4[2], p5[2];
	

	for (int i = 0; i < 900; i=i+300)
	{
		for (int j = 0; j < 900; j=j+300)
		{
			
			switch (current)
			{
			case LINE:
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				p1[0] = MinPoint.first + j;
				p1[1] = (MaxPoint.second-MinPoint.second) - i;
				p2[0] = MaxPoint.first + j;
				p2[1] = (MaxPoint.second - MinPoint.second) - i;
				glBegin(GL_LINES);
				glVertex2iv(p1);
				glVertex2iv(p2);
				glEnd();
				current = TRIANGLE;
				break;
			case TRIANGLE:
				glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
				p1[0] = (MinPoint.first - MaxPoint.first) + j;
				p1[1] = MaxPoint.second - i;
				p2[0] = MinPoint.first + j;
				p2[1] = MinPoint.second - i;
				p3[0] = MaxPoint.first + j;
				p3[1] = MinPoint.second - i;
				glBegin(GL_TRIANGLES);
				glVertex2iv(p1);
				glVertex2iv(p2);
				glVertex2iv(p3);
				glEnd();
				current = RECT;
				break;
			case RECT:
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				p1[0] = MinPoint.first + j;
				p1[1] = MaxPoint.second - i;
				p2[0] = MinPoint.first + j;
				p2[1] = MinPoint.second - i;
				p3[0] = MaxPoint.first + j;
				p3[1] = MinPoint.second - i;
				p4[0] = MaxPoint.first + j;
				p4[1] = MaxPoint.second - i;
				glBegin(GL_POLYGON);
				glVertex2iv(p1);
				glVertex2iv(p2);
				glVertex2iv(p3);
				glVertex2iv(p4);
				glEnd();
				current = PENTAGON;
				break;
			case PENTAGON:
				glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
				p1[0] = (MinPoint.first - MaxPoint.first) + j;
				p1[1] = MaxPoint.second - i;
				p2[0] = MinPoint.first + j;
				p2[1] = (MaxPoint.second - MinPoint.second) - i;
				p3[0] = MinPoint.first + j;
				p3[1] = MinPoint.second - i;
				p4[0] = MaxPoint.first + j;
				p4[1] = MinPoint.second - i;
				p5[0] = MaxPoint.first + j;
				p5[1] = (MaxPoint.second - MinPoint.second) - i;
				glBegin(GL_POLYGON);
				glVertex2iv(p1);
				glVertex2iv(p2);
				glVertex2iv(p3);
				glVertex2iv(p4); 
				glVertex2iv(p5);
				glEnd();
				current = LINE;
				break;
			}
		}
	}

}
void main (int argc, char *argv[] )
{ //초기화 함수들
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
glutCreateWindow("Example" ); // 윈도우 생성 (윈도우 이름) 
glutDisplayFunc(drawScene); // 출력 함수의 지정 
glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	//Training1();
	//Training2();
	//Training3();
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape (int w, int h)
{
	glViewport(0, 0, w, h);
}
