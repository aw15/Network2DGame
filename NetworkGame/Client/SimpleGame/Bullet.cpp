#include "stdafx.h"
#include "Bullet.h"





Bullet::Bullet(Renderer * renderer, const Transform & pos, int type, int team, Transform* direction)
{
	mTransform = pos;
	mType = type;
	mRenderer = renderer;
	mTeam = team;
	if (team == RED_TEAM)
		mColor = REDTEAM_COLOR;
	else if (team == BLUE_TEAM)
		mColor = BLUETEAM_COLOR;


	if (direction!=nullptr)
	{
		mDirection = *direction;
	}
	else
	{
		if (team == RED_TEAM)
			mDirection = {0,-1};
		else if (team == BLUE_TEAM)
			mDirection = {0,1};
	}

	switch (type)
	{
	case OBJECT_BULLET:
		mSize = 4;
		mLife = 15;
		mSpeed = { 100,100,0 };
		mLevel = 0.3f;
		break;
	case OBJECT_ARROW:
		mSize = 4;
		mLife = 10;
		mSpeed = { 100,100,0 };
		mLevel = 0.4;
		break;
	}
}

Bullet::~Bullet()
{
}

void Bullet::Render(GLuint particle)
{
	if (mType == OBJECT_BULLET)
		mRenderer->DrawParticle(mTransform.x, mTransform.y, mTransform.z, 7, 1, 1, 1, 1, -mDirection.x, -mDirection.y, particle, mParticleIndex, mLevel + 0.1f);
	else
		mRenderer->DrawSolidRect(mTransform.x, mTransform.y, mTransform.z, mSize, mColor.r, mColor.g, mColor.b, mColor.a, mLevel);
}

void Bullet::Update()
{
	mDamageCoolTime += TIME_FREQUENCY;
	mParticleIndex += TIME_FREQUENCY * 0.6;

	mTransform.x += mDirection.x*(mSpeed.x*TIME_FREQUENCY);
	mTransform.y += mDirection.y*(mSpeed.y*TIME_FREQUENCY);
	mTransform.z += mDirection.z*(mSpeed.z*TIME_FREQUENCY);


	if (mTransform.y <= -(HEIGHT / 2) || mTransform.y >= (HEIGHT / 2) || mTransform.x <= -(WIDTH / 2) || mTransform.x >= (WIDTH / 2))
	{
		isDead = true;
	}

}

Transform* Bullet::GetCollider()
{
	mCollider[0].x = mTransform.x - (mSize / 2);
	mCollider[0].y = mTransform.y - (mSize / 2);
	mCollider[0].z = 0;
	mCollider[1].x = mTransform.x + (mSize / 2);
	mCollider[1].y = mTransform.y + (mSize / 2);
	mCollider[1].z = 0;
	return mCollider;
}


void Bullet::Damage(const float amount)
{

	mLifeTime += amount;
	if (mLife <= mLifeTime)
	{
		isDead = true;
	}
	mDamageCoolTime = 0;

}
