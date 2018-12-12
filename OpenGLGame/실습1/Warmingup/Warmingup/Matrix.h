#pragma once
class Matrix
{
	friend class Matrix4x4;
private:
	int matrix[3][3];
public:
	Matrix(void);
	Matrix(int(*param)[3]);
	Matrix operator+(Matrix &param);
	Matrix operator-(Matrix &param);
	Matrix operator*(Matrix &param);
	void Show();
	int Determinant();
};