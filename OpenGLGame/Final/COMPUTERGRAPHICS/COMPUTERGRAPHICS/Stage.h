#pragma once
#include"Pyramid.h"
#include"Player.h"
#include"effect.h"


void Draw_Background1();
void Draw_Background2();
void Draw_Background3();
void Draw_Background4();
void Draw_Background5();
void Draw_Background6();
void Draw_Background7();
void Draw_Background8();



float RGB_c(float num);

class Stage
{
public:
	Stage();
	~Stage();
	void Initialize();
	bool WinCheck();
	void Win();
	void Lose();
	bool LoseCheck(int);
	void SetStage(int stage);
	bool CollisionCheck(Vector3 & compare);
	void Render();
	void Update();
	void HandleEvent(unsigned char key);

	int activeStageNumber = 1;
	//------------------------------------------------
	FMOD_SYSTEM *g_System;
	FMOD_SOUND **g_Sound;
	FMOD_CHANNEL **g_Channel;
	bool win = false;
	bool lose = false;
	bool clear = false;
private:
	vector<Pyramid*> stage[8];
	Vector3 stage_1_color[4] = { {255, 218, 245}, {232, 119, 171}, {250,235,85 },{ 113, 182, 255 } };
	Vector3 stage_2_color[4] = { { 219,205,43 },{ 196,184,100 },{ 166,163,147 },{ 42,196,58 } };
	Vector3 stage_3_color[4] = { {145,133,255 }, { 92,209,229 }, { 244,125,225 },{ 252,248,85 }};
	Vector3 stage_4_color[4] = { {219,205,43 }, { 167,100,196 }, { 150,166,147 },{ 42,196,58 } };
	Vector3 stage_5_color[4] = { { 125,142,244 },{ 246,152,255 },{ 252,132,85 },{ 9,181,154 } };
	Vector3 stage_6_color[4] = { { 255,205,18 },{ 183,240,177 },{ 250,244,192 } ,{ 255,255,255 } };
	Vector3 stage_7_color[4] = { { 219,205,43 },{ 196,184,100 } ,{ 166,163,147 },{ 42,1963,58 } };
	Vector3 stage_8_color[4] = { { 219,205,43 },{ 167,100,196 },{ 150,166,147 },{ 246,246,246 } };

	vector<Effect*> effectList;
	Player player;
	Vector3* stageColor = stage_1_color;
	clock_t totalTime = 50000;
	clock_t prevTime;
	int stageIndex[8] = { 0, };
	function <void()> background[8] = {};
};


