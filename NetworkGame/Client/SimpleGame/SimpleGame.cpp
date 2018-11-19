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


SceneManager* gSceneManager;
Network* gNetwork;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gSceneManager->Update();
	gSceneManager->Render();
	auto state = gSceneManager->GetState();
	if (state == STATE::win || state == STATE::lose)
	{
		gNetwork->SendExitData(gSceneManager->GetScore());
	//	exit(NULL);
	}
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	gSceneManager->MouseInput(button, state, x, y);
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	gSceneManager->KeyInput(key);
}

void SpecialKeyInput(int key, int x, int y)
{
	gSceneManager->KeyInput(key);
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

	gNetwork = new Network();
	int temp;
	scanf("%d", &temp);
	if(argc>1)
		gSceneManager = new SceneManager(atoi(argv[1]), gNetwork);
	else
		gSceneManager = new SceneManager(temp, gNetwork);



	gNetwork->Initialize(gSceneManager);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMainLoop();

	delete gNetwork;
	delete gSceneManager;

    return 0;
}

