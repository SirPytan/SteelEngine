/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EPoint.h: base point struct + general point template functions
/*=============================================================================*/
#ifndef ELITE_MATH_POINT
#define	ELITE_MATH_POINT

namespace Elite
{
	//=== CORE POINT TYPE ===
	template<int N, typename T>
	struct Point
	{
		//=== Data ===
		T data[N];

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		inline T operator[](uint8_t i) const
		{
			assert((i < N) && "ERROR: index of Vector [] operator is out of bounds!");
			return data[i];
		}

		inline T& operator[](uint8_t i)
		{
			assert((i < N) && "ERROR: index of Vector [] operator is out of bounds!");
			return data[i];
		}
#pragma endregion
	};

	template<int N, typename T>
	inline T SqrDistance(const Point<N, T>& p1, const Point<N, T>& p2)
	{
		const Vector<N, T> diff = p2 - p1;
		return SqrMagnitude(diff);
	}

	template<int N, typename T>
	inline T Distance(const Point<N, T>& p1, const Point<N, T>& p2)
	{ return static_cast<T>(sqrt(SqrDistance(p1, p2))); }
}
#endif