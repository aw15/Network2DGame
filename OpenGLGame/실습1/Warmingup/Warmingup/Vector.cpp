#include "stdafx.h"

class Vector {
public:
	float x;
	float y;
	float z;
	Vector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector() { x = 0.f; y = 0.f; z = 0.f; }
	Vector operator+(const Vector& param)
	{
		Vector result;
		result.x = x + param.x;
		result.y = y + param.y;
		result.z = z + param.z;
		return result;
	}
	Vector operator-(const Vector& param)
	{
		Vector result;
		result.x = x - param.x;
		result.y = y - param.y;
		result.z = z - param.z;
		return result;
	}
	float Dot(const Vector& param)
	{
		float result;
		result = x * param.x+ y * param.y+ z * param.z;
		return result;
	}
	Vector Cross(const Vector& param)
	{
		Vector result;
		result.x = (y * param.z)-(z*param.y);
		result.y = (z * param.x) - (x*param.z);
		result.z = (x * param.y) - (y*param.x);
		return result;
	}
	pair<float,float> Length(const Vector& param)
	{
		pair<float, float> result;
		result.first = sqrt(x + y + z);
		result.second = sqrt(param.x + param.y + param.z);
		return result;
	}
};


int main()
{
	float x, y, z;
	cout << "백터 A 입력: ";
	cin >> x >> y >> z;
	Vector vA(x, y, z);
	cout << "백터 B 입력: ";
	cin >> x >> y >> z;
	Vector vB(x, y, z);
	
	char selection;
	Vector result;
	float fResult;
	pair<float, float> pResult;
	while (true)
	{
		cout << "+:더하기 -:빼기 c:내적 d:외적 l:길이"<<endl;
		cout << "=================================\n";
		cin >> selection;
		switch (selection)
		{
		case '+':
			result = vA + vB;
			printf("결과 : (%f, %f, %f)\n", result.x, result.y, result. z);
			break;
		case '-':
			result = vA - vB;
			printf("결과 : (%f, %f, %f)\n", result.x, result.y, result. z);
			break;
		case 'c':
			result = vA.Cross(vB);
			printf("결과 : (%f, %f, %f)\n", result.x, result.y, result. z);
			break;
		case 'd':
			fResult = vA.Dot(vB);
			printf("결과 : %f\n", fResult);
			break;
		case 'l':
			pResult = vA.Length(vB);
			printf("A : %f, B : %f\n", pResult.first,pResult.second);
			break;
		}
	}
}