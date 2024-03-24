#pragma once

#include "Brain.h"
#include "Vector2.h"


class Agent
{
public:
	Agent( const Vector2& start_pos, const Vector2& start_fwd );

	void Init();
	void Update();
	void Draw();

	Brain& GetBrain()
	{
		return *brain;
	}

	void Move( float move );
	void Rotate( float rot );

	bool NextPositionIsOut() const;

private:
	std::unique_ptr< Brain > brain = nullptr;

	Vector2 pos = {};
	Vector2 fwd = {};

	bool alive = true;
	bool show_direction = false;
};