#pragma once
class Object;
class Player;
class Network;

class SceneManager
{
public:
	SceneManager(const int side, Network* network);
	~SceneManager();

	void AddObject(float x, float y);
	void NetworkAddObject(const SpawnData& spawnData);
	void TestAddObject(float x, float y);

	void CollisionCheck();
	void EnemyBulletCheck(Object*);
	void AllyBulletCheck(Object*);
	void Update();
	void Render();
	void Delete();
	void CleanUp();
	//GET//////////////////////////////
	STATE GetState();
	int GetScore() { return mScore; }
	//이벤트///////////////////////////
	void KeyInput(unsigned char key);
	void MouseInput(int button, int state, int x, int y);

private:
	GLuint mTexture[10];
	vector<Object*> mAllyList;//유닛들 리스트
	vector<Object*> mEnemyList;//유닛들 리스트
	Player* mPlayer;//플레이어
	Player* mEnemy;//플레이어
	int mSide;

	int mScore = 0;

	//사운드
	Sound* mSound;
	//렌더러
	Renderer* mRenderer;
	
	//시간////////////////////////
	TimePoint mPrevTime;//이전시간
	float mTimeAccumulator=0.f;
	float mSoundTime = 0;//사운드 재생후 흐른 시간
	float mSpawnTime = 2.0f;//유닛생성 후 흐른 시간
	//네트워크//////////////////////
	Network* mNetwork;
};

