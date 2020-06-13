#pragma once
#include <string>

//By DAE Second Semester Game Development

namespace dae1
{
	struct Point2f
	{
		Point2f( );
		Point2f( float x, float y );

		float x;
		float y;
	};

	struct Rectf
	{
		Rectf( );
		explicit Rectf( float left, float bottom, float width, float height );
	

		float left;
		float bottom;
		float width;
		float height;

		//Rectf& operator=(const Rectf& rhs);
	};

	//Rectf& Rectf::operator=(const Rectf& rhs)
	//{
	//	this->left = rhs.left;
	//	this->bottom = rhs.bottom;
	//	this->width = rhs.width;
	//	this->height = rhs.height;
	//	return *this;
	//}

	struct Color4f
	{
		Color4f( );
		explicit Color4f( float r, float g, float b, float a );
	
		float r;
		float g;
		float b;
		float a;
	};

	struct Circlef
	{
		Circlef( );
		explicit Circlef( const Point2f& center, float radius );
		explicit Circlef( float centerX, float centerY, float radius );

		Point2f center;
		float radius;
	};


	struct Ellipsef
	{
		Ellipsef( );
		explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
		explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

		Point2f center;
		float radiusX;
		float radiusY;
	};

}




