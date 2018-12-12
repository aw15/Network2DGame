#include "stdafx.h"
#include "OpenGLClass.h"



OpenGLClass::OpenGLClass(int width,int length, void(*Menufunc)(int))
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(width, length); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 
	m_menufunc = Menufunc;
}

void OpenGLClass::MenuLayout()
{
	int SubMenu1, SubMenu2, SubMenu3;
	int MainMenu;


	SubMenu1 = glutCreateMenu(m_menufunc);
	glutAddMenuEntry("삼각형", 1);
	glutAddMenuEntry("사각형", 2);
	glutAddMenuEntry("원", 3);

	SubMenu2 = glutCreateMenu(m_menufunc);
	glutAddMenuEntry("Red", 11);
	glutAddMenuEntry("Green", 22);

	SubMenu3 = glutCreateMenu(m_menufunc);
	glutAddMenuEntry("Wire", 111);
	glutAddMenuEntry("Solid", 222);

	MainMenu = glutCreateMenu(m_menufunc);
	glutAddSubMenu("Shape", SubMenu1);
	glutAddSubMenu("Color", SubMenu2);
	glutAddSubMenu("State", SubMenu3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}




OpenGLClass::~OpenGLClass()
{
}

