#pragma once
class Renderer
{
public:
	Renderer();
	void DrawRect(int x, int y, int size);
	void DrawShape(char shape, int x, int y, int size, const Color& color);
	void DrawCircle(int x, int y, int size);
	void DrawTriangle(int x, int y, int size);
	~Renderer();
};

