// GameServer.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#define MAX_PLAYER 10

ClientType client[MAX_PLAYER];
HANDLE hThread[MAX_PLAYER];
int id = 0;
int gClientNumber = 0;
DWORD WINAPI ClientProcess(LPVOID arg);
void DispatchSignal(const int signal, ClientType* clientData);
void ProcessSpawn(const int signal , ClientType* clientData);
void ProcessExit(const int signal, ClientType* clientData);

int main()
{
	HWND consoleWindow = GetConsoleWindow();
	//SetWindowPos(consoleWindow, 0, 1500, 200, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2),&wsa) != 0)
		return -1;


	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
		return -1;


	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = ADDR_ANY;
	
	int retval = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	retval = listen(listenSocket, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");


	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		client[i] = { INVALID_SOCKET,-1 };
	}


	while(true)
	{
		SOCKET incoming = accept(listenSocket, NULL,NULL);
		if (incoming == INVALID_SOCKET)
		{
			printf("accept failed\n");
			continue;
		}
	
		if (gClientNumber < MAX_PLAYER)
		{
			printf("connection success\n");
			client[id].socket = incoming;
			client[id].id = id;


			hThread[id] = CreateThread(NULL, NULL, ClientProcess, (LPVOID)&(client[id]), NULL, NULL);

			gClientNumber++;
			id++;
		}
	}

	closesocket(listenSocket);
	WSACleanup();
    return 0;
}


DWORD WINAPI ClientProcess(LPVOID arg)
{
	ClientType* clientData = (ClientType*)arg;
	
	int signal = 0;
	cout << clientData->id << "번 스레드" << endl;
	while (true)
	{
		int retval = recv(clientData->socket, (char*)&signal, sizeof(signal), 0);
		if (retval == SOCKET_ERROR)
		{
			printf("recv error\n");
			break;
		}
		if (retval == 0)
			continue;
		else
		{
			signal = ntohl(signal);
			DispatchSignal(signal, clientData);
		}
	}
	closesocket(clientData->socket);
	clientData->socket = INVALID_SOCKET;


	ExitThread(NULL);
	return 0;
}

void DispatchSignal(const int signal, ClientType* clientData)
{
	switch (signal)
	{
	case SIGNAL_SPAWN:
		ProcessSpawn(signal, clientData);
		break;
	case SIGNAL_EXIT:
		ProcessExit(signal, clientData);
		break;
	}
}

void ProcessExit(const int signal, ClientType* clientData)
{
	int retval;
	while (true)
	{
		int score = 0;
		retval = recvn(clientData->socket, (char*)&score, sizeof(score), 0);
		printf("Exit Signal %d\n",score);
		break;
	}
}

void ProcessSpawn(const int signal, ClientType* clientData)
{
	int retval;
	while (true)
	{
		SpawnData data;
		retval = recvn(clientData->socket, (char*)&data, sizeof(SpawnData), 0);


		if (retval == SOCKET_ERROR)
		{
			printf("Spawn Failed\n");
			return;
		}
		else if (retval == 0) break;
		else
		{
			for (int i = 0; i < gClientNumber; ++i)
			{
				if (client[i].socket != INVALID_SOCKET)
				{
					int bigEndianSignal = htonl(signal);
					retval = send(client[i].socket, (char*)&bigEndianSignal, sizeof(int), 0);
					if (retval == SOCKET_ERROR)
					{
						printf("spawn signal send failed\n");
						return;
					}

					retval = send(client[i].socket, (char*)&data, sizeof(data), 0);
					if (retval == SOCKET_ERROR)
					{
						printf("spawn data send failed\n");
						return;
					}
				}
			}
			break;
		}
	}


	return;
}
