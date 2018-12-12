#include "stdafx.h"

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

void PrintData(SpawnData & data)
{
	printf("pos(%f %f) type : %d side : %d\n", data.x, data.y, data.type, data.side);
}

void PrintSignal(int signal)
{
	if (signal == SIGNAL_SPAWN)
		printf("spawn signal\n");
	if (signal == SIGNAL_EXIT)
		printf("chat signal\n");
}

void PrintTeam(UINT team)
{
	if (team == RED_TEAM)
	{
		printf("i'm red!\n");
	}
	if (team == BLUE_TEAM)
	{
		printf("i'm blue!\n");
	}
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
