#pragma once

class Agent;

class PopulationManager
{
public:
	PopulationManager() = default;
	~PopulationManager() = default;

	void Start();
	std::unique_ptr< Agent > Breed( const std::unique_ptr< Agent >& parent1, const std::unique_ptr< Agent >& parent2 ) const;
	void BreedNewPopulation();
	void Update();
	void Draw() const;

private:
	std::vector< std::unique_ptr< Agent > > population;
	static float elapsed;
	float trialTime = 2.5f;
	int generation = 1;
	int populationSize = 150;
};