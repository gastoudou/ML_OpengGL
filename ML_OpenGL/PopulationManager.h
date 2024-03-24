#pragma once
#include <vector>

class Agent;

class PopulationManager
{
	int populationSize = 150;
	std::vector< Agent* > population;
	static float elapsed;
	float trialTime = 2.5f;
	int generation = 1;

public:

	void Start();
	Agent* Breed( Agent* parent1, Agent* parent2 );
	void BreedNewPopulation();
	void Update();
	void Draw();
};