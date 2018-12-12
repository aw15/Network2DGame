#pragma once


#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

typedef int OutCode;

class Collision
{
public:
	Collision();
	OutCode ComputeOutCode(double x, double y, Transform & min, Transform & max);
	bool BoxCollision(const float maxX,const float maxY,const float minX,const float minY, const float targetX,const float targetY);
	void SetLine(Transform& _start, Transform& _end);
	bool LineCollision( Transform& min, Transform& max, Transform& _newStart, Transform& _newEnd);
	~Collision();
private:
	Transform m_lineStart;
	Transform m_lineEnd;
};

