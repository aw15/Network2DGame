#include "stdafx.h"
#include "Collision.h"


Collision::Collision()
{
}

bool Collision::BoxCollision(const int maxX, const int maxY, const int minX, const int minY, const int targetX, const int targetY)
{
	if (targetX<maxX&&targetX>minX&&targetY<maxY&&targetY>minY)
		return true;
	return false;
}


Collision::~Collision()
{
}
