/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EPoint.h: Point4D struct
/*=============================================================================*/
#ifndef ELITE_MATH_POINT4
#define	ELITE_MATH_POINT4

#include "EPoint.h"
#include "EVector.h"
#include "EMathUtilities.h"

namespace Elite
{
	//=== POINT4 SPECIALIZATION ===
	template<typename T>
	struct Point<4, T>
	{
		//=== Data ===
#pragma warning(disable : 4201)
		union
		{
			T data[4];
			struct { T x, y, z, w; };
			Point<2, T> xy;
			Point<3, T> xyz;
		};
#pragma warning(default : 4201)

		//=== Constructors ===
#pragma region Constructors
		Point<4, T>() = default;
		Point<4, T>(T _x, T _y, T _z, T _w = 1) //W component of Point is usually 1
			: x(_x), y(_y), z(_z), w(_w) {}
		Point<4, T>(const Point<2, T> p, T _z, T _w = 1)
			: x(p.x), y(p.y), z(_z), w(_w) {}
		Point<4, T>(const Point<3, T> p, T _w = 1)
			: x(p.x), y(p.y), z(p.z), w(_w) {}
		Point<4, T>(const Point<4, T>& p)
			: x(p.x), y(p.y), z(p.z), w(p.w) {}
		Point<4, T>(Point<4, T>&& p) noexcept
			:x(std::move(p.x)), y(std::move(p.y)), z(std::move(p.z)), w(std::move(p.w)) {}
		explicit Point<4, T>(const Vector<4, T>& v)
			: x(v.x), y(v.y), z(v.z), w(v.w) {}
#pragma endregion

		//=== Conversion Operator ===
#pragma region ConversionOperator
		template<typename U>
		operator Point<4, U>() const //Implicit conversion to different types of Point3
		{
			return Point<4, U>(
				static_cast<U>(this->x),
				static_cast<U>(this->y),
				static_cast<U>(this->z),
				static_cast<U>(this->w));
		}
#pragma endregion

		//=== Arithmetic Operators ===
#pragma region ArithmeticOperators
		template<typename U>
		inline Point<4, T> operator+(const Vector<4, U>& v) const
		{ return Point<4, T>(x + static_cast<T>(v.x), y + static_cast<T>(v.y), 
			z + static_cast<T>(v.z), w + static_cast<T>(v.w)); }

		template<typename U>
		inline Point<4, T> operator-(const Vector<4, U>& v) const
		{ return Point<4, T>(x - static_cast<T>(v.x), y - static_cast<T>(v.y), 
			z - static_cast<T>(v.z), w - static_cast<T>(v.w)); }

		template<typename U>
		inline Vector<4, T> operator-(const Point<4, U>& p) const
		{ return Vector<4, T>(x - static_cast<T>(p.x), y - static_cast<T>(p.y), 
			z - static_cast<T>(p.z), w - static_cast<T>(p.w)); }

		inline Point<4, T> operator*(T scale) const
		{ return Point<4, T>(x * scale, y * scale, z * scale, w * scale); }

		inline Point<4, T> operator/(T scale) const
		{
			const T revS = static_cast<T>(1.0f / scale);
			return Point<4, T>(x * revS, y * revS, z * revS, w * revS);
		}
#pragma endregion

		//=== Compound Assignment Operators ===
#pragma region CompoundAssignmentOperators
		inline Point<4, T>& operator=(const Point<4, T>& p)
		{ x = p.x; y = p.y; z = p.z; w = p.w; return *this; }

		inline Point<4, T>& operator+=(const Vector<4, T>& v)
		{ x += v.x; y += v.y; z += v.z; w += v.w; return *this; }

		inline Point<4, T>& operator-=(const Vector<4, T>& v)
		{ x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }

		inline Point<4, T>& operator*=(T scale)
		{ x *= scale; y *= scale; z *= scale; w *= scale; return *this; }

		inline Point<4, T>& operator/=(T scale)
		{
			const T revS = static_cast<T>(1.0f / scale);
			x *= revS; y *= revS; z *= revS; w *= revS; return *this;
		}
#pragma endregion

		//=== Relational Operators ===
#pragma region RelationalOperators
		inline bool operator==(const Point<4, T>& p) const
		{ return AreEqual<T>(x, p.x) && AreEqual<T>(y, p.y) && AreEqual<T>(z, p.z) && AreEqual<T>(w, p.w); }

		inline bool operator!=(const Point<4, T>& p) const
		{ return !(*this == p);	}
#pragma endregion 

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		inline T operator[](uint8_t i) const
		{
			assert((i < 4) && "ERROR: index of Point4 [] operator is out of bounds!");
			return data[i];
		}

		inline T& operator[](uint8_t i)
		{
			assert((i < 4) && "ERROR: index of Point4 [] operator is out of bounds!");
			return data[i];
		}
#pragma endregion
	};
}
#endif