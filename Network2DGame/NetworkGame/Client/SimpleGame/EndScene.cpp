#include "stdafx.h"
#include "EndScene.h"



EndScene::EndScene(Renderer * renderer)
{
	mRenderer = renderer;
	mRenderer->CreatePngTexture("./Resource/win.png", "WinPage");
	mRenderer->CreatePngTexture("./Resource/lose.png", "LosePage");
}

EndScene::~EndScene()
{
}

bool EndScene::Initialize()
{
	return false;
}

void EndScene::Render()
{
	if (mState == STATE::EndWin)
	{
		mRenderer->DrawTexturedRect(0, 0, 0, 100, 1, 1, 1, 1, mRenderer->GetTexture("WinPage"),0.1);
	}
	if (mState == STATE::EndLose)
	{
		mRenderer->DrawTexturedRect(0, 0, 0, 100, 1, 1, 1, 1, mRenderer->GetTexture("LosePage"), 0.1);
	}
}

void EndScene::Update()
{
}

STATE EndScene::GetState()
{
	return mState;
}

void EndScene::KeyInput(unsigned char key)
{
	if (key == ' ')
		mState = STATE::EndQuit;
}

void EndScene::KeyUpInput(unsigned char key)
{
}

void EndScene::MouseInput(int button, int state, int x, int y)
{
}

void EndScene::CleanUp()
{
}
