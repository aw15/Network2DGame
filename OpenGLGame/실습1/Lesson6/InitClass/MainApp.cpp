// InitClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <GL/glut.h> 
#include <stdio.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

int on = 0;

float angle = 10;


void main(int argc, char** argv)    // 윈도우 출력하고 출력함수 설정 
{

	glutInit(&argc, argv);    // glut 초기화        
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);   // 윈도우의 위치 지정
	glutInitWindowSize(600, 600);    // 윈도우의 크기 지정
	glutCreateWindow("13");   // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene);    // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);   // 다시 그리기 함수 지정
	glutMainLoop();    // 이벤트 처리 시작 
}
GLvoid drawScene()     // 출력 함수 
{
	//glMatrixMode(GL_MODELVIEW);
	printf("teset");

	//if (on == 1) {
	//	glRotatef(45.0f + angle, 0.0f, 1.0f, 0.0f);
	//	printf("d");
	//}


	//xy축 평면 삼각형

	//yz평면에 삼각형


	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'h') {
		on = 1;
		printf("나와?\n");
	}
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}