#pragma once

#include"Util.h"

#define PI 3.141592
#define TRI_NUM 15




class Effect
{
	float radius=1;
	Vector3 rotation = { 0,0,0 };
	Vector3 color;
	Vector3 position;
	Vector3 position2;
	Vector3 defaultPosition;
	int max;
	coordi trans[TRI_NUM];
	float angle = 0;
	float radian = 0;

	Vector3 dir[20];
	float speed[20];
	Vector3 effectPos[20];
	Vector3 effectColor;
public:
	bool end = false;

	Effect(Vector3 position,Vector3 color);
	void Render();

};