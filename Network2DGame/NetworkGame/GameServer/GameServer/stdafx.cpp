// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// GameServer.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.
void err_quit(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);

		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}

void ToNetwork(SpawnData & data)
{
	data.side = htons(data.side);
	data.type = htons(data.type);
	data.x = data.x;
	data.y = data.y;
}

void ToClient(SpawnData & data)
{
	data.side = ntohs(data.side);
	data.type = ntohs(data.type);
	data.x = data.x;
	data.y = data.y;
}

void PrintData(SpawnData & data)
{
	printf("pos(%f %f) type : %d side : %d\n", data.x, data.y, data.type, data.side);
}


void err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}


void PrintSignal(int signal)
{
	if (signal == SIGNAL_SPAWN)
		printf("spawn signal\n");
	if (signal == SIGNAL_MOVE)
		printf("move signal\n");
	if (signal == SIGNAL_EXIT)
		printf("chat signal\n");
}


bool isEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}