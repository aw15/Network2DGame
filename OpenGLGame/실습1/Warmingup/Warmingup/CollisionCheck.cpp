#include"stdafx.h"

#define MIN 0
#define MAX 1

class Rectangle {
private:
	pair<int, int> minPoint;
	pair<int, int> maxPoint;
public:
	Rectangle(int x1, int y1, int x2, int y2)
	{
		minPoint.first = x1;
		minPoint.second = y1;
		maxPoint.first = x2;
		maxPoint.second = y2;
	}
	void GetCord(pair<int,int> *rect)
	{
		rect[0] = minPoint;
		rect[1] = maxPoint;
	}
	void SetCord(int x, int y)
	{
		minPoint.first += x;
		minPoint.second += y;
		maxPoint.first += x;
		maxPoint.second += y;
	}
	void Show()
	{
		printf("(%d, %d), (%d, %d)\n",minPoint.first, minPoint.second, maxPoint.first, maxPoint.second );
	}

};



bool CheckCollision(Rectangle& A, Rectangle& B) {
	pair<int, int> rectA[2];
	A.GetCord(rectA);
	pair<int, int> rectB[2];
	B.GetCord(rectB);

	for (int i = MIN; i < MAX; ++i)
	{
		if (rectA[MIN].first <= rectB[i].first&&rectA[MAX].first >= rectB[i].first)
		{
			for (int j = MIN; j < MAX; ++j)
			{
				if (rectA[MIN].second <= rectB[i].second&&rectA[MAX].second >= rectB[i].second)
				{
					return true;
				}
			}
		}
	}
	return false;
}

int main()
{
	int x1, y1, x2,y2;

	cout << "사각형 A좌표: ";
	cin >> x1 >> y1 >> x2>>y2;
	Rectangle A(x1,y1,x2,y2);
	cout << "사각형 B좌표: ";
	cin >> x1 >> y1 >> x2>>y2;
	Rectangle B(x1,y1,x2,y2);

	char selection;

	while (true)
	{
		cout << "\n=====================\n";
		cout << "사각형A: ";
		A.Show();
		cout << "사각형B: ";
		B.Show();
		cin >> selection;
		switch (selection)
		{
		case 'a':
			A.SetCord(-40, 0);
			break;
		case 'd':
			A.SetCord(40, 0);
			break;
		case 'w':
			A.SetCord(0, 40);
			break;
		case 's':
			A.SetCord(0, -40);
			break;
		}
		if (CheckCollision(A, B))
		{
			cout << "A와 B가 충돌했습니다." << endl;
			break;
		}
	}
}