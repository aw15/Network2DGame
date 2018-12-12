#pragma once
class Bullet
{
public:
	bool isDead = false;
public:
	Bullet(Renderer* renderer, const Transform& pos, int type, int team,  Transform* direction = nullptr);
	~Bullet();

	Transform* GetCollider();
	float GetLife() { return mLife; }
	int GetTeam() { return mTeam; }
	float getDamageCoolTime() { return mDamageCoolTime; }

	void Damage(const float amount);
	void Render(GLuint particle);
	void Update();
private:
	Renderer* mRenderer;
	Transform mSpeed;//속도
	Transform mDirection;//진행 방향
	Transform mTransform;//현재 위치
	Transform mCollider[2];
	//인게임 데이터
	float mLife;
	float mLifeTime = 0;
	float mLevel;
	float mSize;
	int mType;
	int mTeam;
	Color mColor;
	float mDamageCoolTime=0;
	//파티클
	float mParticleIndex = 0;
	GLuint mParticle;
	
};

