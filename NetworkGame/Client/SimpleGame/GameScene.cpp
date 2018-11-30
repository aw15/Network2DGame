#include "stdafx.h"
#include "GameScene.h"



bool BoxCollision(Transform* standard, Transform* target)
{
	//cout <<"standard: "<< standard[0].x <<" "<<standard[1].x <<"target: " <<target[0].x<<" "<<target[1].x << endl;
	bool isX = ((standard[0].x <= target[0].x&&standard[1].x >= target[0].x) || (standard[0].x <= target[1].x&&standard[1].x >= target[1].x));
	bool isY = ((standard[0].y <= target[0].y&&standard[1].y >= target[0].y) || (standard[0].y <= target[1].y&&standard[1].y >= target[1].y));


	return (isX&&isY);
}

GameScene::GameScene(Renderer* renderer , Network* network)
{
	mNetwork = network;

	mRenderer = renderer;

	mAllyList.reserve(20);
	mEnemyList.reserve(20);
	mPrevTime = Time::now();



	mRenderer->CreatePngTexture("./Resource/background.png","BackGround");//배경
	mRenderer->CreatePngTexture("./Resource/charater.png","Archer");//캐릭
	mRenderer->CreatePngTexture("./Resource/Warrior.png","Warrior");//전사
	mRenderer->CreatePngTexture("./Resource/Mage.png","Mage");//마법사


	mRenderer->CreatePngTexture("./Resource/snow.png","Snow");//눈
	mRenderer->CreatePngTexture("./Resource/flare.png","Particle1");//파티클
	mRenderer->CreatePngTexture("./Resource/flare2.png","Particle2");//파티클



	mSound = new Sound();
	auto soundBG = mSound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	mSound->PlaySound(soundBG, true, 0.2f);
}


GameScene::~GameScene()
{
	CleanUp();
}

bool GameScene::Initialize()
{
	mPlayer = new Player(mRenderer);

	mEnemy = new Player(mRenderer);



	if (mSide == BLUE_TEAM)
	{
		mPlayer->SetPosition(0, -200, 0);
		mEnemy->SetPosition(0, 200, 0);
		mRenderer->CreatePngTexture("./Resource/small2.png", "Player");
		mRenderer->CreatePngTexture("./Resource/small1.png", "Enemy");//건물
	}
	else if (mSide == RED_TEAM)
	{
		mPlayer->SetPosition(0, 200, 0);
		mEnemy->SetPosition(0, -200, 0);
		mRenderer->CreatePngTexture("./Resource/small2.png", "Enemy");
		mRenderer->CreatePngTexture("./Resource/small1.png", "Player");//건물
	}

	return true;
}

void GameScene::AddObject(float x, float y)
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

void GameScene::NetworkAddObject(const SpawnData& spawnData)
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
		mAllyList.push_back(newObject);
	}
	else
	{
		mEnemyList.push_back(newObject);
	}
}

void GameScene::NetworkMovePlayer(const MoveData & moveData)
{
	moveData.side == mSide ? mPlayer->Force(moveData.forceX, moveData.forceY) : mEnemy->Force(moveData.forceX, moveData.forceY);
}

void GameScene::TestAddObject(float x, float y)
{
	Transform newPos = { x, y,0 };
	Object* newObject = nullptr;

	newObject = new Object(mRenderer, newPos, OBJECT_ARCHER, RED_TEAM);
	newObject->SetDirection({ 0,-1 });
	mEnemyList.push_back(newObject);
}



void GameScene::CollisionCheck()
{

	//for (auto& enemy : mEnemyList)
	//{
	//	Transform* standard = enemy->GetCollider();

	//	for (auto& ally : mAllyList)
	//	{
	//		Transform* compare = ally->GetCollider();
	//		if (BoxCollision(standard, compare))
	//		{
	//			ally->isDead = true;
	//			enemy->isDead = true;
	//			break;
	//		}
	//	}
	//}

	for (auto& enemy : mEnemyList)
	{
		if (BoxCollision(mPlayer->GetCollider(), enemy->GetCollider()))
		{
			enemy->isDead = true;
			mPlayer->Damage(DAMAGE);
		}
	}

	for (auto& ally:mAllyList)
	{
		if (BoxCollision(mEnemy->GetCollider(), ally->GetCollider()))
		{
			ally->isDead = true;
			mEnemy->Damage(DAMAGE);
		}
	}
}

//void GameScene::EnemyBulletCheck(Object* object)
//{
//	bool isCollide = false;
//	for (auto& ally:mAllyList)
//	{
//		for (auto& bullet : object->mArrowList)
//		{
//			isCollide = BoxCollision(ally->GetCollider(), bullet->GetCollider());
//
//			if (ally->GetDamageCoolTime()> DAMAGE_COOLTIME&&isCollide)
//				ally->Damage(DAMAGE);
//			if(bullet->getDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
//				bullet->Damage(DAMAGE);
//
//			isCollide = false;
//		}
//	}
//}
//
//void GameScene::AllyBulletCheck(Object* object)
//{
//	bool isCollide = false;
//
//	for (auto& enemy:mEnemyList)
//	{
//		for (auto& bullet : object->mArrowList)
//		{
//			isCollide = BoxCollision(enemy->GetCollider(), bullet->GetCollider());
//
//			if (enemy->GetDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
//				enemy->Damage(DAMAGE);
//			if (bullet->getDamageCoolTime() > DAMAGE_COOLTIME&&isCollide)
//				bullet->Damage(DAMAGE);
//
//			isCollide = false;
//		}
//	}
//}

void GameScene::Update()
{	
	//시간계산---------------------------------------------------
	TimePoint currTime = Time::now();
	float elapsedTime = TimeDuration(currTime - mPrevTime).count();//현재시간 - 이전시간으로 시간차를 구한다.
	mPrevTime = currTime;
	mTimeAccumulator += elapsedTime;
	//	m_soundTime += elapsedTime;//소리가 계속 나면 안되니까 쿨타임
	mSpawnTime += elapsedTime;//유닛 생성을 위한 쿨타임

	while (mTimeAccumulator > TIME_FREQUENCY)
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
		DeleteDeadObject();//죽은 애들 지우기
	}
	if (mPlayer->isDead)
		mState = STATE::GameLose;
	else if (mEnemy->isDead)
		mState = STATE::GameWin;
	if (mState == STATE::GameWin || mState == STATE::GameLose)
	{
		mNetwork->SendExitData(mScore, mPlayerName);
	}
}

void GameScene::Render()
{
	mRenderer->DrawTexturedRect(0, 0, 0, 1000, 1, 1, 1, 1, mRenderer->GetTexture("BackGround"), 0.9f);
	for (auto data : mAllyList)
	{
		if (data->GetType() == OBJECT_ARCHER)
			data->Render(mRenderer->GetTexture("Archer"), mRenderer->GetTexture("Particle1"));
		else if (data->GetType() == OBJECT_WARRIOR)
			data->Render(mRenderer->GetTexture("Warrior"), mRenderer->GetTexture("Particle1"));
		else if (data->GetType() == OBJECT_MAGE)
			data->Render(mRenderer->GetTexture("Mage"), mRenderer->GetTexture("Particle2"));
	}
	for (auto data : mEnemyList)
	{
		if (data->GetType() == OBJECT_ARCHER)
			data->Render(mRenderer->GetTexture("Archer"), mRenderer->GetTexture("Particle1"));
		else if (data->GetType() == OBJECT_WARRIOR)
			data->Render(mRenderer->GetTexture("Warrior"), mRenderer->GetTexture("Particle1"));
		else if (data->GetType() == OBJECT_MAGE)
			data->Render(mRenderer->GetTexture("Mage"), mRenderer->GetTexture("Particle2"));
	}

	mPlayer->Render(mRenderer->GetTexture("Player"));
	mEnemy->Render(mRenderer->GetTexture("Enemy"));
	
	
}

void GameScene::DeleteDeadObject()
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
			iter++;
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
			iter++;
		}
	}
}

STATE GameScene::GetState()
{
	return mState;
}


void GameScene::CleanUp()
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
}

void GameScene::KeyInput(unsigned char key)
{
	if (key == 'w')
	{
		//mPlayer->Force(0, KEY_FORCE);
		mNetwork->SendMoveData(MoveData{ mSide,0,KEY_FORCE });
	}
	else if (key == 's')
	{
		//mPlayer->Force(0, -KEY_FORCE);
		mNetwork->SendMoveData(MoveData{ mSide, 0,-KEY_FORCE });
	}
	else if (key == 'd')
	{
		//mPlayer->Force(KEY_FORCE,0);
		mNetwork->SendMoveData(MoveData{ mSide, KEY_FORCE,0});
	}
	else if (key == 'a')
	{
		//mPlayer->Force(-KEY_FORCE, 0);
		mNetwork->SendMoveData(MoveData{mSide, -KEY_FORCE,0 });
	}
	else if (key == 'q')
	{
		mState = STATE::GameLose;
	}
}

void GameScene::KeyUpInput(unsigned char key)
{
	//if (key == 'w')
	//{
	//	//mPlayer->Force(0, -KEY_FORCE);
	//	mNetwork->SendMoveData(MoveData{ mSide, 0, -KEY_FORCE });
	//}
	//else if (key == 's')
	//{
	//	//mPlayer->Force(0, KEY_FORCE);
	//	mNetwork->SendMoveData(MoveData{ mSide, 0,KEY_FORCE });
	//}
	//else if (key == 'd')
	//{
	//	//mPlayer->Force(-KEY_FORCE, 0);
	//	mNetwork->SendMoveData(MoveData{ mSide, -KEY_FORCE,0 });
	//}
	//else if (key == 'a')
	//{
	//	//mPlayer->Force(KEY_FORCE, 0);
	//	mNetwork->SendMoveData(MoveData{ mSide, KEY_FORCE, 0 });
	//}
}

void GameScene::MouseInput(int button, int state, int x, int y)
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




