#pragma once
class Object;
class Player;
class Network;
class Scene;

class GameScene :public Scene
{
public:
	GameScene(Renderer* renderer, Network* network);
	~GameScene();

	bool Initialize();

	void AddObject(float x, float y);
	void SendExitData(){ mNetwork->SendExitData(mScore, mState ,mPlayerName); }

	void NetworkAddObject(const SpawnData& spawnData);
	void NetworkMovePlayer(const MoveData& moveData);



	void CollisionCheck();
	void Update();
	void Render();
	void DeleteDeadObject();
	void CleanUp();
	//SET//////////////////////////////
	void SetTeam(const int side) { mSide = side; }
	void SetName(const char* name) { strcpy(mPlayerName, name); }
	void SetState(const int state) { state == STATE::GameWin ? mState = STATE::GameLose : mState = STATE::GameWin; }
	//GET//////////////////////////////
	STATE GetState();
	int GetScore() { return mScore; }
	//�̺�Ʈ///////////////////////////
	void KeyInput(unsigned char key);
	void KeyUpInput(unsigned char key);
	void MouseInput(int button, int state, int x, int y);

private:
	GLuint mPlayerTex;
	GLuint mEnemyTex;
	vector<Object*> mAllyList;//���ֵ� ����Ʈ
	vector<Object*> mEnemyList;//���ֵ� ����Ʈ
	Player* mPlayer;//�÷��̾�
	Player* mEnemy;//�÷��̾�
	unsigned short mSide = BLUE_TEAM;

	int mScore = 0;
	char mPlayerName[NAME_BUFSIZE] = "Leopard";

	//����
	Sound* mSound;

	int movePosition = 0;
	float mTime = 0;

	STATE mState = STATE::GamePlay;
	//�ð�////////////////////////
	TimePoint mPrevTime;//�����ð�
	float mTimeAccumulator=0.f;
	float mSoundTime = 0;//���� ����� �帥 �ð�
	float mSpawnTime = 2.0f;//���ֻ��� �� �帥 �ð�
	//��Ʈ��ũ//////////////////////
	Network* mNetwork;
};
