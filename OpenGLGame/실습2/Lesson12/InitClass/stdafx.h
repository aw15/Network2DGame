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
#define ROTATION_X 1
#define ROTATION_Y 2
#define ROTATION_Z 3


#define RECT 0x80
#define TRIANGLE 0x40
#define CIRCLE 0x20
#define LINE 0x10
#define POINT_ 0x08
#define SIN 0x04
#define TONADO 0x02
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
