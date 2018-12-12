#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}
void Renderer::DrawRect(int x, int y, int size)
{
	glRectf(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2));
}


Renderer::~Renderer()
{
}
