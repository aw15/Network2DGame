#include "stdafx.h"
#include "InputClass.h"


InputClass::InputClass()
{
	currentPos.x = 0;
	currentPos.y = 0;
	mousePositions.clear();
	saveAmount = 10;
}


void InputClass::GetMousePositions(list<MousePosition>::iterator &m_lineStart, list<MousePosition>::iterator &end)
{
	m_lineStart = mousePositions.begin();
	end = mousePositions.end();
}

InputClass::~InputClass()
{
}
