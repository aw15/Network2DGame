#pragma once
class Renderer
{
public:
	Renderer();
	void DrawShape(char shape, int x, int y, int size,const Color& color);
	~Renderer();
private:
	void DrawRect(int x, int y, int size);
	void DrawCircle(int x, int y, int size);
	void DrawTriangle(int x, int y, int size);
	void DrawLine(int x, int y, int size);
	void DrawPoint(int x, int y, int size);
};

