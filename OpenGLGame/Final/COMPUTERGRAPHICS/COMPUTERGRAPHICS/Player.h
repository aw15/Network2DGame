#pragma once
#include "Bullet.h"

class Bullet;

class Player
{
public:
	Player();
	~Player();

	void Shoot();
	void RotateZ(int degree);
	void RotateX(int degree);
	void RotateY(int degree);
	void Move(Vector3& move);
	void Update();
	void Render();
	//------------변수---------------------------
	Vector3 color;
	Vector3 position;
	Vector3 rotation = {0,0,1};
	Vector3 scale;
	Vector3 direction;
	int degree = 0;
	coordi Gun;
	bool fire=false;
public:
	bool helpingLine = false;

	float size;
	float radius;
	float prev_time;
	float elapsedTime;
	//------------총알 리스트--------------
	list<Bullet*> bulletList;
};
