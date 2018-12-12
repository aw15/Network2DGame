#include "stdafx.h"
#include "InputClass.h"


InputClass::InputClass()
{
	currentPos.x = 0;
	currentPos.y = 0;
	mousePositions.clear();
	saveAmount = 10;
}


void InputClass::GetMousePositions(list<MousePosition>::iterator &start, list<MousePosition>::iterator &end)
{
	start = mousePositions.begin();
	end = mousePositions.end();
}

InputClass::~InputClass()
{
}
