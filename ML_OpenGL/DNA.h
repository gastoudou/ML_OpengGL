#pragma once

class DNA
{
	std::vector<int> genes;
	int dnaLength = 0;
	int maxValues = 0;

	DNA() = delete;

public:
	DNA( int l, int v );

	void SetRandom();

	void SetInt( int pos, int value );

	void Combine( DNA* d1, DNA* d2 );

	void Mutate();

	int GetGene( int pos );
};
