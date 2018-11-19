#pragma once




class Object
{
public:
	//-----------------------------------자신의 화살 리스트
	vector<Bullet*> mArrowList;
	bool isDead = false;
	bool isFired = false;
public:
	Object(Renderer* renderer, const Transform& pos, int type, int team);
	~Object();
	//-------------------------------세트--------------------------------------------------------
	void SetSpeed(const Transform speed) { mSpeed = speed; };
	void Damage(const float amount);
	void SetPosition(const Transform& pos) { mPosition = pos;}
	void SetSize(const float size) { mSize = size; }
	void SetDirection(const Transform& dir) { mDirection = dir; }
	//---------------------------------게트----------------------------------------------
	float GetSize() { return mSize; }
	Transform* GetCollider();
	Transform GetTransform() { return mPosition; };
	int GetType() { return mType; };
	float GetLife() { return mLife; };
	int GetTeam() { return mTeam; };
	float GetDamageCoolTime() { return mDamageCoolTime; }
	Transform GetDir() { return mDirection; }
	//-----------------------------기능함수--------------------------------------------------------
	void MakeArrow();
	void DeleteArrow();
	//--------------------업데이트-----------------------------------------------------------
	virtual void Render(GLuint texture,GLuint);
	virtual void Update();


private:
	Renderer* mRenderer;
	Transform mSpeed;//속도
	Transform mDirection;//진행 방향
	Transform mPosition;//현재 위치
	Transform mCollider[2];

	Color mColor;
	float mSize;
	int mType;
	int mTeam;
	float mLevel;
	//----------------------애니메이션, 파티클--------------------------------------
	float mAnimationIndex = 0;
	int mMaxIndex = 0;
	//수명----------------------------------------------
	float mLife;
	float mLifeTime=0;
	//-----------------------------------화살관련
	float mArrowSpawnTime = 0;
	float mDamageCoolTime = 0;
	float mArrowSpawnCoolTime = 0;
	//----------------------------------- 팀

};

