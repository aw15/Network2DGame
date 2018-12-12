#include "stdafx.h"
#include "OpenGLClass.h"



OpenGLClass::OpenGLClass(int width,int length, void(*Menufunc)(int))
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(width, length); // �������� ũ�� ���� 
	glutCreateWindow("Example"); // ������ ���� (������ �̸�) 
	m_menufunc = Menufunc;
}

void OpenGLClass::MenuLayout()
{
	int SubMenu1, SubMenu2, SubMenu3;
	int MainMenu;


	SubMenu1 = glutCreateMenu(m_menufunc);
	glutAddMenuEntry("�ﰢ��", 1);
	glutAddMenuEntry("�簢��", 2);
	glutAddMenuEntry("��", 3);

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

