#pragma once
class Particle
{
public:
	Particle(Vector3 param);
	~Particle();
	void Update();
	Vector3 position[100];
	float totalTime, currentTime;
};

