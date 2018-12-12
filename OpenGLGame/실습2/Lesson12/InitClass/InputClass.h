#pragma once

class InputClass
{
public:
	InputClass();
	~InputClass();
	void Mouse(int button, int state, int x, int y);//x,y���� ������ �����̱� ������ ��������� 0,0�̴�.
	void Keyboard(unsigned char key, int x, int y);
	void GetMousePositions(list<MousePosition>::iterator &start, list<MousePosition>::iterator &end);

private:
	MousePosition currentPos;
	list<MousePosition> mousePositions;
	int saveAmount;
};

