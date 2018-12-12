// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#include <stdio.h>
#include <tchar.h>
#include <GL/glut.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include<windows.h>
#include<cmath>
#include <functional>
#include <windows.h>
#include <conio.h>
#include "fmod.h"


using namespace std;
#define LOG_3(s,x,y,z) cout<<s<<" "<<x<<" "<<y<<" "<<z<<endl
#define LOG_1(x) cout<<x<<endl


#define BOTTOM 0
#define LEFT 1
#define RIGHT 2
#define BACK 3
#define FRONT 4


#define DISTANCE 100
#define SQUARE(x) (x)*(x)



#define _USE_MATH_DEFINES
#define PI 3.141
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RADIAN 3.141592 / (float)180.0 // 라디안 = 파이(==180), 파이 / 180 = 1도
#define DEGREE 180/3.141592
#define MAX_ANGLE 360;



#define SOUND_NUM 20
#define SIZE 4
#define HEART_NUM 20

struct coordi {
	float x;
	float y;
	float z;

	float size;
	float speed;
	float time = 0;
	float alpha_c = 0;
	float angle = 0;
	float alpha_sign = 1;
	bool on = false;
};


struct Plane
{
	float a;
	float b;
	float c;
	float d;
};



struct Vector3
{
	float x;
	float y;
	float z;
	Vector3 operator-(Vector3& param)
	{
		Vector3 result = {
			x - param.x,
			y - param.y,
			z - param.z
		};
		return result;
	}
	Vector3 operator+(Vector3& param)
	{
		Vector3 result =
		{
			x + param.x,
			y + param.y,
			z + param.z,
		};
		return result;
	}
	Vector3 operator*(Vector3 param)
	{
		Vector3 result =
		{
			x * param.x,
			y * param.y,
			z * param.z,
		};
		return result;
	}
	void Copy(Vector3 param)
	{
		x = param.x;
		y = param.y;
		z = param.z;
	}
	Vector3 Cross(Vector3 param)
	{
		Vector3 result;
		result.x = y*param.z - z*param.y;
		result.y = z*param.x - x*param.z;
		result.z = x*param.y - y*param.x;
		return result;
	}


	void Normalize()
	{
		float length = sqrt(x*x + y*y + z*z);
		x = x / length;
		y = y / length;
		z = z / length;
	}
};

struct Color
{
	float r;
	float g;
	float b;
	float a;
};



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
