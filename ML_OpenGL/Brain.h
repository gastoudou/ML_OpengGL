#pragma once

class Agent;
class DNA;

class Brain
{
public:

	int DNALength = 2;
	float timeAlive = 0.0f;
	float timeWalking = 0.0f;
	DNA* dna = nullptr;
	bool alive = true;
	bool seeGround = true;

	void Init();

	void Update( Agent* owner );
};
