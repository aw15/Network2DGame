// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

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


using namespace std;

#define _USE_MATH_DEFINES
#define PI 3.141
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define ANGLE 3.141592 / 180 // 라디안 = 파이(==180), 파이 / 180 = 1도
#define MAX_ANGLE 360;
#define ROTATION_NONE 0
#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3


#define RECT 0x8000
#define TRIANGLE 0x4000
#define CIRCLE 0x2000
#define WIRE_SPHERE 0x1000
#define WIRE_CUBE 0x0800
#define WIRE_CONE 0x0400
#define WIRE_TEAPOT 0x0200
#define WIRE_TRIANGLE 0x0100

#define SPHERE 0x0080
#define CUBE 0x0040
#define CONE 0x0020
#define TEAPOT 0x0010
#define TORUS 0x0008


struct MousePosition
{
	float x;
	float y;
};

struct Transform
{
	float x;
	float y;
	float z;
	Transform operator-(Transform& param)
	{
		Transform result = {
		x - param.x,
		y - param.y,
		z - param.z
		};
		return result;
	}
	Transform operator+(Transform& param)
	{
		Transform result =
		{
			x + param.x,
			y + param.y,
			z + param.z,
		};
		return result;
	}
	Transform operator*(int param)
	{
		Transform result =
		{
			x * param,
			y * param,
			z * param,
		};
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
