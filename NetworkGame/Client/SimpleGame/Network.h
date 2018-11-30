#pragma once
//DWORD WINAPI RecieveProcess(LPVOID arg);
class GameScene;



class Network
{
public:
	Network();
	~Network();
	bool Initialize(GameScene*);
	void SendSpawnData(SpawnData& data);
	void SendExitData(int score, char* name);
	void SendMoveData(MoveData data);
	void SetIP(const char* iptext);

	static DWORD WINAPI RecieveProcess(LPVOID param);
	static void DispatchSignal(const int signal, ClientType* clientData);
	static void ReceiveSpawnData(ClientType* clientData);
	static void ReceiveMoveData(ClientType* clientData);
private:
	SOCKADDR_IN mServerAddr;
	ClientType mClientData;
	HANDLE mThread;

	GameScene* mSceneManager;
	ULONG mIp = inet_addr("127.0.0.1");
};

