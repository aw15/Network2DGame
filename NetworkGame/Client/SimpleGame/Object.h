#pragma once




class Object
{
public:
	//-----------------------------------�ڽ��� ȭ�� ����Ʈ
	vector<Bullet*> mArrowList;
	bool isDead = false;
	bool isFired = false;
public:
	Object(Renderer* renderer, const Transform& pos, int type, int team);
	~Object();
	//-------------------------------��Ʈ--------------------------------------------------------
	void SetSpeed(const Transform speed) { mSpeed = speed; };
	void Damage(const float amount);
	void SetPosition(const Transform& pos) { mPosition = pos;}
	void SetSize(const float size) { mSize = size; }
	void SetDirection(const Transform& dir) { mDirection = dir; }
	//---------------------------------��Ʈ----------------------------------------------
	float GetSize() { return mSize; }
	Transform* GetCollider();
	Transform GetTransform() { return mPosition; };
	int GetType() { return mType; };
	float GetLife() { return mLife; };
	int GetTeam() { return mTeam; };
	float GetDamageCoolTime() { return mDamageCoolTime; }
	Transform GetDir() { return mDirection; }
	//-----------------------------����Լ�--------------------------------------------------------
	void MakeArrow();
	void DeleteArrow();
	//--------------------������Ʈ-----------------------------------------------------------
	virtual void Render(GLuint texture,GLuint);
	virtual void Update();


private:
	Renderer* mRenderer;
	Transform mSpeed;//�ӵ�
	Transform mDirection;//���� ����
	Transform mPosition;//���� ��ġ
	Transform mCollider[2];

	Color mColor;
	float mSize;
	int mType;
	int mTeam;
	float mLevel;
	//----------------------�ִϸ��̼�, ��ƼŬ--------------------------------------
	float mAnimationIndex = 0;
	int mMaxIndex = 0;
	//����----------------------------------------------
	float mLife;
	float mLifeTime=0;
	//-----------------------------------ȭ�����
	float mArrowSpawnTime = 0;
	float mDamageCoolTime = 0;
	float mArrowSpawnCoolTime = 0;
	//----------------------------------- ��

};

