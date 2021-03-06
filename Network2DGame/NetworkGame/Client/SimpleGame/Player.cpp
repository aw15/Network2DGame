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
	mRenderer->DrawSolidRectGauge(mPosition.x, mPosition.y + (mSize / 2), mPosition.z, mSize, 2, mColor.r, mColor.g, mColor.b, mColor.a, (mTotalLife - mCurrentLife) / (float)mTotalLife, mLevel);
}

void Player::Update(float eTime)
{
	
	mPosition.x += mForce.x*TIME_FREQUENCY;
	mPosition.y += mForce.y*TIME_FREQUENCY;



	if (mPosition.y >= (HEIGHT / 2 - 10) ||
		mPosition.y <= -(HEIGHT / 2 - 10) ||
		mPosition.x >= (WIDTH / 2 - 10) ||
		mPosition.x <= -(WIDTH / 2 - 10)
		)
	{

		mPosition.x -= mForce.x*TIME_FREQUENCY;
		mPosition.y -= mForce.y*TIME_FREQUENCY;
	}

	//mForce.x = 0;
	//mForce.y = 0;
}

void Player::Damage(const int amount)
{
	mCurrentLife += amount;
	if (mTotalLife <= mCurrentLife)
	{
		isDead = true;
	}
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


