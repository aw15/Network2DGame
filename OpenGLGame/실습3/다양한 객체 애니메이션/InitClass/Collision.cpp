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

	bool bAccept = false;//���� ���ο� ���ԵǴ� ��������

	while (true)
	{
		if (!(startCode | endCode))//������ ���ȿ� ��ġ(0000)
		{
			//cout << "finalTest";
			bAccept = true;
			break;
		}
		//�� �ڵ��� and������ 0�� �ƴϸ� �ܺο� �ִٴ� ��
		else if (startCode&endCode)
		{
			break;
		}
		else
		{
			float resultX = 0, resultY = 0;
			OutCode outCode = startCode ? startCode : endCode;
			//cout << outCode << endl;
			//Ŭ���� ���� �ۿ� �ִ� ���� Ŭ���� ������ �������� ã�Ƽ� ����
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
			// ������ ���� ����� �����ȿ� �������� �˻��ϰ�
			// ���� ������ ���� �غ�
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
