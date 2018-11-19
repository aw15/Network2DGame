#pragma once
//DWORD WINAPI RecieveProcess(LPVOID arg);
class SceneManager;



class Network
{
public:
	Network();
	~Network();
	bool Initialize(SceneManager*);
	void SendSpawnData(SpawnData& data);
	void SendExitData(int score);

	static DWORD WINAPI RecieveProcess(LPVOID param);
	static void DispatchSignal(const int signal, ClientType* clientData);
	static void ReceiveSpawnData(ClientType* clientData);
private:
	SOCKADDR_IN mServerAddr;
	ClientType mClientData;
	HANDLE mThread;

	SceneManager* mSceneManager;
};

