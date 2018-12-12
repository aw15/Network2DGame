#pragma once
class OpenGLClass
{
public:
	OpenGLClass(int,int, void(*Menufunc)(int));
	void MenuLayout();
	~OpenGLClass();

private:
	int width;
	int length;
	void (*m_menufunc)(int);
};

