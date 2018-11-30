#pragma once
class Player
{
public:
	Player(Renderer* renderer);
	~Player();

	virtual void Render(GLuint texture);
	virtual void Update();
public:
	//-------------------------------세트--------------------------------------------------------
	void Damage(const float amount);
	void SetPosition(float x, float y, float z) { mPosition.x = x; mPosition.y = y; mPosition.z = z;}
	void SetSize(const float size) { mSize = size; }
	void Force(float x, float y) { mForce.x += x; mForce.y += y; }
	//-------------------------------GET-----------------------------------------------------------
	//float GetDamageCoolTime() { return mDamageCoolTime; }
	Transform* GetCollider();
public:
	bool isDead=false;
private:
	Renderer* mRenderer = nullptr;
	float mLife = 1000;
	float mLifeTime = 0;
	//float mDamageCoolTime = 0;
	

	Transform mPosition = {0,0,0};
	Transform mCollider[2];
	float mSpeed = 0;
	Transform mForce = { 0,0,0 };
	float mMass = 10.0f;
	Transform mVel = { 0,0,0 };//x속도, y속도

	Color mColor = {1,1,1,1};
	float mSize = 50.0f;
	float mLevel = 0.3f;


};

