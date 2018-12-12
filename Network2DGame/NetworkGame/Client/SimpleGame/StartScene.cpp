#include "stdafx.h"
#include "StartScene.h"


StartScene::StartScene(Renderer* renderer)
{
	mRenderer = renderer;
	mRenderer->CreatePngTexture("./Resource/start.png", "StartPage");
}


StartScene::~StartScene()
{
	printf("Hello!\n");
}

bool StartScene::Initialize()
{
	return true;
}

void StartScene::Render()
{
	mRenderer->DrawTexturedRect(0, 0, 0, WIDTH, 1, 1, 1, 1,
		mRenderer->GetTexture("StartPage"),0.1);
}

void StartScene::Update()
{
}

STATE StartScene::GetState()
{
	return mState;
}

void StartScene::KeyInput(unsigned char key)
{
	if (key == ' ')
		mState = STATE::Start;
}

void StartScene::KeyUpInput(unsigned char key)
{
}

void StartScene::MouseInput(int button, int state, int x, int y)
{
}

void StartScene::CleanUp()
{
}
