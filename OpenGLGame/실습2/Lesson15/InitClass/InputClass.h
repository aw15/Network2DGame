#pragma once

class InputClass
{
public:
	InputClass();
	~InputClass();
	void Mouse(int button, int state, int x, int y);//x,y값은 윈도우 기준이기 때문에 좌측상단이 0,0이다.
	void Keyboard(unsigned char key, int x, int y);
	void GetMousePositions(list<MousePosition>::iterator &start, list<MousePosition>::iterator &end);

private:
	MousePosition currentPos;
	list<MousePosition> mousePositions;
	int saveAmount;
};

