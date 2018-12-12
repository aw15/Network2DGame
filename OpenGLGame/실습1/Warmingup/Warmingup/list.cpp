#include "stdafx.h"
#define MAX 10

class List 
{
	struct vector {
		vector() {}
		vector(int x, int y, int z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		int x, y, z;
		vector* next=nullptr;
	};
private:
	int len;
public:
	vector* head;
	List()
	{
		head = nullptr;
		len = 0 ;
	}
	bool Push(const int x,const int y,const int z)
	{
		if (head == nullptr)
		{
			head = new vector(x, y, z);
			head->next = nullptr;
		}
		else if (len < MAX) {
			vector* newNode = new vector(x, y, z);
			newNode->next = nullptr;
			vector* prev = head;
			while (prev->next != nullptr) { prev = prev->next; }
			prev->next = newNode;
		}
		else
			return false;
		len++;
		return true;
	}
	bool Pop(int &x,int &y,int &z)
	{
		if (len > 0)
		{
			if (head->next == nullptr)
			{
				x = head->x;
				y = head->y;
				z = head->z;
				delete head;
				head = nullptr;
			}
			else {
				vector* target = head;
				for (int i = 0; i < len - 2; ++i) { target = target->next; }
				x = target->next->x;
				y = target->next->y;
				z = target->next->z;
				delete target->next;
				target->next = nullptr;
			}
		}
		else
			return false;
		len--;
		return true;
	}
	bool Show(){
		if (head!=nullptr)
		{
			vector* current = head;
			cout << "====================결과=======================" << endl;
			while (current != nullptr) {
				printf("%d %d %d\n", current->x, current->y, current->z);
				current = current->next;
			}
			cout <<"길이"<< len<<endl;
			cout << "===========================================" << endl;
		}
		else
			return false;
		return true;
	}
	bool enque(int x, int y, int z)
	{
		if (head == nullptr)
		{
			head = new vector(x, y, z);
			head->next = nullptr;
		}
		else if (len < MAX) {
			vector* newNode = new vector(x, y, z);
			newNode->next = head;
			head = newNode;
		}
		else
			return false;
		len++;
		return true;
	}
	bool deque(int &x, int &y, int &z)
	{
		if (len > 0)
		{
			if (head->next == nullptr)
			{
				x = head->x;
				y = head->y;
				z = head->z;
				delete head;
				head = nullptr;
			}
			else {
				vector* target = head;
				x = head->x;
				y = head->y;
				z = head->z;
				head = head->next;
				delete target;
			}
		}
		else
			return false;
		len--;
		return true;
	}
	void Clear()
	{
		while (head!=nullptr)
		{
			if (head->next == nullptr)
			{
				delete head;
				head = nullptr;
			}
			else {
				vector* target = head;
				head = head->next;
				delete target;
			}
		}
		len = 0;
	}
	double MaxDistance()
	{
		double max=0;
		vector* current = head;
		double result=0;
		while (current != nullptr)
		{
			
			result = sqrt((current->x*current->x) + (current->y*current->y) + (current->z*current->z));
			current = current->next;
			if (result > max)
				max=result;
		}
		return max;
	}
	double MinDistance()
	{
		double min=1000;
		vector* current = head;
		double result;
		while (current != nullptr)
		{

			result = sqrt((current->x*current->x) + (current->y*current->y) + (current->z*current->z));
			current = current->next;
			if (result < min)
				min = result;
		}
		return min;
	}
	int GetLen() { return len; }
};
int main()
{
	List list;
	int x = 0, y = 0, z = 0;
	char selection;
	double result;
	printf("+:push -:pop l:길이\ne:맨아래 입력\nd:맨아래출력 c:clear\nm:원점에서 가장 먼 거리에 있는 점\nn:원점에서 가장 가까운 거리에 있는 점\nq:종료\n");
	while (true)
	{

		
		cin >> selection;
		if (selection == 'q')
			break;
		switch (selection)
		{
		case'+':
			cin >> x >> y >> z;
			list.Push(x, y, z);
			list.Show();
			break;
		case '-':
			list.Pop(x, y, z);
			list.Show();
			break;
		case 'l':
			cout <<"길이는 " <<list.GetLen() << endl;
			break;
		case 'e':
			cin >> x >> y >> z;
			list.enque(x,y,z);
			list.Show();
			break;
		case 'd':
			list.deque(x, y, z);
			list.Show();
			break;
		case 'c':
			list.Clear();
			list.Show();
			break;
		case 'm':
			result = list.MaxDistance();
			if (result > 0)
				cout << result << endl;
			break;
		case 'n':
			result = list.MinDistance();
			if (result < 1000)
				cout << result << endl;
			break;
		}
	}
}