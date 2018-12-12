#pragma once
class Collision
{
public:
	Collision();
	bool BoxCollision(const int maxX,const int maxY,const int minX,const int minY, const int targetX,const int targetY);
	~Collision();
};

