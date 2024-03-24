#include "stdafx.h"
#include "Agent.h"

#define GLOBE 1
#define SPHERIC 2
#define BLUE_INDEX 16

bool OutOfWorld( const Vector2& pos )
{
	if ( pos.x <= -worldLimits.x || pos.x >= worldLimits.x || pos.y <= -worldLimits.y || pos.y >= worldLimits.y )
	{
		return true;
	}
	return false;
}

Agent::Agent( const Vector2& start_pos, const Vector2& start_fwd )
	: brain( std::make_unique< Brain >() )
	, pos( start_pos )
	, fwd( start_fwd )
{
}

void Agent::Init()
{
	{
		GLUquadricObj* quadObj;

		glNewList( GLOBE, GL_COMPILE );
		quadObj = gluNewQuadric();
		gluQuadricDrawStyle( quadObj, GLU_LINE );
		gluSphere( quadObj, 1.0, 8, 8 );
		glEndList();
	}

	{
		GLUquadricObj* quadObj;

		glNewList( SPHERIC, GL_COMPILE );
		quadObj = gluNewQuadric();
		gluSphere( quadObj, 0.1, 8, 8 );
		glEndList();
	}

	brain->Init();
}

void Agent::Update()
{
	if ( !alive )
	{
		return;
	}

	if ( OutOfWorld( pos ) )
	{
		alive = false;
		return;
	}

	brain->Update( this );
}

void Agent::Draw()
{
	if ( !alive )
	{
		glColor3f( 1.0f, 0.0f, 0.0f );
	}
	else
	{
		glColor3f( 1.0f, 1.0f, 1.0f );
	}

	glPushMatrix();
	glTranslatef( pos.x, pos.y, zoom );

	glBegin( GL_QUADS );
	glVertex3f( -1.0f, 1.0f, 0.0f );
	glVertex3f( 1.0f, 1.0f, 0.0f );
	glVertex3f( 1.0f, -1.0f, 0.0f );
	glVertex3f( -1.0f, -1.0f, 0.0f );
	glEnd();

	glPopMatrix();
}

void Agent::Move( float move )
{
	if ( move > 0.001f || move < -0.001f )
	{
		pos += fwd * move;
	}
}

void Agent::Rotate( float rot )
{
	if ( rot > 0.001f || rot < -0.001f )
	{
		const float x = fwd.x;
		const float y = fwd.y;

		fwd.x = cosf( rot ) * x - sinf( rot ) * y;
		fwd.y = sinf( rot ) * x + cosf( rot ) * y;
	}
}

bool Agent::NextPositionIsOut() const
{
	Vector2 futurPos = pos + fwd * 5.0f;

	if ( OutOfWorld( futurPos ) )
	{
		return true;
	}
	return false;
}