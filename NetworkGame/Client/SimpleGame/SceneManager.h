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
	//�̺�Ʈ///////////////////////////
	void KeyInput(unsigned char key);
	void MouseInput(int button, int state, int x, int y);

private:
	GLuint mTexture[10];
	vector<Object*> mAllyList;//���ֵ� ����Ʈ
	vector<Object*> mEnemyList;//���ֵ� ����Ʈ
	Player* mPlayer;//�÷��̾�
	Player* mEnemy;//�÷��̾�
	int mSide;

	int mScore = 0;

	//����
	Sound* mSound;
	//������
	Renderer* mRenderer;
	
	//�ð�////////////////////////
	TimePoint mPrevTime;//�����ð�
	float mTimeAccumulator=0.f;
	float mSoundTime = 0;//���� ����� �帥 �ð�
	float mSpawnTime = 2.0f;//���ֻ��� �� �帥 �ð�
	//��Ʈ��ũ//////////////////////
	Network* mNetwork;
};

