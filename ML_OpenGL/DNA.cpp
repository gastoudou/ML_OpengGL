#include "stdafx.h"
#include "DNA.h"

DNA::DNA( int l, int v )
{
	dnaLength = l;
	maxValues = v;
	SetRandom();
}

void DNA::SetRandom()
{
	genes.clear();
	for ( int i = 0; i < dnaLength; i++ )
	{
		genes.push_back( RandomRange( 0, maxValues ) );
	}
}

void DNA::SetInt( int pos, int value )
{
	genes[ pos ] = value;
}

void DNA::Combine( DNA* d1, DNA* d2 )
{
	for ( int i = 0; i < dnaLength; ++i )
	{
		if ( i < dnaLength / 2.0 )
		{
			int c = d1->genes[ i ];
			genes[ i ] = c;
		}
		else
		{
			int c = d2->genes[ i ];
			genes[ i ] = c;
		}
	}
}

void DNA::Mutate()
{
	genes[ RandomRange( 0, dnaLength ) ] = RandomRange( 0, maxValues );
}

int DNA::GetGene( int pos )
{
	return genes[ pos ];
}