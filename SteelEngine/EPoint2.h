/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EPoint.h: Point2D struct
/*=============================================================================*/
#ifndef ELITE_MATH_POINT2
#define	ELITE_MATH_POINT2

#include "EPoint.h"
#include "EVector.h"
#include "EMathUtilities.h"

namespace Elite
{
	//=== POINT2 SPECIALIZATION ===
	template<typename T>
	struct Point<2, T>
	{
		//=== Data ===
#pragma warning(disable : 4201)
		union
		{
			T data[2];
			struct { T x, y; };
		};
#pragma warning(default : 4201)

		//=== Constructors ===
#pragma region Constructors
		Point<2, T>() = default;
		Point<2, T>(T _x, T _y)
			: x(_x), y(_y) {}
		Point<2, T>(const Point<2, T>& p)
			: x(p.x), y(p.y) {}
		Point<2, T>(Point<2, T>&& p) noexcept
			:x(std::move(p.x)), y(std::move(p.y)) {}
		explicit Point<2, T>(const Vector<2, T>& v)
			: x(v.x), y(v.y) {}
		explicit Point<2, T>(const Point<3, T>& p)
			: x(p.x), y(p.y) {}
		explicit Point<2, T>(const Point<4, T>& p)
			: x(p.x), y(p.y) {}
#pragma endregion

		//=== Conversion Operator ===
#pragma region ConversionOperator
		template<typename U>
		operator Point<2, U>() const //Implicit conversion to different types of Point2
		{
			return Point<2, U>(
				static_cast<U>(this->x),
				static_cast<U>(this->y));
		}
#pragma endregion

		//=== Arithmetic Operators ===
#pragma region ArithmeticOperators
		template<typename U>
		inline Point<2, T> operator+(const Vector<2, U>& v) const
		{ return Point<2, T>(x + static_cast<T>(v.x), y + static_cast<T>(v.y)); }

		template<typename U>
		inline Point<2, T> operator-(const Vector<2, U>& v) const
		{ return Point<2, T>(x - static_cast<T>(v.x), y - static_cast<T>(v.y)); }

		template<typename U>
		inline Vector<2, T> operator-(const Point<2, U>& p) const
		{ return Vector<2, T>(x - static_cast<T>(p.x), y - static_cast<T>(p.y)); }

		inline Point<2, T> operator*(T scale) const
		{ return Point<2, T>(x * scale, y * scale); }

		inline Point<2, T> operator/(T scale) const
		{
			const T revS = static_cast<T>(1.0f / scale);
			return Point<2, T>(x * revS, y * revS);
		}
#pragma endregion

		//=== Compound Assignment Operators ===
#pragma region CompoundAssignmentOperators
		inline Point<2, T>& operator=(const Point<2, T>& p)
		{ x = p.x; y = p.y; return *this; }

		inline Point<2, T>& operator+=(const Vector<2, T>& v)
		{ x += v.x; y += v.y; return *this; }

		inline Point<2, T>& operator-=(const Vector<2, T>& v)
		{ x -= v.x; y -= v.y; return *this; }

		inline Point<2, T>& operator*=(T scale)
		{ x *= scale; y *= scale; return *this;	}

		inline Point<2, T>& operator/=(T scale)
		{
			const T revS = static_cast<T>(1.0f / scale);
			x *= revS; y *= revS; return *this;
		}
#pragma endregion

		//=== Relational Operators ===
#pragma region RelationalOperators
		inline bool operator==(const Point<2, T>& p) const
		{ return AreEqual<T>(x, p.x) && AreEqual<T>(y, p.y); }

		inline bool operator!=(const Point<2, T>& p) const
		{ return !(*this == p);	}
#pragma endregion 

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		inline T operator[](uint8_t i) const
		{
			assert((i < 2) && "ERROR: index of Point2 [] operator is out of bounds!");
			return data[i];
		}

		inline T& operator[](uint8_t i)
		{
			assert((i < 2) && "ERROR: index of Point2 [] operator is out of bounds!");
			return data[i];
		}
#pragma endregion
	};
}
#endif