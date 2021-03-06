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
	//이벤트///////////////////////////
	void KeyInput(unsigned char key);
	void KeyUpInput(unsigned char key);
	void MouseInput(int button, int state, int x, int y);

	//void EnemyBulletCheck(Object* object);
	//void AllyBulletCheck(Object* object);

private:
	GLuint mPlayerTex;
	GLuint mEnemyTex;
	vector<Object*> mAllyList;//유닛들 리스트
	vector<Object*> mEnemyList;//유닛들 리스트
	Player* mPlayer;//플레이어
	Player* mEnemy;//플레이어
	unsigned short mSide = BLUE_TEAM;

	int mScore = 0;
	char mPlayerName[NAME_BUFSIZE] = "Leopard";

	//사운드
	Sound* mSound;

	int movePosition = 0;
	float mTime = 0;

	STATE mState = STATE::GamePlay;
	//시간////////////////////////
	TimePoint mPrevTime;//이전시간
	float mTimeAccumulator=0.f;
	float mSoundTime = 0;//사운드 재생후 흐른 시간
	float mSpawnTime = 2.0f;//유닛생성 후 흐른 시간
	//네트워크//////////////////////
	Network* mNetwork;
};

