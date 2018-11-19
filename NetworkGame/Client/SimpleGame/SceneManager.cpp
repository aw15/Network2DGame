#include "stdafx.h"
#include "SceneManager.h"



bool BoxCollision(Transform* standard, Transform* target)
{
	//cout <<"standard: "<< standard[0].x <<" "<<standard[1].x <<"target: " <<target[0].x<<" "<<target[1].x << endl;
	bool isX = ((standard[0].x <= target[0].x&&standard[1].x >= target[0].x) || (standard[0].x <= target[1].x&&standard[1].x >= target[1].x));
	bool isY = ((standard[0].y <= target[0].y&&standard[1].y >= target[0].y) || (standard[0].y <= target[1].y&&standard[1].y >= target[1].y));


	return (isX&&isY);
}

SceneManager::SceneManager(const int side, Network* network)
{
	mNetwork = network;

	PrintTeam(side);

	mSide = side;
	mRenderer = new Renderer(WIDTH, HEIGHT);
	if (!mRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	mAllyList.reserve(100);
	mPrevTime = Time::now();

	mPlayer = new Player(mRenderer);

	mEnemy = new Player(mRenderer);


	if (mSide == BLUE_TEAM)
	{
		mPlayer->SetPosition(0, -200, 0);
		mEnemy->SetPosition(0, 200, 0);
	}
	else if (mSide == RED_TEAM)
	{
		mPlayer->SetPosition(0, 200, 0);
		mEnemy->SetPosition(0, -200, 0);
	}
	

	mTexture[TEX_BUILDING1] = mRenderer->CreatePngTexture("./Resource/small2.png");
	mTexture[TEX_BUILDING2] = mRenderer->CreatePngTexture("./Resource/small1.png");//건물
	mTexture[TEX_BACKGROUND] = mRenderer->CreatePngTexture("./Resource/background.png");//배경
	mTexture[TEX_ARCHER] = mRenderer->CreatePngTexture("./Resource/charater.png");//캐릭
	mTexture[TEX_WARRIOR] = mRenderer->CreatePngTexture("./Resource/Warrior.png");//전사
	mTexture[TEX_MAGE] = mRenderer->CreatePngTexture("./Resource/Mage.png");//마법사


	mTexture[TEX_SNOW] = mRenderer->CreatePngTexture("./Resource/snow.png");//눈
	mTexture[TEX_PARTICLE1] = mRenderer->CreatePngTexture("./Resource/flare.png");//파티클
	mTexture[TEX_PARTICLE2] = mRenderer->CreatePngTexture("./Resource/flare2.png");//파티클
	mSound = new Sound();
	
	auto soundBG = mSound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	mSound->PlaySound(soundBG, true, 0.2f);
}


SceneManager::~SceneManager()
{
	delete mRenderer;
}

void SceneManager::AddObject(float x, float y)
{
	bool spawnCondition = false;
	if (mSide == BLUE_TEAM)
		spawnCondition = y <= 0;
	else
		spawnCondition = y >= 0;

	if (mSpawnTime>SPAWN_COOLTIME&&spawnCondition)
	{
		mSpawnTime = 0;
		Transform newPos = { x,y,0 };
		SpawnData data;

		if (rand() % 10 <= 3)
		{
			data.type = OBJECT_WARRIOR;
		}
		else if(rand()%10 < 6 && rand() % 10 > 3)
		{
			data.type = OBJECT_MAGE;
		}
		else
		{
			data.type = OBJECT_ARCHER;
		}


		float dirx = (rand() / float(RAND_MAX)) * 2 - 1;
		float diry = 1 - dirx;



		data.side = mSide;
		data.x = x;
		data.y = y;
		data.dirx = dirx;
		data.diry = diry;

		mNetwork->SendSpawnData(data);
	}
}

void SceneManager::NetworkAddObject(const SpawnData& spawnData)
{

	Transform newPos = { spawnData.x,spawnData.y,0 };

	Object* newObject = nullptr;


	newObject = new Object(mRenderer, newPos, spawnData.type, spawnData.side);

	Transform newDir = { spawnData.dirx, spawnData.diry };

	if (spawnData.side == RED_TEAM && newDir.y > 0)
		newDir.y *= -1;
	newObject->SetDirection(newDir);

	if (spawnData.side == mSide)
	{
		printf("Allyspawn\n");
		mAllyList.push_back(newObject);
	}
	else
	{
		printf("Enemyspawn\n");
		mEnemyList.push_back(newObject);
	}
}

void SceneManager::TestAddObject(float x, float y)
{
	Transform newPos = { x, y,0 };
	Object* newObject = nullptr;

	newObject = new Object(mRenderer, newPos, OBJECT_ARCHER, RED_TEAM);
	newObject->SetDirection({ 0,-1 });
	mEnemyList.push_back(newObject);
}



void SceneManager::CollisionCheck()
{
	bool isCollide = false;

	for (auto& enemy : mEnemyList)
	{
		Transform* standard = enemy->GetCollider();

		for (auto& ally:mAllyList)
		{
			Transform* compare = ally->GetCollider();
			isCollide = BoxCollision(standard, compare);
			if (ally->GetDamageCoolTime() > DAMAGE_COOLTIME && isCollide)
				ally->Damage(DAMAGE);

			if (enemy->GetDamageCoolTime() > DAMAGE_COOLTIME && isCollide)
				enemy->Damage(DAMAGE);
			
			isCollide = false;
		}
	}


	for (auto& enemy : mEnemyList)
	{
		isCollide = BoxCollision(mPlayer->GetCollider(), enemy->GetCollider());
		if (!isCollide)
			continue;
		if(mPlayer->GetDamageCoolTime()>DAMAGE_COOLTIME&&isCollide)
			mPlayer->Damage(DAMAGE);
		if (enemy->GetDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
			enemy->Damage(DAMAGE);
		isCollide = false;

	//	EnemyBulletCheck(enemy);
	}

	for (auto& ally:mAllyList)
	{
		isCollide = BoxCollision(mEnemy->GetCollider(), ally->GetCollider());
		if (!isCollide)
			continue;
		if (mEnemy->GetDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
			mEnemy->Damage(DAMAGE);
		if (ally->GetDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
			ally->Damage(DAMAGE);

		isCollide = false;

		//AllyBulletCheck(ally);
	}
}

void SceneManager::EnemyBulletCheck(Object* object)
{
	bool isCollide = false;
	for (auto& ally:mAllyList)
	{
		for (auto& bullet : object->mArrowList)
		{
			isCollide = BoxCollision(ally->GetCollider(), bullet->GetCollider());

			if (ally->GetDamageCoolTime()> DAMAGE_COOLTIME&&isCollide)
				ally->Damage(DAMAGE);
			if(bullet->getDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
				bullet->Damage(DAMAGE);

			isCollide = false;
		}
	}
}

void SceneManager::AllyBulletCheck(Object* object)
{
	bool isCollide = false;

	for (auto& enemy:mEnemyList)
	{
		for (auto& bullet : object->mArrowList)
		{
			isCollide = BoxCollision(enemy->GetCollider(), bullet->GetCollider());

			if (enemy->GetDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
				enemy->Damage(DAMAGE);
			if (bullet->getDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
				bullet->Damage(DAMAGE);

			isCollide = false;
		}
	}
}

void SceneManager::Update()
{	
	//시간계산---------------------------------------------------
	TimePoint currTime = Time::now();
	float elapsedTime = TimeDuration(currTime - mPrevTime).count();//현재시간 - 이전시간으로 시간차를 구한다.
	mPrevTime = currTime;
	mTimeAccumulator += elapsedTime;
	//	m_soundTime += elapsedTime;//소리가 계속 나면 안되니까 쿨타임
	mSpawnTime += elapsedTime;//유닛 생성을 위한 쿨타임


	if (mTimeAccumulator > TIME_FREQUENCY)
	{
		for (auto object : mAllyList)
		{
			if (object->GetType() != OBJECT_BUILDING)
				object->Update();//업데이트
		}
		for (auto object : mEnemyList)
		{
			if (object->GetType() != OBJECT_BUILDING)
				object->Update();//업데이트
		}
		mPlayer->Update();
		mEnemy->Update();

		mTimeAccumulator -= TIME_FREQUENCY;
		CollisionCheck();
		Delete();//죽은 애들 지우기
	}
}

void SceneManager::Render()
{
	mRenderer->DrawTexturedRect(0, 0, 0, 1000, 1, 1, 1, 1, mTexture[TEX_BACKGROUND], 0.9f);
	for (auto data : mAllyList)
	{
		if (data->GetType() == OBJECT_ARCHER)
			data->Render(mTexture[TEX_ARCHER], mTexture[TEX_PARTICLE1]);
		else if (data->GetType() == OBJECT_WARRIOR)
			data->Render(mTexture[TEX_WARRIOR], mTexture[TEX_PARTICLE1]);
		else if (data->GetType() == OBJECT_MAGE)
			data->Render(mTexture[TEX_MAGE], mTexture[TEX_PARTICLE2]);
		//else
		//	data->RenderBullet(m_texture[TEX_PARTICLE1]);
	}
	for (auto data : mEnemyList)
	{
		if (data->GetType() == OBJECT_ARCHER)
			data->Render(mTexture[TEX_ARCHER], mTexture[TEX_PARTICLE1]);
		else if (data->GetType() == OBJECT_WARRIOR)
			data->Render(mTexture[TEX_WARRIOR], mTexture[TEX_PARTICLE1]);
		else if (data->GetType() == OBJECT_MAGE)
			data->Render(mTexture[TEX_MAGE], mTexture[TEX_PARTICLE2]);
		//else
		//	data->RenderBullet(m_texture[TEX_PARTICLE1]);
	}

	mPlayer->Render(mTexture[TEX_BUILDING1]);
	mEnemy->Render(mTexture[TEX_BUILDING2]);
	
}

void SceneManager::Delete()
{
	for (vector<Object*>::iterator iter = mAllyList.begin();iter!= mAllyList.end();)
	{
		Object* object = *iter;
		if (object->isDead)
		{
			iter = mAllyList.erase(iter);
		}
		else
		{
			for (auto arrowIter =  object->mArrowList.begin();arrowIter!=object->mArrowList.end();)
			{
				Bullet* arrow = *arrowIter;
				if (arrow->isDead)
				{
					delete arrow;
					arrowIter = object->mArrowList.erase(arrowIter);
				}
				else
					arrowIter++;
			}
			++iter;
		}
	}

	for (vector<Object*>::iterator iter = mEnemyList.begin(); iter != mEnemyList.end();)
	{
		Object* object = *iter;
		if (object->isDead)
		{
			mScore += 1;
			iter = mEnemyList.erase(iter);
		}
		else
		{
			for (auto arrowIter = object->mArrowList.begin(); arrowIter != object->mArrowList.end();)
			{
				Bullet* arrow = *arrowIter;
				if (arrow->isDead)
				{
					delete arrow;
					arrowIter = object->mArrowList.erase(arrowIter);
				}
				else
					arrowIter++;
			}
			++iter;
		}
	}
}

STATE SceneManager::GetState()
{
	if (mPlayer->isDead)
		return STATE::lose;
	else if (mEnemy->isDead)
		return STATE::win;
	else
		return STATE::play;
}


void SceneManager::CleanUp()
{
	for (auto iter = mAllyList.begin(); iter != mAllyList.end();)
	{
		(*iter)->DeleteArrow();
		delete (*iter);
		iter = mAllyList.erase(iter);
	}
	for (auto iter = mEnemyList.begin(); iter != mEnemyList.end();)
	{
		(*iter)->DeleteArrow();
		delete (*iter);
		iter = mEnemyList.erase(iter);
	}
	delete mRenderer;
	delete mNetwork;
}

void SceneManager::KeyInput(unsigned char key)
{
	if (key == 'c')
	{
		printf("ChatTest\n");
	}
	if (key == GLUT_KEY_UP)
	{
		mPlayer->Force(0, KEY_FORCE);
	}
	if (key == GLUT_KEY_DOWN)
	{
		mPlayer->Force(0, -KEY_FORCE);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		mPlayer->Force(KEY_FORCE,0);
	}
	if (key == GLUT_KEY_LEFT)
	{
		mPlayer->Force(-KEY_FORCE, 0);
	}
}

void SceneManager::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x = x - (WIDTH / 2);
		y = (HEIGHT / 2) - y;
		AddObject(x, y);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		x = x - (WIDTH / 2);
		y = (HEIGHT / 2) - y;

	
		TestAddObject(x,y);
	}
}




