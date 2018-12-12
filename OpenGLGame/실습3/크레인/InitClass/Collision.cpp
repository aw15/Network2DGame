#include "stdafx.h"
#include "Collision.h"


Collision::Collision()
{
}

bool Collision::BoxCollision(const float maxX, const float maxY, const float minX, const float minY, const float targetX, const float targetY)
{
	if (targetX<maxX&&targetX>minX&&targetY<maxY&&targetY>minY)
		return true;
	return false;
}

void Collision::SetLine(Transform & _start, Transform & _end)
{
	m_lineStart = _start;
	m_lineEnd = _end;
}

OutCode Collision::ComputeOutCode(float x, float y, Transform & min, Transform & max)
{
	OutCode code;

	code = INSIDE;          // initialised as being inside of [[clip window]]

	if (x < min.x)           // to the left of clip window
		code |= LEFT;
	else if (x > max.x)      // to the right of clip window
		code |= RIGHT;
	if (y < min.y)           // below the clip window
		code |= BOTTOM;
	else if (y > max.y)      // above the clip window
		code |= TOP;

	//cout << code << endl;
	return code;
}


bool Collision::LineCollision( Transform & min,  Transform & max, Transform& _newStart, Transform& _newEnd)
{

	OutCode startCode = ComputeOutCode(m_lineStart.x,m_lineStart.y,min,max);
	OutCode endCode = ComputeOutCode(m_lineEnd.x,m_lineEnd.y,min,max);
	//cout << startCode << " " << endCode << endl;

	bool bAccept = false;//완전 내부에 포함되는 직선인지

	while (true)
	{
		if (!(startCode | endCode))//두점다 경계안에 위치(0000)
		{
			//cout << "finalTest";
			bAccept = true;
			break;
		}
		//두 코드의 and연산이 0이 아니면 외부에 있다는 것
		else if (startCode&endCode)
		{
			break;
		}
		else
		{
			float resultX = 0, resultY = 0;
			OutCode outCode = startCode ? startCode : endCode;
			//cout << outCode << endl;
			//클리핑 영역 밖에 있는 점과 클리핑 영역의 교차점을 찾아서 보정
			float deltaX = m_lineEnd.x - m_lineStart.x;
			float deltaY = m_lineEnd.y - m_lineStart.y;



			if (outCode&TOP)
			{
				resultX = m_lineStart.x + deltaX *(max.y - m_lineStart.y) / deltaY;
				resultY = max.y;
			}
			else if (outCode & BOTTOM)
			{
				resultX = m_lineStart.x + deltaX * (min.y - m_lineStart.y) / deltaY;
				resultY = min.y;
			}
			else if (outCode & RIGHT)
			{
				resultX = max.x;
				resultY = m_lineStart.y + deltaY * (max.x - m_lineStart.x) / deltaX;
			}
			else if (outCode & LEFT)
			{
				resultX = min.x;
				resultY = m_lineStart.y + deltaY * (min.x - m_lineStart.x) / deltaX;
			}
			// 보정된 값이 제대로 영역안에 들어오는지 검사하고
			// 다음 보정을 위한 준비
			if (outCode == startCode)
			{
				//cout << "start: "<<resultX << " " << resultY << endl;
				_newStart.x = resultX;
				_newStart.y = resultY;
				startCode = ComputeOutCode(_newStart.x, _newStart.y,min,max);
			}
			else
			{
				//cout << "end: " << resultX << " " << resultY << endl;
				_newEnd.x = resultX;
				_newEnd.y = resultY;
				endCode = ComputeOutCode(_newEnd.x, _newEnd.y,min,max);
				//cout << endCode << endl;
			}
		}
	}
	
	if (bAccept)
	{
		//cout << _newStart.x<<endl;
		//cout << "finaltest" << endl;
		return true;
	}
	return false;
}


Collision::~Collision()
{
}
