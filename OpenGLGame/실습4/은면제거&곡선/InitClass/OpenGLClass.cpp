#include "stdafx.h"
#include "OpenGLClass.h"



OpenGLClass::OpenGLClass(int width,int length, void(*Menufunc)(int))
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 30); // �������� ��ġ���� 
	glutInitWindowSize(width, length); // �������� ũ�� ���� 
	glutCreateWindow("Example"); // ������ ���� (������ �̸�) 
	m_menufunc = Menufunc;
}




OpenGLClass::~OpenGLClass()
{
}

