#include "stdafx.h"
#include "OpenGLClass.h"



OpenGLClass::OpenGLClass(int width,int length)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(width, length); // �������� ũ�� ���� 
	glutCreateWindow("Example"); // ������ ���� (������ �̸�) 

}


OpenGLClass::~OpenGLClass()
{
}

