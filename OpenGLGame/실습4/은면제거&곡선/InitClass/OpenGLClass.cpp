#include "stdafx.h"
#include "OpenGLClass.h"



OpenGLClass::OpenGLClass(int width,int length, void(*Menufunc)(int))
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 30); // 윈도우의 위치지정 
	glutInitWindowSize(width, length); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 
	m_menufunc = Menufunc;
}




OpenGLClass::~OpenGLClass()
{
}

