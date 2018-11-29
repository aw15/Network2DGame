#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer* renderer)
{
	mRenderer = renderer;
}


Player::~Player()
{
}

void Player::Render(GLuint texture)
{
	//char s1[10];
	//_itoa_s(mLife - mLifeTime, s1, 10);
	//mRenderer->DrawText(mPosition.x, mPosition.y + mSize / 1.5, GLUT_BITMAP_TIMES_ROMAN_10, 1, 1, 1, s1);
	mRenderer->DrawTexturedRect(mPosition.x, mPosition.y, mPosition.z, mSize, 1, 1, 1, 1, texture, mLevel);
	mRenderer->DrawSolidRectGauge(mPosition.x, mPosition.y + (mSize / 2), mPosition.z, mSize, 2, mColor.r, mColor.g, mColor.b, mColor.a, (mLife - mLifeTime) / mLife, mLevel);
}

void Player::Update()
{
	mDamageCoolTime += TIME_FREQUENCY;
	//mForce = { 0,0,0 };


	////속도의 크기 구하기

	//float velocity = sqrt((mVel.x * mVel.x) + (mVel.y * mVel.y));

	//if (velocity > FLT_EPSILON)//속도가 있으면.
	//{
	//	float gz = GRAVITY * mMass;//중력가속도. 중력 속도 * 질량.
	//	float friction = FRICTION_COEF * gz;//마찰력 값

	//	float frictionVelX, frictionVelY;
	//	frictionVelX = -friction * mVel.x / velocity;
	//	frictionVelY = -friction * mVel.y / velocity;


	//	float frictionAccX, frictionAccY;
	//	frictionAccX = frictionVelX / mMass;
	//	frictionAccY = frictionVelY / mMass;

	//	float afterVelX, afterVelY;
	//	afterVelX = mVel.x + (frictionAccX*TIME_FREQUENCY);
	//	afterVelY = mVel.y + (frictionAccY*TIME_FREQUENCY);

	//	if (afterVelX * mVel.x < 0.0f)
	//		mVel.x = 0.0f;
	//	else
	//		mVel.x = mVel.x + (frictionAccX * TIME_FREQUENCY);

	//	if (afterVelY * mVel.y < 0.0f)
	//		mVel.y = 0.0f;
	//	else
	//		mVel.y = mVel.y + (frictionAccY * TIME_FREQUENCY);
	//}

	//float accX = (mForce.x / mMass);
	//float accY = (mForce.y / mMass);

	//mVel.x = mVel.x + accX * TIME_FREQUENCY;
	//mVel.y = mVel.y + accY * TIME_FREQUENCY;


	//mPosition.x = mPosition.x + (mVel.x*TIME_FREQUENCY);
	//mPosition.y = mPosition.y + (mVel.y*TIME_FREQUENCY);


	//if (mPosition.y >= (HEIGHT / 2 - 10))
	//{
	//	mPosition.y -= 2.0f;
	//	mVel.x = 0;
	//	mVel.y = 0;
	//}
	//else if (mPosition.y <= -(HEIGHT / 2 - 10))
	//{
	//	mPosition.y += 2.0f;
	//	mVel.x = 0;
	//	mVel.y = 0;
	//}
	//else if (mPosition.x >= (WIDTH / 2 - 10))
	//{
	//	mPosition.x -= 2.0f;
	//	mVel.x = 0;
	//	mVel.y = 0;
	//}
	//else if (mPosition.x <= -(WIDTH / 2 - 10))
	//{
	//	mPosition.x += 2.0f;
	//	mVel.x = 0;
	//	mVel.y = 0;
	//}
	mPosition.x += mForce.x;
	mPosition.x += mForce.y;
}

void Player::Damage(const float amount)
{
	mLifeTime += amount;
	if (mLife <= mLifeTime)
	{
		isDead = true;
	}
	mDamageCoolTime = 0;
}

Transform* Player::GetCollider()
{
	mCollider[0].x = mPosition.x - (mSize / 2);
	mCollider[0].y = mPosition.y - (mSize / 2);
	mCollider[0].z = 0;
	mCollider[1].x = mPosition.x + (mSize / 2);
	mCollider[1].y = mPosition.y + (mSize / 2);
	mCollider[1].z = 0;
	return mCollider;
}


