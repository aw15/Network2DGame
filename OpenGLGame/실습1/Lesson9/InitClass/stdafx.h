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
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RECT 0x80
#define TRIANGLE 0x40
#define CIRCLE 0x20
#define POINT_ 0x10

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
};
struct Color
{
	float r;
	float g;
	float b;
	float a;
};


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
