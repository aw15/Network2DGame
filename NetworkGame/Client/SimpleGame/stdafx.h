#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>

#include<iostream>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<random>

#include<WinSock2.h>
#include<Windows.h>
#include<chrono>

#define TEX_BUILDING1 0 
#define TEX_BUILDING2 1
#define TEX_BACKGROUND 2
#define TEX_ARCHER 3
#define TEX_WARRIOR 4
#define TEX_MAGE 5
#define TEX_SNOW 6
#define TEX_PARTICLE1 7
#define TEX_PARTICLE2 8

#define WIDTH 500
#define HEIGHT 700


#define OBJECT_ARCHER 0x01
#define OBJECT_WARRIOR 0x02
#define OBJECT_MAGE 0x03

#define OBJECT_BUILDING 0x04
#define OBJECT_BULLET 0x05
#define OBJECT_ARROW 0x06

#define RED_TEAM 1
#define BLUE_TEAM 2

#define SPAWN_COOLTIME 1.0f
#define SOUND_COOLTIME 1.0f
#define ARROW_SPAWNTIME 1.0f

#define DAMAGE_COOLTIME 1.0f
#define DAMAGE 100

#define KEY_FORCE 1
#define GRAVITY 9.8f
#define FRICTION_COEF 2.0f


enum STATE
{
	GameWin =0,
	GameLose,
	GamePlay,
	Start,
	EndWin,
	EndLose,
	EndQuit
};

#define NAME_BUFSIZE 256
//NETWORK CONSTANTS
#define SIGNAL_SPAWN 0x01
#define SIGNAL_MOVE 0x02
#define SIGNAL_EXIT 0x03



using namespace std;

using Time = chrono::high_resolution_clock;
using TimePoint = Time::time_point;
using TimeDuration = chrono::duration<float>;
using USHORT = unsigned short;

const float TIME_FREQUENCY = 1 / 120.f;



struct Transform
{
	float x;
	float y;
	float z;
	Transform operator-(float param)
	{
		Transform result;
		result.x = x - param;
		result.y = y - param;
		result.z = z - param;
		return result;
	}
	bool operator==(Transform& param)
	{
		if (x == param.x&&y == param.y&&z == param.z)
		{
			return true;
		}
		return false;
	}
};
struct Color
{
	float r;
	float g;
	float b;
	float a;
};


#pragma pack(1)
struct ClientType
{
	SOCKET socket;
	int id;
};
#pragma pack()

#pragma pack(1)
struct SpawnData
{
	float dirx;
	float diry;
	float x;
	float y;
	USHORT type;
	USHORT side;
};
#pragma pack()

#pragma pack(1)
struct MoveData
{
	unsigned short side;
	int forceX;
	int forceY;
};
#pragma pack()

const Color REDTEAM_COLOR = { 1,0,0,1 };
const Color BLUETEAM_COLOR = { 0,0,1,1 } ;

#include "Renderer.h"
#include"Sound.h"
#include"Scene.h"
#include"Network.h"
#include"GameScene.h"
#include"StartScene.h"
#include"EndScene.h"
#include"Bullet.h"
#include"Player.h"
#include"Object.h"


void err_display(const char *msg);

// 소켓 함수 오류 출력 후 종료
void err_quit(const char *msg);

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags);

void PrintData(SpawnData& data);
void PrintSignal(int signal);
void PrintTeam(UINT team);

//void ToNetwork(SpawnData& data);
//void ToClient(SpawnData& data);