/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"



unordered_map<string, Scene*> gScenes;

Scene* currentScene;
Network* gNetwork;
Renderer* gRenderer;
int gSide = BLUE_TEAM;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	currentScene->Update();
	currentScene->Render();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	currentScene->MouseInput(button, state, x, y);
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	//currentScene->KeyInput(key);
}

void SpecialKeyInput(int key, int x, int y)
{
	currentScene->KeyInput(key);
}

void KeyUpInput(int key, int x, int y)
{
	currentScene->KeyUpInput(key);
}

int main(int argc, char **argv)
{

	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);//윈도우 세로크기 700도 안되서 600으로 합니다.
	glutCreateWindow("Game Software Engineering KPU");
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
		std::cout << " GLEW Version is 3.0\n ";
	else
		std::cout << "GLEW 3.0 not supported\n ";

	 //Initialize Renderer
	srand((unsigned)time(NULL));


	gRenderer = new Renderer(WIDTH, HEIGHT);
	if (!gRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	gNetwork = new Network();

	StartScene* startScene = new StartScene(gRenderer);
	gScenes["Start"] = startScene;

	GameScene* gameScene = new GameScene(gRenderer,gNetwork);
	gScenes["Game"] = gameScene;

	gNetwork->Initialize(dynamic_cast<GameScene*>(gScenes["Game"]));
	gScenes["Game"]->Initialize();


	currentScene = gScenes["Game"];
	//currentScene = gScenes["Start"];

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutSpecialUpFunc(KeyUpInput);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMainLoop();

	delete gRenderer;
	delete gNetwork;

	

	delete gScenes["Game"];
	gScenes.erase("Game");
	delete gScenes["Start"];
	gScenes.erase("Start");

    return 0;
}

