/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EPoint.h: Point3D struct
/*=============================================================================*/
#ifndef ELITE_MATH_POINT3
#define	ELITE_MATH_POINT3

#include "EPoint.h"
#include "EVector.h"
#include "EMathUtilities.h"

namespace Elite
{
	//=== POINT3 SPECIALIZATION ===
	template<typename T>
	struct Point<3, T>
	{
		//=== Data ===
#pragma warning(disable : 4201)
		union
		{
			T data[3];
			struct { T x, y, z; };
			Point<2, T> xy;
		};
#pragma warning(default : 4201)

		//=== Constructors ===
#pragma region Constructors
		Point<3, T>() = default;
		Point<3, T>(T _x, T _y, T _z = 1)
			: x(_x), y(_y), z(_z) {}
		Point<3, T>(const Point<3, T>& p)
			: x(p.x), y(p.y), z(p.z) {}
		Point<3, T>(const Point<2, T>& p, T _z = 1)
			: x(p.x), y(p.y), z(_z) {}
		Point<3, T>(Point<3, T>&& p) noexcept
			:x(std::move(p.x)), y(std::move(p.y)), z(std::move(p.z)) {}
		explicit Point<3, T>(const Vector<3, T>& v)
			: x(v.x), y(v.y), z(v.z) {}
		explicit Point<3, T>(const Point<4, T>& p)
			: x(p.x), y(p.y), z(p.z) {}
#pragma endregion

		//=== Conversion Operator ===
#pragma region ConversionOperator
		template<typename U>
		operator Point<3, U>() const //Implicit conversion to different types of Point3
		{
			return Point<3, U>(
				static_cast<U>(this->x),
				static_cast<U>(this->y),
				static_cast<U>(this->z));
		}
#pragma endregion

		//=== Arithmetic Operators ===
#pragma region ArithmeticOperators
		template<typename U>
		inline Point<3, T> operator+(const Vector<3, U>& v) const
		{ return Point<3, T>(x + static_cast<T>(v.x), y + static_cast<T>(v.y), z + static_cast<T>(v.z)); }

		template<typename U>
		inline Point<3, T> operator-(const Vector<3, U>& v) const
		{ return Point<3, T>(x - static_cast<T>(v.x), y - static_cast<T>(v.y), z - static_cast<T>(v.z)); }

		template<typename U>
		inline Vector<3, T> operator-(const Point<3, U>& p) const
		{ return Vector<3, T>(x - static_cast<T>(p.x), y - static_cast<T>(p.y), z - static_cast<T>(p.z)); }

		inline Point<3, T> operator*(T scale) const
		{ return Point<3, T>(x * scale, y * scale, z * scale); }

		inline Point<3, T> operator/(T scale) const
		{
			const T revS = static_cast<T>(1.0f / scale);
			return Point<3, T>(x * revS, y * revS, z * revS);
		}
#pragma endregion

		//=== Compound Assignment Operators ===
#pragma region CompoundAssignmentOperators
		inline Point<3, T>& operator=(const Point<3, T>& p)
		{ x = p.x; y = p.y; z = p.z; return *this; }

		inline Point<3, T>& operator+=(const Vector<3, T>& v)
		{ x += v.x; y += v.y; z += v.z; return *this; }

		inline Point<3, T>& operator-=(const Vector<3, T>& v)
		{ x -= v.x; y -= v.y; z -= v.z; return *this; }

		inline Point<3, T>& operator*=(T scale)
		{ x *= scale; y *= scale; z *= scale; return *this;	}

		inline Point<3, T>& operator/=(T scale)
		{
			const T revS = static_cast<T>(1.0f / scale);
			x *= revS; y *= revS; z *= revS; return *this;
		}
#pragma endregion

		//=== Relational Operators ===
#pragma region RelationalOperators
		inline bool operator==(const Point<3, T>& p) const
		{ return AreEqual<T>(x, p.x) && AreEqual<T>(y, p.y) && AreEqual<T>(z, p.z); }

		inline bool operator!=(const Point<3, T>& p) const
		{ return !(*this == p);	}
#pragma endregion 

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		inline T operator[](uint8_t i) const
		{
			assert((i < 3) && "ERROR: index of Point3 [] operator is out of bounds!");
			return data[i];
		}

		inline T& operator[](uint8_t i)
		{
			assert((i < 3) && "ERROR: index of Point3 [] operator is out of bounds!");
			return data[i];
		}
#pragma endregion
	};
}
#endif