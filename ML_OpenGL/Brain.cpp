#include "stdafx.h"
#include "Brain.h"

#include "Agent.h"
#include "DNA.h"

void Brain::Init()
{
	// 0 : forward
	// 1 : left
	// 2 : right
	dna = new DNA( DNALength, 3 );
	timeAlive = 0.0f;
	timeWalking = 0.0f;
	alive = true;
}

void Brain::Update( Agent* owner )
{
	if ( dna == nullptr || !alive )
	{
		return;
	}

	timeAlive += 0.01f;

	float turn = 0.0f;
	float move = 0.0f;

	auto outputGene = [ & ] ( int currentGene )
		{
			if ( currentGene == 0 )
			{
				move = 1.0f;
				timeWalking += 0.01f;
			}
			else if ( currentGene == 1 )
			{
				turn = ( float )-M_PI;
			}
			else if ( currentGene == 2 )
			{
				turn = ( float )M_PI;
			}
		};

	if ( owner->NextPositionIsOut() )
	{
		outputGene( dna->GetGene( 1 ) );
	}
	else
	{
		outputGene( dna->GetGene( 0 ) );
	}

	owner->Rotate( turn * 0.15f );
	owner->Move( move * 0.5f );
}