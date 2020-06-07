/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EVector4.h: Vector4D struct
/*=============================================================================*/
#ifndef ELITE_MATH_VECTOR4
#define	ELITE_MATH_VECTOR4

#include "EVector.h"
#include "EPoint.h"
#include "EMathUtilities.h"

namespace Elite
{
	//=== VECTOR4 SPECIALIZATION ===
	template<typename T>
	struct Vector<4, T>
	{
		//=== Data ===
#pragma warning(disable : 4201)
		union
		{
			T data[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			Vector<2, T> xy;
			Vector<3, T> xyz;
			Vector<2, T> rg;
			Vector<3, T> rgb;
		};
#pragma warning(default : 4201)

		//=== Constructors ===
#pragma region Constructors
		Vector<4, T>() = default;
		Vector<4, T>(T _x, T _y, T _z, T _w = 0) //W component of Vector is usually 0
			: x(_x), y(_y), z(_z), w(_w) {}
		Vector<4, T>(const Vector<2, T> v, T _z, T _w = 0)
			: x(v.x), y(v.y), z(_z), w(_w) {}
		Vector<4, T>(const Vector<3, T> v, T _w = 0)
			: x(v.x), y(v.y), z(v.z), w(_w) {}
		Vector<4, T>(const Vector<4, T>& v)
			: x(v.x), y(v.y), z(v.z), w(v.w) {}
		Vector<4, T>(Vector<4, T>&& v) noexcept
			:x(std::move(v.x)), y(std::move(v.y)), z(std::move(v.z)), w(std::move(v.w)) {}
		explicit Vector<4, T>(const Point<4, T>& p)
			: x(p.x), y(p.y), z(p.z), w(p.w) {}
#pragma endregion

		//=== Conversion Operator ===
#pragma region ConversionOperator
		template<typename U>
		operator Vector<4, U>() const //Implicit conversion to different types of Vector4
		{
			return Vector<4, U>(
				static_cast<U>(this->x),
				static_cast<U>(this->y),
				static_cast<U>(this->z),
				static_cast<U>(this->w));
		}
#pragma endregion

		//=== Arithmetic Operators ===
#pragma region ArithmeticOperators
		template<typename U>
		inline Vector<4, T> operator+(const Vector<4, U>& v) const
		{ return Vector<4, T>(x + static_cast<T>(v.x), y + static_cast<T>(v.y), 
			z + static_cast<T>(v.z), w + static_cast<T>(v.w)); }

		template<typename U>
		inline Vector<4, T> operator-(const Vector<4, U>& v) const
		{ return Vector<4, T>(x - static_cast<T>(v.x), y - static_cast<T>(v.y),
			z - static_cast<T>(v.z), w - static_cast<T>(v.w)); }

		inline Vector<4, T> operator*(T scale) const
		{ return Vector<4, T>(x * scale, y * scale, z * scale, w * scale); }

		inline Vector<4, T> operator/(T scale) const
		{
			const T revS = static_cast<T>(1.0f / scale);
			return Vector<4, T>(x * revS, y * revS, z * revS, w * revS);
		}
#pragma endregion

		//=== Compound Assignment Operators ===
#pragma region CompoundAssignmentOperators
		inline Vector<4, T>& operator=(const Vector<4, T>& v)
		{ x = v.x; y = v.y; z = v.z; w = v.w; return *this;	}

		inline Vector<4, T>& operator+=(const Vector<4, T>& v)
		{ x += v.x; y += v.y; z += v.z; w += v.w; return *this;	}

		inline Vector<4, T>& operator-=(const Vector<4, T>& v)
		{ x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }

		inline Vector<4, T>& operator*=(T scale)
		{ x *= scale; y *= scale; z *= scale; w *= scale; return *this;	}

		inline Vector<4, T>& operator/=(T scale)
		{
			const T revS = static_cast<T>(1.0f / scale);
			x *= revS; y *= revS; z *= revS; w *= revS; return *this;
		}
#pragma endregion

		//=== Unary Operators ===
#pragma region UnaryOperators
		inline Vector<4, T>& operator-() const
		{ return Vector<4, T>(-x, -y, -z, -w); }
#pragma endregion

		//=== Relational Operators ===
#pragma region RelationalOperators
		inline bool operator==(const Vector<4, T>& v) const
		{ return AreEqual<T>(x, v.x) && AreEqual<T>(y, v.y) && AreEqual<T>(z, v.z) && AreEqual<T>(w, v.w); }

		inline bool operator!=(const Vector<4, T>& v) const
		{ return !(*this == v);	}
#pragma endregion 

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		inline T operator[](uint8_t i) const
		{
			assert((i < 4) && "ERROR: index of Vector4 [] operator is out of bounds!");
			return data[i];
		}

		inline T& operator[](uint8_t i)
		{
			assert((i < 4) && "ERROR: index of Vector4 [] operator is out of bounds!");
			return data[i];
		}
#pragma endregion

		//=== Static Functions ===
		static Vector<4, T> ZeroVector();
	};

	//--- VECTOR4 FUNCTIONS ---
#pragma region GlobalOperators
	template<typename T, typename U>
	inline Vector<4, T> operator*(U scale, const Vector<4, T>& v)
	{ 
		T s = static_cast<T>(scale);
		return Vector<4, T>(v.x * s, v.y * s, v.z * s, v.w * s); 
	}
#pragma endregion

#pragma region GlobalFunctions
	template<typename T>
	inline Vector<4, T> Vector<4, T>::ZeroVector()
	{
		T z = static_cast<T>(0);
		return Vector<4, T>(z, z, z, z);
	}

	template<typename T>
	inline T Dot(const Vector<4, T>& v1, const Vector<4, T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template<typename T>
	inline Vector<4, T> GetAbs(const Vector<4, T>& v)
	{ return Vector<4, T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w)); }

	template<typename T>
	inline Vector<4, T> Max(const Vector<4, T>& v1, const Vector<4, T>& v2)
	{
		Vector<4, T>v = v1;
		if (v2.x > v.x) v.x = v2.x;
		if (v2.y > v.y) v.y = v2.y;
		if (v2.z > v.z) v.z = v2.z;
		if (v2.w > v.w) v.w = v2.w;
		return v;
	}

	template<typename T>
	inline Vector<4, T> Min(const Vector<4, T>& v1, const Vector<4, T>& v2)
	{
		Vector<4, T>v = v1;
		if (v2.x < v.x) v.x = v2.x;
		if (v2.y < v.y) v.y = v2.y;
		if (v2.z < v.z) v.z = v2.z;
		if (v2.w < v.w) v.w = v2.w;
		return v;
	}
#pragma endregion
}
#endif