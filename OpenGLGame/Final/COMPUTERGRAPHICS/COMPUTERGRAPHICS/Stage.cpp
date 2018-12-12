
#include "Stage.h"



Vector3 g_moving, g_rotation;
bool g_select = true;
bool invulunable = false;

float  LineIntersectPlane(Plane& plane, Vector3 *line)
{
	
	Vector3 dir = line[1] - line[0];
	float t = -plane.d -( (plane.a * line[1].x + plane.b * line[1].y + plane.c * line[1].z)
		/ (plane.a*dir.x + plane.b*dir.y + plane.c*dir.z));

	return t;
}

Plane PlaneEquation(Vector3* param)
{
	Vector3 side1 = param[0] - param[2];
	Vector3 side2 = param[1] - param[2];

	Vector3 cross = side1.Cross(side2);
	cross.Normalize();
	float dist = sqrt(pow(cross.x, 2) + pow(cross.y, 2) + pow(cross.z, 2));
	cross.x = cross.x / dist;
	cross.y = cross.y / dist;
	cross.z = cross.z / dist;

	float d = -((cross.x * param[0].x) + (cross.y*param[0].y) + (cross.z*param[0].z));

	Plane plane;
	plane.a = cross.x;
	plane.b = cross.y;
	plane.c = cross.z;
	plane.d = d;

	return plane;
}

bool PlaneCollision(Vector3* param, Vector3 point)
{
	Plane plane = PlaneEquation(param);
	float condition1 = plane.a*point.x + plane.b*point.y + plane.c*point.z + plane.d;
	float condition2 = plane.d;


	if (condition1*condition2 < 0)
	{
		Vector3 line[2];
		line[0] = { 0,0,0 };
		line[1].x =  point.x;
		line[1].y = point.y;
		line[1].z = point.z;
		float target = LineIntersectPlane(plane, line);
		float dist = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));
		//cout << target << endl;
		if (dist < target+50)
		{
			return true;
		}
	}
	return false;
}


bool Stage::CollisionCheck( Vector3& compare)
{

	int random = rand() % 5;
	if (random > 3)
	{
		random = 3;
	}
	if (invulunable)
	{
		random = 3;
	}
	//cout << random << endl;

	bool check = false;
	WinCheck();
	
	for (auto poly : stage[activeStageNumber - 1])
	{
		auto collider = poly->GetCollider();
		if (PlaneCollision(collider->left, compare))
		{
			LoseCheck(LEFT);
			poly->ChangeColor(stageColor[random], LEFT);
			auto neweffect = new Effect(compare, stageColor[random]);
			effectList.push_back(neweffect);
			return true;
		}
		if (PlaneCollision(collider->right, compare))
		{
			LoseCheck(RIGHT);
			poly->ChangeColor(stageColor[random], RIGHT);
			auto neweffect = new Effect(compare, stageColor[random]);
			//cout << "right" << endl;
			effectList.push_back(neweffect);
			return true;
		}
		if (PlaneCollision(collider->front, compare))
		{
			LoseCheck(FRONT);
			poly->ChangeColor(stageColor[random], FRONT);
			auto neweffect = new Effect(compare, stageColor[random]);
			//cout << "left" << endl;
			effectList.push_back(neweffect);
			return true;
		}
		if (PlaneCollision(collider->back, compare))
		{
			LoseCheck(BACK);
			poly->ChangeColor(stageColor[random], BACK);
			auto neweffect = new Effect(compare, stageColor[random]);
			//cout << "right" << endl;
			effectList.push_back(neweffect);
			return true;
		}
	}
	return check;
}

Stage::Stage()
{
	Initialize();
}



Stage::~Stage()
{
}

bool Stage::WinCheck()
{
	int size = 0;
	int check = 0;
	for (auto poly : stage[activeStageNumber - 1])
	{
		for(int i=1;i<5;++i)
		{
			if ((poly->color[i].x == stageColor[3].x&&poly->color[i].y == stageColor[3].y &&poly->color[i].z == stageColor[3].z))
			{
				check++;
			}
		}
		size++;
	}
	if (size*4 > check)
	{
		return false;
	}
	else
	{
		Win();
		return true;
	}
}
void Stage::Win()
{
	win = true;
	SetStage(activeStageNumber + 1);
}
void Stage::Lose()
{
	for (auto poly : stage[activeStageNumber - 1])
	{
		for (int i = 1; i<5; ++i)
		{
			poly->color[i] = { 253,243,187 };
		}
	}
}
bool Stage::LoseCheck(int side)
{

	if (!invulunable)
	{
		for (auto poly : stage[activeStageNumber - 1])
		{
			if ((poly->color[side].x == stageColor[3].x && poly->color[side].y == stageColor[3].y &&poly->color[side].z == stageColor[3].z))
			{
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[12], 0, &g_Channel[12]);
				lose = true;
			}
		}
	}
	return false;
}

void Stage::SetStage(int stage)
{
	cout << activeStageNumber << endl;
	if (stage >= 9)
	{
		stage = 8;
		clear = true;
		return;
	}
	else if (stage < 1)
	{
		stage = 1;
		return;
	}
	//else if (stage > 8)
	//{
	//	stage = 8;
	//	return;
	//}
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[13], 0, &g_Channel[13]);


	effectList.clear();
	player.bulletList.clear();
	activeStageNumber = stage;

		switch (activeStageNumber)
		{
		case 1:
			player.rotation.z = 1;
			stageColor = stage_1_color;
			break;
		case 2:
			player.rotation.z = 1;
			stageColor = stage_2_color;
			break;
		case 3:
			player.rotation.z = 1;
			stageColor = stage_3_color;
			break;
		case 4:
			player.rotation.z = 1;
			stageColor = stage_4_color;
			break;
		case 5:
			player.rotation.z = 1;
			stageColor = stage_5_color;
			break;
		case 6:
			player.rotation.z = 1;
			stageColor = stage_6_color;
			break;
		case 7:
			player.rotation.z = 1;
			stageColor = stage_7_color;
			break;
		case 8:
			player.rotation.z = 5;
			stageColor = stage_8_color;
			break;
		}
		player.color = stageColor[3];
}






void Stage::Update()
{
	if (lose)
	{
		//cout << "test" << endl;
		Lose();
	}


}

void Stage::HandleEvent(unsigned char key)
{
	Vector3 move;
	if (key == 'a')
	{
		invulunable== true ? invulunable = false : invulunable = true;
		if (player.helpingLine == true)
		{
			player.helpingLine = false;
		}
		else if (player.helpingLine == false)
		{
			player.helpingLine = true;
		}
		cout << player.helpingLine << endl;
	}
	
	if (key == 'i')
	{
		player.position = { 0,350,0 };
		player.rotation = { 0,0,2 };
		player.degree = 0;
		if (activeStageNumber == 7)
		{
			player.rotation = { 0,0,5 };
		}
	}
	if (key == ' ')
	{
		player.Gun.on = true;
		if(true)//(totalTime / CLOCKS_PER_SEC > 0.2)
		{
			player.Shoot();
			totalTime = 0;
		}
	}
	if (key == 'Y')
	{
		for (auto poly : stage[activeStageNumber - 1])
		{
			poly->rotation.y += 0.1;
			poly->rotation.z = 0;
		}
	}
	if (key == 'y')
	{
		for (auto poly : stage[activeStageNumber - 1])
		{
			poly->rotation.y -= 0.1;
			poly->rotation.z = 0;
		}
	}
	if (key == 'Z')
	{
		for (auto poly : stage[activeStageNumber - 1])
		{
			poly->rotation.y = 0;
			poly->rotation.z += 0.1;
		}
	}
	if (key == 'z')
	{
		for (auto poly : stage[activeStageNumber - 1])
		{
			poly->rotation.y = 0;
			poly->rotation.z -= 0.1;
		}
	}



	if (key == 'n')
	{
		win = true;
		cout << activeStageNumber + 1 << endl;
		SetStage(activeStageNumber + 1);
	}
	if (key == 'b')
	{	
		win = true;
		SetStage(activeStageNumber - 1);
	}
}

void Stage::Render()
{
	bool collide = false;
	clock_t currentTime = clock();
	totalTime += (currentTime - prevTime);
	prevTime = currentTime;
	static int blockRotation = 0;
	static int soundIndex = 0;

	glPushMatrix();
	glLoadIdentity();
	background[activeStageNumber - 1]();
	glColor3ub(stageColor[3].x, stageColor[3].y, stageColor[3].z);
	glTranslatef(400, 400, 0);
	glRotatef(blockRotation, 0, 1, 0);
	blockRotation += 5;
	glutSolidCube(50);
	glPopMatrix();


	player.Update();
	player.Render();
	
	for (auto poly : stage[activeStageNumber - 1])
	{
		poly->Render();
	}
	WinCheck();
	for (auto iter = player.bulletList.begin(); iter != player.bulletList.end();)//충돌체크
	{
		auto bullet = *iter;
		//LOG_3("bullet", bullet->position.x, bullet->position.y, bullet->position.z);
		if (CollisionCheck(bullet->GetCollider()))
		{
			for (int i = 0; i < 3; i++)
			{
				bullet->Update();
				bullet->Render();
			}
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[soundIndex+2], 0, &g_Channel[soundIndex+2]);

			soundIndex = (soundIndex+ 1)%10;
			iter = player.bulletList.erase(iter);
		}
		else
			iter++;
	}
	//-----------------------------------------------------------------------------------------------

	for (auto iter = effectList.begin(); iter != effectList.end();)
	{
		auto effect = *iter;
		effect->Render();
		if (effect->end)
			iter = effectList.erase(iter);
		else
			iter++;
	}
}




void Stage::Initialize()
{
	
	for (int i = 0; i < 8; i++)
	{
		stage[i].clear();
	}


	Pyramid* temp[20];
	//--------------스테이지 세팅-----------------
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;
	temp[0]->Move({ -100,50,0 });
	temp[1]->RotateZ(180);
	temp[1]->Move({ -100,-50,0 });

	temp[2] = new Pyramid;
	temp[3] = new Pyramid;

	temp[2]->Move({ 100,50,0 });
	temp[3]->RotateZ(180);
	temp[3]->Move({ 100,-50,0 });

	for (int i = 0; i < 4; i++)
	{
		stage[1].push_back(temp[i]);
	}
	background[1] = bind(Draw_Background2);
	//---------------------2--------------------------
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;
	temp[0]->Move({ 0,50,0 });
	temp[1]->RotateZ(180);
	temp[1]->Move({ 0,-50,0 });


	for (int i = 0; i < 2; i++)
	{
		stage[0].push_back(temp[i]);
	}
	background[0] = bind(Draw_Background1);
	//---------------------3--------------------------빈 표창
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;
	temp[2] = new Pyramid;
	temp[3] = new Pyramid;
	temp[0]->RotateZ(0);
	temp[0]->Move({ 0,100,0 });
	temp[1]->RotateZ(90);
	temp[1]->Move({ -100,0,0 });
	temp[2]->RotateZ(180);
	temp[2]->Move({ 0,0 - 100,0 });
	temp[3]->RotateZ(270);
	temp[3]->Move({ 100,0,0 });


	for (int i = 0; i < 4; i++)
	{
		stage[2].push_back(temp[i]);
	}
	background[2] = bind(Draw_Background3);
	//---------------------4--------------------------빈 표창+알파
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;
	temp[2] = new Pyramid;
	temp[3] = new Pyramid;
	temp[0]->RotateZ(0);
	temp[0]->Move({ 0,100,0 });
	temp[1]->RotateZ(90);
	temp[1]->Move({ -100,0,0 });
	temp[2]->RotateZ(180);
	temp[2]->Move({ 0,0 - 100,0 });
	temp[3]->RotateZ(270);
	temp[3]->Move({ 100,0,0 });


	temp[4] = new Pyramid;
	temp[5] = new Pyramid;
	temp[4]->RotateX(90);
	temp[4]->Move({ 0,0,100 });
	temp[5]->RotateX(-90);
	temp[5]->Move({ 0,0,-100 });
	//cout << g_moving.x << "  " << g_moving.y << " " << g_rotation.x << endl;

	temp[4]->rotation = { 0,0,2 };
	temp[5]->rotation = { 0,0,2 };

	for (int i = 0; i < 6; i++)
	{
		stage[3].push_back(temp[i]);
	}
	background[3] = bind(Draw_Background4);
	//--------------------5-----------------------------꽉찬 표창
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;
	temp[0]->Move({ 0,150,0 });
	temp[1]->RotateZ(180);
	temp[1]->Move({ 0,50,0 });

	temp[2] = new Pyramid;
	temp[3] = new Pyramid;
	temp[2]->Move({ 0,-50,0 });
	temp[3]->RotateZ(180);
	temp[3]->Move({ 0,-150,0 });

	temp[4] = new Pyramid;
	temp[5] = new Pyramid;
	temp[4]->RotateZ(-90);
	temp[4]->Move({ 150,0,0 });
	temp[5]->RotateZ(90);
	temp[5]->Move({ 50,0,0 });


	temp[6] = new Pyramid;
	temp[7] = new Pyramid;
	temp[6]->RotateZ(-90);
	temp[6]->Move({ -50,0,0 });
	temp[7]->RotateZ(90);
	temp[7]->Move({ -150,0,0 });

	for (int i = 0; i < 8; i++)
	{
		stage[4].push_back(temp[i]);
	}
	background[4] = bind(Draw_Background5);
	//--------------------6-----------------------------나비
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;

	temp[0]->RotateZ(47);
	temp[0]->Move({ -129,95,0 });
	temp[1]->RotateZ(-135);
	temp[1]->Move({ -56,26,0 });

	temp[2] = new Pyramid;
	temp[3] = new Pyramid;
	temp[2]->RotateZ(-47);
	temp[2]->Move({ 129,95,0 });
	temp[3]->RotateZ(135);
	temp[3]->Move({ 56,26,0 });



	temp[4] = new Pyramid;
	temp[5] = new Pyramid;
	temp[4]->Move({ 0,-100,0 });
	temp[5]->RotateZ(180);
	temp[5]->Move({ 0,-200,0 });


	temp[6] = new Pyramid;
	temp[7] = new Pyramid;
	temp[6]->RotateZ(-45);
	temp[6]->Move({ -54,-78,0 });
	temp[7]->RotateZ(135);
	temp[7]->Move({ -128,-147,0 });


	temp[8] = new Pyramid;
	temp[9] = new Pyramid;
	temp[8]->RotateZ(45);
	temp[8]->Move({ 54,-78,0 });
	temp[9]->RotateZ(-135);
	temp[9]->Move({ 128,-147,0 });

	for (int i = 0; i <10; i++)
	{
		stage[5].push_back(temp[i]);
	}
	background[5] = bind(Draw_Background6);

	//--------------------7-----------------------------
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;
	temp[0]->Move({ 0,150,0 });
	temp[1]->RotateZ(180);
	temp[1]->Move({ 0,50,0 });


	//cout << g_moving.x << "  " << g_moving.y << " " << g_rotation.x << endl;

	temp[2] = new Pyramid;
	temp[3] = new Pyramid;

	temp[2]->RotateZ(47);
	temp[2]->Move({ -129,95,0 });
	temp[3]->RotateZ(-135);
	temp[3]->Move({ -56,26,0 });

	temp[4] = new Pyramid;
	temp[5] = new Pyramid;
	temp[4]->RotateZ(-47);
	temp[4]->Move({ 129,95,0 });
	temp[5]->RotateZ(135);
	temp[5]->Move({ 56,26,0 });


	temp[6] = new Pyramid;
	temp[7] = new Pyramid;
	temp[6]->RotateZ(269);
	temp[6]->Move({ -77,-25,0 });
	temp[7]->RotateZ(86);
	temp[7]->Move({ -175,-25,0 });


	temp[8] = new Pyramid;
	temp[9] = new Pyramid;
	temp[8]->RotateZ(269);
	temp[8]->Move({ 175,-25,0 });
	temp[9]->RotateZ(86);
	temp[9]->Move({ 77,-25,0 });

	temp[10] = new Pyramid;
	temp[11] = new Pyramid;
	temp[10]->Move({ 0,-100,0 });
	temp[11]->RotateZ(180);
	temp[11]->Move({ 0,-200,0 });

	temp[12] = new Pyramid;
	temp[13] = new Pyramid;
	temp[12]->RotateZ(-45);
	temp[12]->Move({ -54,-78,0 });
	temp[13]->RotateZ(135);
	temp[13]->Move({ -128,-147,0 });


	temp[14] = new Pyramid;
	temp[15] = new Pyramid;
	temp[14]->RotateZ(45);
	temp[14]->Move({ 54,-78,0 });
	temp[15]->RotateZ(-135);
	temp[15]->Move({ 128,-147,0 });

	for (int i = 0; i < 16; i++)
	{
		stage[6].push_back(temp[i]);
	}
	background[6] = bind(Draw_Background7);
	//--------------------8-----------------------------
	temp[0] = new Pyramid;
	temp[1] = new Pyramid;
	temp[0]->Move({ 0,150,0 });
	temp[1]->RotateZ(180);
	temp[1]->Move({ 0,50,0 });


	//cout << g_moving.x << "  " << g_moving.y << " " << g_rotation.x << endl;

	temp[2] = new Pyramid;
	temp[3] = new Pyramid;

	temp[2]->RotateZ(47);
	temp[2]->Move({ -129,95,0 });
	temp[3]->RotateZ(-135);
	temp[3]->Move({ -56,26,0 });

	temp[4] = new Pyramid;
	temp[5] = new Pyramid;
	temp[4]->RotateZ(-47);
	temp[4]->Move({ 129,95,0 });
	temp[5]->RotateZ(135);
	temp[5]->Move({ 56,26,0 });


	temp[6] = new Pyramid;
	temp[7] = new Pyramid;
	temp[6]->RotateZ(269);
	temp[6]->Move({ -77,-25,0 });
	temp[7]->RotateZ(86);
	temp[7]->Move({ -175,-25,0 });


	temp[8] = new Pyramid;
	temp[9] = new Pyramid;
	temp[8]->RotateZ(269);
	temp[8]->Move({ 175,-25,0 });
	temp[9]->RotateZ(86);
	temp[9]->Move({ 77,-25,0 });

	temp[10] = new Pyramid;
	temp[11] = new Pyramid;
	temp[10]->Move({ 0,-100,0 });
	temp[11]->RotateZ(180);
	temp[11]->Move({ 0,-200,0 });

	temp[12] = new Pyramid;
	temp[13] = new Pyramid;
	temp[12]->RotateZ(-45);
	temp[12]->Move({ -54,-78,0 });
	temp[13]->RotateZ(135);
	temp[13]->Move({ -128,-147,0 });


	temp[14] = new Pyramid;
	temp[15] = new Pyramid;
	temp[14]->RotateZ(45);
	temp[14]->Move({ 54,-78,0 });
	temp[15]->RotateZ(-135);
	temp[15]->Move({ 128,-147,0 });

	for (int i = 0; i < 16; i++)
	{
		stage[7].push_back(temp[i]);
	}
	background[7] = bind(Draw_Background8);
}


void Draw_Background1() {



	glBegin(GL_QUADS);
	glColor3f(RGB_c(92), RGB_c(209), RGB_c(229));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(92), RGB_c(209), RGB_c(229));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(212), RGB_c(244), RGB_c(250));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(212), RGB_c(244), RGB_c(250));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();

}
void Draw_Background2() {
	glBegin(GL_QUADS);
	glColor3f(RGB_c(206), RGB_c(0), RGB_c(35));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(206), RGB_c(0), RGB_c(35));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(255), RGB_c(167), RGB_c(167));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(255), RGB_c(167), RGB_c(167));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();
}
void Draw_Background3() {
	glBegin(GL_QUADS);
	glColor3f(RGB_c(31), RGB_c(25), RGB_c(13));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(31), RGB_c(25), RGB_c(13));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(93), RGB_c(93), RGB_c(93));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(93), RGB_c(93), RGB_c(93));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();
}
void Draw_Background4() {
	glBegin(GL_QUADS);
	glColor3f(RGB_c(21), RGB_c(18), RGB_c(120));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(21), RGB_c(18), RGB_c(120));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(18), RGB_c(69), RGB_c(171));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(18), RGB_c(69), RGB_c(171));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();
}
void Draw_Background5() {
	glBegin(GL_QUADS);
	glColor3f(RGB_c(183), RGB_c(240), RGB_c(177));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(183), RGB_c(240), RGB_c(177));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(206), RGB_c(242), RGB_c(121));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(206), RGB_c(242), RGB_c(121));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();
}
void Draw_Background6() {

	glBegin(GL_QUADS);
	glColor3f(RGB_c(255), RGB_c(178), RGB_c(217));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(255), RGB_c(178), RGB_c(217));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(255), RGB_c(217), RGB_c(236));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(255), RGB_c(217), RGB_c(236));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();
}
void Draw_Background7() {
	glBegin(GL_QUADS);
	glColor3f(RGB_c(206), RGB_c(0), RGB_c(35));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(206), RGB_c(0), RGB_c(35));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(255), RGB_c(167), RGB_c(167));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(255), RGB_c(167), RGB_c(167));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();
}
void Draw_Background8() {
	glBegin(GL_QUADS);
	glColor3f(RGB_c(21), RGB_c(18), RGB_c(120));
	glVertex3f(1000.0, 1000.0, -500.0);//1
	glColor3f(RGB_c(21), RGB_c(18), RGB_c(120));
	glVertex3f(-1000.0, 1000.0, -500.0);//2
	glColor3f(RGB_c(18), RGB_c(69), RGB_c(171));
	glVertex3f(-1000.0, -1000.0, -500.0);//3
	glColor3f(RGB_c(18), RGB_c(69), RGB_c(171));
	glVertex3f(1000.0, -1000.0, -500.0);//4
	glEnd();
}
