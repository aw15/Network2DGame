// Warmingup.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include"Matrix.h"
Matrix::Matrix()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matrix[i][j] = 0;
		}
	}
}
	Matrix::Matrix(int(*param)[3])
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				matrix[i][j] = param[i][j];
			}
		}
	}

	Matrix Matrix:: operator+(Matrix &param)
	{
		Matrix result;

		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				result.matrix[row][col] = matrix[row][col] + param.matrix[row][col];

		return result;
	}
	Matrix Matrix:: operator-(Matrix &param)
	{
		Matrix result;

		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				result.matrix[row][col] = matrix[row][col] - param.matrix[row][col];

		return result;
	}
	Matrix Matrix:: operator*(Matrix &param)
	{
		Matrix result; 

		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				for (int k = 0; k < 3; ++k)
					result.matrix[row][col] += matrix[row][k] * param.matrix[k][col];

		return result;
	}
	void Matrix::Show()
	{
		for (int row = 0; row < 3; ++row) {
			for (int col = 0; col < 3; ++col) {
				cout << matrix[row][col]<<" ";
			}
			cout << endl;
		}
			
	}
	int Matrix::Determinant()
	{
		return matrix[0][0] * matrix[1][1] * matrix[2][2] + 
			matrix[0][1] * matrix[1][2] * matrix[2][0]+
			matrix[0][2]*matrix[1][0]*matrix[2][1]-
			matrix[0][2]*matrix[1][1]*matrix[2][0]-
			matrix[0][1]*matrix[1][0]*matrix[2][2]-
			matrix[0][0]*matrix[1][2]*matrix[2][1];
	}
	class Matrix4x4
	{
	public:
		int matrix[4][4];
		void transform(Matrix &param){
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					matrix[i][j] = param.matrix[i][j];
				}
			}
			matrix[0][3] = 0, matrix[1][3] = 0, matrix[2][3] = 0;
			matrix[3][0] = 0, matrix[3][1] = 0, matrix[3][2] = 0;
			matrix[3][3] = 1;
		}
		void Show() {
			for (int row = 0; row < 4; ++row) {
				for (int col = 0; col < 4; ++col) {
					cout << matrix[row][col] << " ";
				}
				cout << endl;
			}
		}
	};
int main()
{
	int A[3][3] =
	{ {0,0,1},
	{1,1,1},
	{0,1,0} };
	int B[3][3] =
	{ { 1,0,1 },
	{ 0,0,0 },
	{ 0,1,0 } };
	Matrix a(A);
	Matrix b(B);
	Matrix result;
	Matrix4x4 result4x4;
	cout << "m:곱셈 a:덧셈 d:뺄셈 r:행렬식 h:4x4변환" << endl;
	cout << "================a======================"<<endl;
	a.Show();
	cout << "================b======================"<<endl;
	b.Show();
	while (true)
	{
		char select;
		cin >> select;
		select=toupper(select);
		cout << "===========result==============" << endl;
		switch (select)
		{
		case'M':
			result = a*b;
			result.Show();
			break;

		case'A':
			result = a+b;
			result.Show();
			break;
		case'D':
			result = a-b;
			result.Show();
			break;
		case'R':
			cout << a.Determinant();
			break;
		case'H':
			result4x4.transform(a);
			result4x4.Show();
			break;
		}
	}
    return 0;
}