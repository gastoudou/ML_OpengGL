#pragma once

#include <corecrt_math.h>

class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vector2()
		: x( 0.0f )
		, y( 0.0f )
	{
	}

	explicit Vector2( const float _x, const float _y )
		: x( _x )
		, y( _y )
	{
	}

	~Vector2()
	{
	}

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
	}

	const Vector2 operator+( const Vector2& _lhs ) const
	{
		return Vector2( this->x + _lhs.x, this->y + _lhs.y );
	}

	const Vector2& operator+=( const Vector2& _lhs )
	{
		this->x += _lhs.x;
		this->y += _lhs.y;
		return *this;
	}

	const Vector2 operator+=( const Vector2& _lhs ) const
	{
		return Vector2( this->x + _lhs.x, this->y + _lhs.y );
	}

	const Vector2 operator-( const Vector2& _lhs ) const
	{
		return Vector2( this->x - _lhs.x, this->y - _lhs.y );
	}

	const Vector2& operator-=( const Vector2& _rhs )
	{
		this->x -= _rhs.x;
		this->y -= _rhs.y;
		return *this;
	}

	const Vector2 operator-=( const Vector2& _rhs ) const
	{
		return Vector2( this->x - _rhs.x, this->y - _rhs.y );
	}

	const Vector2 operator*( const float _f ) const
	{
		return Vector2( this->x * _f, this->y * _f );
	}

	const Vector2& operator*=( const float _f )
	{
		this->x *= _f;
		this->y *= _f;
		return *this;
	}

	const Vector2 operator*=( const float _f ) const
	{
		return Vector2( this->x * _f, this->y * _f );
	}

	const Vector2 operator/( const float _f ) const
	{
		return Vector2( this->x / _f, this->y / _f );
	}

	const Vector2& operator/=( const float _f )
	{
		this->x /= _f;
		this->y /= _f;
		return *this;
	}

	const Vector2 operator/=( const float _f ) const
	{
		return Vector2( this->x / _f, this->y / _f );
	}

	float length() const
	{
		return sqrtf( x * x + y * y );
	}

	float lengthSq() const
	{
		return x * x + y * y;
	}

	void normalize()
	{
		const float len = length();
		x /= len;
		y /= len;
	}
};