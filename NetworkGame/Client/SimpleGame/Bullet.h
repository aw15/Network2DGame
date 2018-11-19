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
	Transform mSpeed;//�ӵ�
	Transform mDirection;//���� ����
	Transform mTransform;//���� ��ġ
	Transform mCollider[2];
	//�ΰ��� ������
	float mLife;
	float mLifeTime = 0;
	float mLevel;
	float mSize;
	int mType;
	int mTeam;
	Color mColor;
	float mDamageCoolTime=0;
	//��ƼŬ
	float mParticleIndex = 0;
	GLuint mParticle;
	
};

