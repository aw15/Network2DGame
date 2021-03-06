// GameServer.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#define MAX_PLAYER 2


unordered_map<int,SOCKET> gClients;
vector<pair<string, int>> gRank;
bool gServerEnd = false;//InputProcess 스레드에서 엔터키가 눌리면  true로 바뀜
HANDLE gRecieveEvent;


int gClientNumber = 1;
int gTeam = BLUE_TEAM;

DWORD WINAPI ProcessClient(LPVOID arg);
DWORD WINAPI InputProcess(LPVOID arg);

void DispatchSignal(const int signal,const int id);
void ProcessSpawn(const int signal ,const int id);
void ProcessExit(const int signal,const int id);
void ProcessKeyboardInput(const int signal, const int id);

void ReadRankData();
void WriteRankData();

int main()
{
	HWND consoleWindow = GetConsoleWindow();
	//SetWindowPos(consoleWindow, 0, 1500, 200, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	printf("Press Enter for exiting server\n");

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


	gRecieveEvent = CreateEvent(NULL, FALSE, TRUE, NULL);



	auto thread = CreateThread(NULL, NULL, InputProcess, nullptr, NULL,NULL);



	unsigned long on = TRUE;
	retval = ioctlsocket(listenSocket, FIONBIO, &on);
	if (retval == SOCKET_ERROR)
		err_display("ioctlsocket()");


	while(!gServerEnd)
	{
		SOCKET incoming = accept(listenSocket, NULL, NULL);
		if (incoming == INVALID_SOCKET)
			continue;



		unsigned long off = FALSE;
		retval = ioctlsocket(incoming, FIONBIO, &off);
		if (retval == SOCKET_ERROR)
			err_display("ioctlsocket()");


		int id = gClientNumber;
		gClients[id] = incoming;

		printf("==================id : %d connection success========================\n",id);
		CreateThread(NULL, NULL, ProcessClient, (LPVOID)&(id), NULL, NULL);

		gClientNumber++;
	}


	cout << "================Write Ranking Data==================\n" << endl;
	WriteRankData();
	for (auto &client : gClients)
	{
		gClients.erase(client.first);
	}
	printf("QUIT\n");
	closesocket(listenSocket);
	WSACleanup();
    return 0;

}


DWORD WINAPI ProcessClient(LPVOID arg)
{
	int id = *(int*)arg;
	
	int signal = 0;
	int retval = 0;



	cout<<"id : " << id << " client Thread Start" << endl;

	//while (gClientNumber % 2 == 0)
	//{

	//}

	retval = send(gClients[id], (char*)&gTeam, sizeof(gTeam), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("team send()");
		closesocket(gClients[id]);
		gClients[id] = INVALID_SOCKET;
		return 0;
	}

	gTeam == BLUE_TEAM ? gTeam = RED_TEAM : gTeam=BLUE_TEAM;

	while (signal != SIGNAL_EXIT)
	{
		//WaitForSingleObject(gRecieveEvent, 1);
	//	printf("id : %d client Receiving Process\n",id);
		retval = recv(gClients[id], (char*)&signal, sizeof(signal), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("recv");
			printf("signal recv error\n");
			break;
		}
		if (retval == 0)
			continue;
		else
		{
			signal = ntohl(signal);
			DispatchSignal(signal, id);
		}
		//SetEvent(gRecieveEvent);
	}

	closesocket(gClients[id]);
	gClients[id] = INVALID_SOCKET;
	gClients.erase(id);


	return 0;
}

DWORD __stdcall InputProcess(LPVOID arg)
{
	ReadRankData();
	while (true)
	{
		if (kbhit())
		{
			int key = getch();
			if (key == 13)
			{
				gServerEnd = true;
				return 0;
			}
		}
	}

	return 0;
}


void DispatchSignal(const int signal,const int id)
{
	switch (signal)
	{
	case SIGNAL_SPAWN:
		ProcessSpawn(signal, id);
		break;
	case SIGNAL_EXIT:
		ProcessExit(signal, id);
		break;
	case SIGNAL_MOVE:
		ProcessKeyboardInput(signal, id);
		break;
	}
}

void ProcessExit(const int signal,const int id)
{
	int retval;
	char name[NAME_BUFSIZE] = "None";
	int score = -1;
	int state = 0;
	retval = recvn(gClients[id], (char*)&score, sizeof(score), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("exit recv()");
		return;
	}


	retval = recvn(gClients[id], (char*)&state, sizeof(state), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("exit recv()");
		return;
	}

	if (id % 2 == 0)
	{
		for (int i = id; i >= id - 1; i--)
		{
			auto client = gClients[i];
			if (client != INVALID_SOCKET && client != NULL)
			{
				int bigEndianSignal = htonl(signal);
				retval = send(client, (char*)&bigEndianSignal, sizeof(int), 0);
				if (retval == SOCKET_ERROR)
				{
					printf("spawn signal send failed\n");
					return;
				}

				retval = send(client, (char*)&state, sizeof(state), 0);
				if (retval == SOCKET_ERROR)
				{
					printf("spawn data send failed\n");
					return;
				}
			}
		}
	}
	else
	{
		for (int i = id; i <= id + 1; i++)
		{
			auto client = gClients[i];
			if (client != INVALID_SOCKET && client != NULL)
			{
				int bigEndianSignal = htonl(signal);
				retval = send(client, (char*)&bigEndianSignal, sizeof(int), 0);
				if (retval == SOCKET_ERROR)
				{
					printf("spawn signal send failed\n");
					return;
				}

				retval = send(client, (char*)&state, sizeof(state), 0);
				if (retval == SOCKET_ERROR)
				{
					printf("spawn data send failed\n");
					return;
				}
			}
		}
	}


	retval = recvn(gClients[id], (char*)name, NAME_BUFSIZE, 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("exit recv()");
		return;
	}

	//printf(" Name %s\n", name);
	gRank.push_back(make_pair(name, score));
		
}

void ProcessKeyboardInput(const int signal, const int id)
{
	int retval;
	MoveData data;
	while (true)
	{
		retval = recvn(gClients[id], (char*)&data, sizeof(data), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("move recv()");
			break;
		}
		else if (retval == 0)
			break;
		else
		{
			if (id % 2 == 0)
			{
				for (int i = id; i >= id - 1; i--)
				{
					auto client = gClients[i];
					if (client != INVALID_SOCKET && client != NULL)
					{
						int bigEndianSignal = htonl(signal);
						retval = send(client, (char*)&bigEndianSignal, sizeof(int), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn signal send failed\n");
							return;
						}

						retval = send(client, (char*)&data, sizeof(data), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn data send failed\n");
							return;
						}
					}
				}
			}
			else
			{
				for (int i = id; i <= id + 1; i++)
				{
					auto client = gClients[i];
					if (client != INVALID_SOCKET && client != NULL)
					{
						int bigEndianSignal = htonl(signal);
						retval = send(client, (char*)&bigEndianSignal, sizeof(int), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn signal send failed\n");
							return;
						}

						retval = send(client, (char*)&data, sizeof(data), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn data send failed\n");
							return;
						}
					}
				}
			}
			break;
		}
	}


}

void ReadRankData()
{
	ifstream in("rank.txt");
	if (!in||isEmpty(in))
		return;

	int score;
	char name[NAME_BUFSIZE];
	cout << "====================RANK=======================" << endl;
	while (!in.eof())
	{
		in >> name;
		if (strlen(name) < 1)
			break;
		in >> score;
		cout << name << " - " << score << endl;
		gRank.push_back(make_pair(name, score));
	}
	cout << "====================RANK=======================" << endl;
	in.close();
}

void WriteRankData()
{
	ofstream out("rank.txt", ios::trunc);

	sort(gRank.begin(), gRank.end(),[](pair<string, int> a, pair<string, int> b) {
		return a.second > b.second;
	});

	int count = 0;
	cout << "====================RANK=======================" << endl;
	for (auto& data : gRank)
	{
		out << data.first.c_str();
		out << " ";
		out << data.second;
		out << " ";
		cout << data.first.c_str() << " - " << data.second << endl;
		if (count++ > 3)
			break;
	}
	cout << "====================RANK=======================" << endl;
	out.close();
}

void ProcessSpawn(const int signal,const int id)
{
	int retval;
	while (true)
	{
		SpawnData data;
		retval = recvn(gClients[id], (char*)&data, sizeof(SpawnData), 0);


		if (retval == SOCKET_ERROR)
		{
			printf("Spawn Failed\n");
			return;
		}
		else if (retval == 0) break;
		else
		{
			if (id % 2 == 0)
			{
				for (int i = id;i>=id-1;i--)
				{
					auto client = gClients[i];
					if (client != INVALID_SOCKET && client != NULL)
					{
						int bigEndianSignal = htonl(signal);
						retval = send(client, (char*)&bigEndianSignal, sizeof(int), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn signal send failed\n");
							return;
						}

						retval = send(client, (char*)&data, sizeof(data), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn data send failed\n");
							return;
						}
					}
				}
			}
			else
			{
				for (int i = id; i <= id + 1; i++)
				{
					auto client = gClients[i];
					if (client != INVALID_SOCKET && client != NULL)
					{
						int bigEndianSignal = htonl(signal);
						retval = send(client, (char*)&bigEndianSignal, sizeof(int), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn signal send failed\n");
							return;
						}

						retval = send(client, (char*)&data, sizeof(data), 0);
						if (retval == SOCKET_ERROR)
						{
							printf("spawn data send failed\n");
							return;
						}
					}
				}
			}
			break;
		}
	}


	return;
}
