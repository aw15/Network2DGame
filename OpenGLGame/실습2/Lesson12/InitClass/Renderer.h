#pragma once
class Renderer
{
public:
	Renderer();
	void DrawShape(char shape, Transform& position, Transform& rotation,const int angle ,float size,const Color& color);
	~Renderer();
private:
	void DrawRect();
	void DrawCircle();
	void DrawTriangle();
	void DrawLine();
	void DrawPoint();
	void DrawTonado();
	void DrawSin();
};

