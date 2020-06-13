#pragma once
#include "SteelEnginePCH.h"
#include "Vector2f.h"
#include <sstream>
#include <iomanip>
#include <cmath>

//By DAE Second Semester Game Development
//-----------------------------------------------------------------
// Vector2f Constructors
//-----------------------------------------------------------------
dae1::Vector2f::Vector2f( )
	:Vector2f{ 0.0f, 0.0f }
{
}

dae1::Vector2f::Vector2f( float x, float y )
	: x{ x }
	, y{ y }
{
}

dae1::Vector2f::Vector2f( const Point2f& fromPoint, const Point2f& tillPoint )
	: Vector2f{ tillPoint.x - fromPoint.x, tillPoint.y - fromPoint.y }
{
}

dae1::Vector2f::Vector2f(const Point2f & point)
	: Vector2f{ Point2f{ 0.0f, 0.0f }, point }
{
}

// -------------------------
// Methods
// -------------------------
bool dae1::Vector2f::Equals(const Vector2f& other, float epsilon) const
{
	return ( abs(x - other.x) < epsilon ) && ( abs(y - other.y) < epsilon );
}

dae1::Point2f dae1::Vector2f::ToPoint2f() const
{
	return Point2f{ x, y };
}

float dae1::Vector2f::DotProduct(const Vector2f& other) const
{
	return x * other.x + y * other.y;
}

float dae1::Vector2f::CrossProduct(const Vector2f& other) const
{
	return x * other.y - y * other.x;
}

std::string dae1::Vector2f::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed;
	buffer << std::setprecision( 2 );
	buffer << "Vector2f(" <<  x  << ", " <<  y  << ")";
	return buffer.str();
}

float dae1::Vector2f::Norm() const
{
	return Length();
}

float dae1::Vector2f::Length() const
{
	return sqrt( x * x + y * y );
}

float dae1::Vector2f::SquaredLength() const
{
	return x * x + y * y;
}

float dae1::Vector2f::AngleWith(const Vector2f& other) const
{
	//https://stackoverflow.com/questions/21483999/using-atan2-to-find-angle-between-two-vectors
	// not calling dot and cross functions to prevent the overhead
	// return atan2f(CrossProduct(other), DotProduct(other));
	return atan2(x * other.y - other.x * y, x * other.x + y * other.y);
}

dae1::Vector2f dae1::Vector2f::Normalized(float epsilon) const
{
	float length{ Length( ) };
	if ( length < epsilon )
	{
		return Vector2f{ 0, 0 };
	}
	else
	{
		return Vector2f{ x / length, y / length };
	}
}

dae1::Vector2f dae1::Vector2f::Orthogonal() const
{
	return Vector2f{ -y, x };
}

dae1::Vector2f dae1::Vector2f::Reflect( const Vector2f& surfaceNormal ) const
{
	return (*this) - 2 * ( this->DotProduct( surfaceNormal ) * surfaceNormal );
}

void dae1::Vector2f::Set(float newX, float newY)
{
	x = newX;
	y = newY;
}

// -------------------------
// Member operators
// -------------------------
dae1::Vector2f dae1::Vector2f::operator-( ) const
{
	return Vector2f{ -x, -y };
}

dae1::Vector2f dae1::Vector2f::operator+ ( ) const
{
	return Vector2f{ x, y };
}

dae1::Vector2f& dae1::Vector2f::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

dae1::Vector2f& dae1::Vector2f::operator/=(float rhs)
{
	*this *= 1 / rhs;
	return *this;
}

dae1::Vector2f& dae1::Vector2f::operator+=(const Vector2f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

dae1::Vector2f& dae1::Vector2f::operator-=(const Vector2f& rhs)
{
	*this += -rhs;
	return *this;
}

dae1::Vector2f::operator dae1::Point2f()
{
	return Point2f{ x,y };
}

// -------------------------
// Non-member operators
// -------------------------
dae1::Vector2f operator*( float lhs, dae1::Vector2f rhs )
{
	return rhs *= lhs;
}

dae1::Vector2f operator*(dae1::Vector2f lhs, float rhs )
{
	return lhs *= rhs;
}

dae1::Vector2f operator/(dae1::Vector2f lhs, float rhs )
{
	return lhs *= (1 / rhs);
}

dae1::Vector2f operator+(dae1::Vector2f lhs, const dae1::Vector2f& rhs )
{
	return lhs += rhs;
}

dae1::Vector2f operator-(dae1::Vector2f lhs, const dae1::Vector2f& rhs )
{
	return lhs += -rhs;
}


bool operator==( const dae1::Vector2f& lhs, const dae1::Vector2f& rhs )
{
	return ( lhs.Equals( rhs ) );
}

bool operator!=( const  dae1::Vector2f& lhs, const dae1::Vector2f& rhs )
{
	return !( lhs == rhs );
}

std::ostream& operator<< ( std::ostream& lhs, const dae1::Vector2f& rhs )
{
	lhs << rhs.ToString( );
	return lhs;
}

// Point2f related operators
dae1::Point2f& operator+=(dae1::Point2f& lhs, const dae1::Vector2f& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

dae1::Point2f operator+(dae1::Point2f lhs, const dae1::Vector2f& rhs)
{
	lhs += rhs;
	return lhs;
}

dae1::Point2f& operator-=(dae1::Point2f& lhs, const dae1::Vector2f& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

dae1::Point2f operator-(dae1::Point2f lhs, const dae1::Vector2f& rhs)
{
	lhs -= rhs;
	return lhs;
}

dae1::Vector2f operator-(const dae1::Point2f& lhs, const dae1::Point2f& rhs)
{
	dae1::Vector2f v{ lhs.x - rhs.x, lhs.y - rhs.y };
	return v;
}