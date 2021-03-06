// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include<conio.h>
#include <tchar.h>
#include<iostream>
#include<WinSock2.h>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<fstream>
using namespace std;
#define PORT 9000
#define NAME_BUFSIZE 256


#define OBJECT_ARCHER 0x01
#define OBJECT_WARRIOR 0x02
#define OBJECT_MAGE 0x03


#define SIGNAL_SPAWN 0x01
#define SIGNAL_MOVE 0x02
#define SIGNAL_EXIT 0x03

#define RED_TEAM 1
#define BLUE_TEAM 2



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
	unsigned short type;
	unsigned short side;
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


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
void err_display(const char *msg);

// 소켓 함수 오류 출력 후 종료
void err_quit(const char *msg);

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags);


void PrintData(SpawnData& data);
void PrintSignal(int signal);

void ToNetwork(SpawnData& data);
void ToClient(SpawnData& data);

bool isEmpty(std::ifstream& pFile);