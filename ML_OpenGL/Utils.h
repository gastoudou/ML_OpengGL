#pragma once

namespace
{
	int RandomRange( int min, int max )
	{
		return min + rand() % ( max - min );
	}

	const Vector2 worldLimits( 10.0f, 10.0f );
	const float zoom = -50.0f;
}