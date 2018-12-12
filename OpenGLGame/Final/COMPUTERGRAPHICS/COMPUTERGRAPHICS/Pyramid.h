#pragma once
#include"Util.h"

struct TriangleList
{
	Vector3 bottom[4];
	Vector3 left[3];
	Vector3 right[3];
	Vector3 front[3];
	Vector3 back[3];
};




class Pyramid
{
public:
	Pyramid();
	void Render();
	//---------------회전-----------------------
	void RotateZ(int degree);
	void RotateX(int degree);
	void RotateY(int degree);
	//------------Move------------------------
	void Move(Vector3 direction);
	void ChangeColor(Vector3 param, int );
	//------------중점 반환
	TriangleList* GetCollider();
public:
	Vector3 verticies[5] =
	{
		{ -50.0, -50.0, -50.0 },
		{ -50.0, -50.0, 50.0 },
		{ 50.0, -50.0, 50.0 },
		{ 50.0, -50.0, -50.0 },
		{ 0.0,80.0, 0.0 }
	};
	int zDegree=0;


	Vector3 color[5] = { { 253,243,187 },{ 253,243,187 },{ 253,243,187 },{ 253,243,187 },{ 253,243,187 } };
	Vector3 position = {0,0,0};
	Vector3 rotation = {0,0,2};
	TriangleList colliderPlane;
	Vector3 maxPoint;
	Vector3 minPoint;
};
