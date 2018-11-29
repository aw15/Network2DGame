#include "stdafx.h"
#include "Network.h"


GameScene* mSceneManagerForNetwork;

DWORD WINAPI Network::RecieveProcess(LPVOID param)
{
	ClientType* clientData = (ClientType*)param;


	int signal = 0;
	while (true)
	{
		int retval = recv(clientData->socket, (char*)&signal, sizeof(signal), 0);
		signal = ntohl(signal);
		//PrintSignal(signal);
		if (retval == SOCKET_ERROR)
		{
			printf("spawn recv socket error\n");
			break;
		}
		else if (retval == 0)
			continue;
		else
		{
			Network::DispatchSignal(signal,clientData);
		}
	}

	return 0;
}

void Network::DispatchSignal(const int signal, ClientType* clientData)
{
	switch (signal)
	{
	case SIGNAL_SPAWN:
		Network::ReceiveSpawnData(clientData);
		break;
	case SIGNAL_MOVE:
		Network::ReceiveMoveData(clientData);
		break;
	}
}

void Network::ReceiveSpawnData(ClientType* clientData)
{

	SpawnData data;
	ZeroMemory(&data, sizeof(data));
	while (true)
	{
		int retval = recvn(clientData->socket, (char*)&data, sizeof(data), 0);
		if (retval == SOCKET_ERROR)
		{
			printf("spawn recv socket error\n");
			break;
		}
		else if (retval == 0)
			continue;
		else
		{
			mSceneManagerForNetwork->NetworkAddObject(data);
			break;
		}
	}
}

void Network::ReceiveMoveData(ClientType* clientData)
{

	MoveData data;
	ZeroMemory(&data, sizeof(data));
	while (true)
	{
		int retval = recvn(clientData->socket, (char*)&data, sizeof(data), 0);
		if (retval == SOCKET_ERROR)
		{
			printf("spawn recv socket error\n");
			break;
		}
		else if (retval == 0)
			continue;
		else
		{
			mSceneManagerForNetwork->NetworkMovePlayer(data);
			break;
		}
	}
}

Network::Network()
{

}

Network::~Network()
{
	closesocket(mClientData.socket);
	WSACleanup();
}

bool Network::Initialize(GameScene* sceneManager)
{
	mSceneManagerForNetwork = sceneManager;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return false;

	//////NETWORK
	mServerAddr.sin_family = AF_INET;
	mServerAddr.sin_port = htons(9000);
	mServerAddr.sin_addr.s_addr = mIp;


	mClientData.socket = socket(AF_INET, SOCK_STREAM, 0);
	if (mClientData.socket == INVALID_SOCKET)
	{
		return false;
	}

	int retval = connect(mClientData.socket, (SOCKADDR*)&mServerAddr, sizeof(mServerAddr));
	if (retval == SOCKET_ERROR)
	{
		closesocket(mClientData.socket);
		mClientData.socket = INVALID_SOCKET;
		return false;
	}

	while (true)
	{
		int side = BLUE_TEAM;
		retval = recv(mClientData.socket, (char*)&side, sizeof(side), 0);
		if (retval == SOCKET_ERROR)
		{
			err_quit("side recv error");
			return false;
		}
		else if (retval == 0)
		{
			break;
		}
		else
		{
			mSceneManagerForNetwork->SetTeam(side);
			PrintTeam(side);
			break;
		}
	}

	mThread = CreateThread(NULL, NULL, RecieveProcess, (LPVOID)&mClientData, NULL, NULL);
	if (mThread == NULL)
		return false;



	return true;
}



void Network::SendSpawnData(SpawnData& data)
{
	int signal = htonl(SIGNAL_SPAWN);
	int retval = 0;

	retval = send(mClientData.socket, (char*)&signal, sizeof(signal), 0);
	if (retval == SOCKET_ERROR)
	{
		printf("spawn send socket error\n");
		return;
	}

	send(mClientData.socket, (char*)&data, sizeof(SpawnData), 0);
	if (retval == SOCKET_ERROR)
	{
		printf("spawn send socket error\n");
		return;
	}

	return;
}

void Network::SendExitData(int score,char* name)
{
	int signal = htonl(SIGNAL_EXIT);
	int retval = 0;

	retval = send(mClientData.socket, (char*)&signal, sizeof(signal), 0);
	if (retval == SOCKET_ERROR)
	{
		printf("spawn send socket error\n");
		return;
	}
	retval = send(mClientData.socket, (char*)&score, sizeof(score), 0);
	if (retval == SOCKET_ERROR)
	{
		printf("spawn send socket error\n");
		return;
	}
	retval = send(mClientData.socket, (char*)name, NAME_BUFSIZE, 0);
	if (retval == SOCKET_ERROR)
	{
		printf("spawn send socket error\n");
		return;
	}
}

void Network::SendMoveData(MoveData data)
{
	int signal = htonl(SIGNAL_MOVE);
	

	int retval = send(mClientData.socket, (char*)&signal, sizeof(signal), 0);
	if (retval == SOCKET_ERROR)
	{
		printf("spawn send socket error\n");
		return;
	}
	retval = send(mClientData.socket, (char*)&data, sizeof(data), 0);
	if (retval == SOCKET_ERROR)
	{
		printf("spawn send socket error\n");
		return;
	}
}

void Network::SetIP(const char * iptext)
{
	mIp = inet_addr(iptext);
}


