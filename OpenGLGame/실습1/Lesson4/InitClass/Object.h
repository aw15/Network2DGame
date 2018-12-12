#pragma once
class Object
{
public:
	Object();
	void SetTransform(int x = 0, int y = 0,int size=1)
	{
		this->x = x;
		this->y = y;
		this->size = size;
	}
	void setColor(float r=0.0f, float g=0.0f, float b = 0.0f, float a = 0.0f)
	{
		glColor4f(r, g, b, a);
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	void GetTransform(int &x, int &y,int& size)
	{
		x = this->x;
		y = this->y;
		size = this->size;
	}
	void GetColor(int &r, int &g, int& b, int& a)
	{
		r = this->r;
		r = this->g;
		r = this->b;
		r = this->a;
	}
	~Object();
private:
	int size;
	int x,y;
	float r, g, b,a;
};

