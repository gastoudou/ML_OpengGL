#include "stdafx.h"
#include "PopulationManager.h"

#include "Agent.h"
#include "Brain.h"
#include "DNA.h"

const int rangePosition = static_cast< int >( worldLimits.x / 2 );

float PopulationManager::elapsed = 0.0f;

void PopulationManager::Start()
{
	for ( int i = 0; i < populationSize; i++ )
	{
		Vector2 start_pos( ( float )RandomRange( -rangePosition, rangePosition ), ( float )RandomRange( -rangePosition, rangePosition ) );
		Vector2 start_fwd( ( float )RandomRange( -rangePosition, rangePosition ), ( float )RandomRange( -rangePosition, rangePosition ) );
		start_fwd.normalize();

		std::unique_ptr< Agent > newBot = std::make_unique< Agent >( start_pos, start_fwd );
		newBot->Init();
		newBot->GetBrain().Init();
		population.push_back( newBot );
	}
}

std::unique_ptr< Agent > PopulationManager::Breed( const std::unique_ptr< Agent >& parent1, const std::unique_ptr< Agent >& parent2 ) const
{
	Vector2 start_pos( ( float )RandomRange( -rangePosition, rangePosition ), ( float )RandomRange( -rangePosition, rangePosition ) );
	Vector2 start_fwd( ( float )RandomRange( -rangePosition, rangePosition ), ( float )RandomRange( -rangePosition, rangePosition ) );
	start_fwd.normalize();

	std::unique_ptr< Agent > newBot = std::make_unique< Agent >( start_pos, start_fwd );
	newBot->Init();

	Brain& newBotBrain = newBot->GetBrain();
	newBotBrain.Init();

	if ( RandomRange( 0, 100 ) == 1 )
	{
		newBotBrain.dna->Mutate();
	}
	else
	{
		newBotBrain.dna->Combine( parent1->GetBrain().dna, parent2->GetBrain().dna );
	}

	return newBot;
}

void PopulationManager::BreedNewPopulation()
{
	const auto sorted_population = population;

	std::sort( sorted_population.begin(), sorted_population.end(), [] ( auto i, auto j )
		{
			return ( i->GetBrain().timeWalking ) < ( j->GetBrain().timeWalking );
		} );

	population.clear();

	for ( size_t i = sorted_population.size() - 1u; i > ( sorted_population.size() / 2u ) - 1; --i )
	{
		population.push_back( Breed( sorted_population[ i ], sorted_population[ i - 1 ] ) );
		population.push_back( Breed( sorted_population[ i - 1 ], sorted_population[ i ] ) );
	}

	generation++;

	std::stringstream out;
	out << "Generation: " << generation << " - size: " << population.size() << std::endl;
	OutputDebugString( out.str().c_str() );
}

void PopulationManager::Update()
{
	elapsed += 0.01f;
	if ( elapsed > trialTime )
	{
		BreedNewPopulation();
		elapsed = 0.0f;
	}
	else
	{
		for ( auto& agent : population )
		{
			agent->Update();
		}
	}
}

void PopulationManager::Draw() const
{
	glColor3f( 0.0f, 1.0f, 0.5f );

	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, zoom - 1.0f );

	glBegin( GL_QUADS );
	glVertex3f( -worldLimits.x, worldLimits.y, 0.0f );
	glVertex3f( worldLimits.x, worldLimits.y, 0.0f );
	glVertex3f( worldLimits.x, -worldLimits.y, 0.0f );
	glVertex3f( -worldLimits.x, -worldLimits.y, 0.0f );
	glEnd();

	glPopMatrix();

	for ( const auto& agent : population )
	{
		agent->Draw();
	}
}