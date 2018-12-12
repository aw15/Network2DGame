#include "stdafx.h"
#include "Object.h"
#define _CRT_SECURE_NO_WARNINGS


Object::Object(Renderer* renderer, const Transform& pos, int type,int team)
{
	mPosition = pos;
	mType = type;
	mRenderer = renderer;
	mTeam = team;
	if (team == RED_TEAM)
		mColor = REDTEAM_COLOR;
	else if (team == BLUE_TEAM)
		mColor = BLUETEAM_COLOR;

	mArrowList.reserve(100);



	switch (type)
	{
	case OBJECT_ARCHER:
		mSize = 50;
		mMaxHp = 300;
		mSpeed = { 100,100,0 };
		mLevel = 0.2;
		mArrowSpawnCoolTime = 1;
		mMaxIndex = 10;
		break;
	case OBJECT_WARRIOR:
		mSize = 100;
		mMaxHp = 300;
		mSpeed = { 40,40,0 };
		mLevel = 0.2f;
		mArrowSpawnCoolTime = 1;
		mMaxIndex = 6;
		break;
	case OBJECT_MAGE:
		mSize = 60;
		mMaxHp = 300;
		mSpeed = { 50,50,0 };
		mLevel = 0.2f;
		mMaxIndex = 7;
		mArrowSpawnCoolTime = 3;
		break;
	}


	
}




//void Object::Damage(const float amount)
//{
//		mLifeTime += amount;
//		if (mLife <= mLifeTime)
//		{
//			isDead = true;
//		}
//		mDamageCoolTime = 0;
//}




Transform* Object::GetCollider()
{
	mCollider[0].x = mPosition.x - (mSize / 1.5);
	mCollider[0].y = mPosition.y - (mSize / 1.5);
	mCollider[0].z = 0;
	mCollider[1].x = mPosition.x + (mSize / 1.5);
	mCollider[1].y = mPosition.y + (mSize / 1.5);
	mCollider[1].z = 0;
	return mCollider;
}

void Object::MakeArrow()
{
		isFired = true;
		mArrowSpawnTime = 0;

		Transform parent = mPosition;

		Bullet* newBullet;

		if (mType == OBJECT_MAGE)
		{
			for (int i = 0; i < 360; i += 30)
			{
				Transform temp = { cos(i*(3.1415/180)),sin(i*(3.1415 / 180)),0 };
				newBullet = new Bullet(mRenderer, parent,  OBJECT_BULLET, mTeam, &temp);
				mArrowList.push_back(newBullet);
			}
		}
		else if(mType == OBJECT_ARCHER)
		{
			newBullet = new Bullet(mRenderer, parent,  OBJECT_ARROW, mTeam);
			mArrowList.push_back(newBullet);
		}
}

void Object::DeleteArrow()
{
	for (auto iter = mArrowList.begin(); iter != mArrowList.end();)
	{
		delete *iter;
		iter = mArrowList.erase(iter);
	}
}

void Object::Render(GLuint texture,GLuint particle)  
{
	
	if (mType == OBJECT_ARCHER)
	{
		mRenderer->DrawSolidRectGauge(mPosition.x, mPosition.y + (mSize), mPosition.z, mSize, 2, mColor.r, mColor.g, mColor.b, mColor.a, (mMaxHp - mCurrentHP) / mMaxHp, mLevel);
		if (mDirection.y > 0)
		{
			
			mRenderer->DrawTexturedRectSeq(mPosition.x, mPosition.y, mPosition.z, mSize, 1, 1, 1, 1, texture, int(mAnimationIndex) % mMaxIndex, 2, 10, 4, mLevel);
		}
		else
		{
			mRenderer->DrawTexturedRectSeq(mPosition.x, mPosition.y, mPosition.z, mSize, 1, 1, 1, 1, texture, int(mAnimationIndex) % mMaxIndex, 0, 10, 4, mLevel);
		}
	}
	else if (mType == OBJECT_WARRIOR)
	{
		mRenderer->DrawSolidRectGauge(mPosition.x, mPosition.y + (20.0f), mPosition.z, mSize, 2, mColor.r, mColor.g, mColor.b, mColor.a, (mMaxHp - mCurrentHP) / mMaxHp, mLevel);	
		if (mDirection.y > 0)
		{
			mRenderer->DrawTexturedRectSeq(mPosition.x, mPosition.y, mPosition.z, mSize, 1, 1, 1, 1, texture, int(mAnimationIndex) % mMaxIndex, 0, 6, 4, mLevel);
		}
		else
		{
			mRenderer->DrawTexturedRectSeq(mPosition.x, mPosition.y, mPosition.z, mSize, 1, 1, 1, 1, texture, int(mAnimationIndex) % mMaxIndex, 2, 6, 4, mLevel);
		}
	}
	else if (mType == OBJECT_MAGE)
	{
		mRenderer->DrawSolidRectGauge(mPosition.x, mPosition.y + (15.0f), mPosition.z, mSize, 2, mColor.r, mColor.g, mColor.b, mColor.a, (mMaxHp - mCurrentHP) / mMaxHp, mLevel);
		if (mDirection.y > 0)
		{
			mRenderer->DrawTexturedRectSeq(mPosition.x, mPosition.y, mPosition.z, mSize, 1, 1, 1, 1, texture, int(mAnimationIndex) % mMaxIndex, 0, 7, 4, mLevel);
		}
		else
		{
			mRenderer->DrawTexturedRectSeq(mPosition.x, mPosition.y, mPosition.z, mSize, 1, 1, 1, 1, texture, int(mAnimationIndex) % mMaxIndex, 2, 7, 4, mLevel);
		}
	}


	for (auto arrow : mArrowList)
		arrow->Render(particle);
	
}
void Object::Update(float eTime)
{
	//if (mArrowSpawnTime >= mArrowSpawnCoolTime)
	//{
	//	MakeArrow();
	//}
	//else if (mType != OBJECT_WARRIOR)
	//{
	//	mArrowSpawnTime += TIME_FREQUENCY;
	//}

	mAnimationIndex += TIME_FREQUENCY * 10;
	

	mPosition.x += mDirection.x*(mSpeed.x*eTime);
	mPosition.y += mDirection.y*(mSpeed.y*eTime);
	mPosition.z += mDirection.z*(mSpeed.z*eTime);

	if (mPosition.y >= (HEIGHT / 2 - 10))
	{
		isDead = true;
		/*mPosition.y = (HEIGHT / 2 - 10);
		mDirection.y *= -1;*/
	}
	if (mPosition.x >= (WIDTH / 2 - 10))
	{
		isDead = true;
	/*	mPosition.x = (WIDTH / 2 - 10);
		mDirection.x *= -1;*/
	}
	if (mPosition.x <= -(WIDTH / 2 - 10))
	{
		isDead = true;
	/*	mPosition.x = -(WIDTH / 2 - 10);
		mDirection.x *= -1;*/
	}
	if (mPosition.y <= -(HEIGHT / 2 - 10))
	{
		isDead = true;
	/*	mPosition.y = -(HEIGHT / 2 - 10);
		mDirection.y *= -1;*/
	}

}




Object::~Object()
{
}
