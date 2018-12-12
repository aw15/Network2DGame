#pragma once
#include "Util.h"

class Bullet
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 currentPosition;
public:
	Bullet(Vector3 position, Vector3 rotation);
	~Bullet();
	void Update();
	void Render();
	Vector3 GetCollider();
private:
	Vector3 color;
};


