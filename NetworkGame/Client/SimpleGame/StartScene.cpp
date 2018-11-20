#include "stdafx.h"
#include "StartScene.h"


StartScene::StartScene(Renderer* renderer)
{
	mRenderer = renderer;
	mRenderer->CreatePngTexture("./Resource/start.png", "StartPage");
}


StartScene::~StartScene()
{
}

bool StartScene::Initialize()
{
	return true;
}

void StartScene::Render()
{
	mRenderer->DrawTexturedRect(0, 0, 0, 500, 1, 1, 1, 1,
		mRenderer->GetTexture("StartPage"),0.1);
}

void StartScene::Update()
{
}

STATE StartScene::GetState()
{
	return STATE();
}

void StartScene::KeyInput(unsigned char key)
{
}

void StartScene::KeyUpInput(unsigned char key)
{
}

void StartScene::MouseInput(int button, int state, int x, int y)
{
}
