#include"stdafx.h"
#define SIZE 50
#define WALL 1
#define ROAD 0
class Maze {
private:
	int maze[SIZE][SIZE];
	pair<int, int> current = { 1,1 };
public:
	Maze() {
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				maze[i][j] = WALL;
			}
		}
		maze[0][0] = 0;
		maze[SIZE - 1][SIZE - 1] = 0;
	}
	void MakeRoad() {
		srand((unsigned int)time(NULL));
		int value;
		while (current.first != SIZE - 1 && current.second != SIZE - 1) 
		{
			
			value = rand() % 100 + 1;

			//cout << value << endl;

			if (value < 40)
			{
				maze[current.first][current.second] = 0;
				current.first++;
				current.second++;
			}
			else if (value >= 40 && value < 50)
			{
				maze[current.first][current.second-1] = 0;
				maze[current.first][current.second] = 0;
				current.first++;
				current.second++;
			}
			else if (value >= 50 && value < 65)
			{
				maze[current.first-1][current.second] = 0;
				maze[current.first - 1][current.second+1] = 0;
				maze[current.first][current.second + 1] = 0;
				maze[current.first+1][current.second+1] = 0;
				current.first+=2;
				current.second+=2;
			}
			else if (value >= 65 && value < 80)
			{
				maze[current.first][current.second] = 0;
				maze[current.first][current.second-1] = 0;
				maze[current.first +1][current.second - 1] = 0;
				maze[current.first + 2][current.second - 1] = 0;
				maze[current.first+2][current.second] = 0;
				maze[current.first + 2][current.second + 1] = 0;
				maze[current.first + 2][current.second + 2] = 0;
				current.first += 2;
				current.second += 2;
			}
			else
			{
				maze[current.first-1][current.second] = 0;
				maze[current.first][current.second] = 0;
				current.first++;
				current.second++;
			}
			
		}

	}
	void Show()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				cout << maze[i][j];
			}
			cout << endl;
		}
	}
	void Clear()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				maze[i][j] = WALL;
			}
		}
		maze[0][0] = 0;
		maze[SIZE - 1][SIZE - 1] = 0;
		current = { 1,1 };
	}
};

int main()
{
	Maze maze1;
	char selection;
	while (true)
	{
		cin >> selection;
		if (selection == 'q')break;
		maze1.MakeRoad();
		maze1.Show();
		maze1.Clear();
	}
}