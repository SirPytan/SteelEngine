/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EVector.h: base Vector struct + general vector template functions
/*=============================================================================*/
#ifndef ELITE_MATH_VECTOR
#define	ELITE_MATH_VECTOR

namespace Elite
{
	//=== CORE VECTOR TYPE ===
	template<int N, typename T>
	struct Vector
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
	inline T SqrMagnitude(const Vector<N, T>& v)
	{ return Dot(v, v); }

	//Euclidean Norm (expect definition of Euclidean Inner Product - Dot Product)
	template<int N, typename T>
	inline T Magnitude(const Vector<N, T>& v) 
	{ return static_cast<T>(sqrt(SqrMagnitude(v))); }

	template<int N, typename T>
	inline T Normalize(Vector<N, T>& v)
	{
		const T m = Magnitude(v);
		if (AreEqual(m, static_cast<T>(0)))
		{
			v = Vector<N,T>();
			return m;
		}

		const T invM = static_cast<T>(1.f / m);
		v *= invM;
		return m;
	}

	template<int N, typename T>
	inline Vector<N, T> GetNormalized(const Vector<N, T>& v) //Get a copy of the original vector but normalized
	{
		Vector<N, T> cv = Vector<N, T>(v);
		Normalize(cv);
		return cv;
	}

	//Projects v onto t
	template<int N, typename T>
	inline Vector<N, T> Project(const Vector<N, T>& v, const Vector<N, T>& t)
	{ return t * (Dot(v,t)/ SqrMagnitude(t)); }

	//Returns the perpendicular vector of projection of v onto t
	template<int N, typename T>
	inline Vector<N, T> Reject(const Vector<N, T>& v, const Vector<N, T>& t)
	{ return v - Project(v, t); }

	template<int N, typename T>
	inline Vector<N, T> Reflect(const Vector<N, T>& d, const Vector<N, T>& n)
	{ return -d + static_cast<T>(2) * Dot(d, n) * n; }

	//Returns angle from v1 to v2 in radians
	template<int N, typename T>
	inline T GetAngle(const Vector<N, T>& v1, const Vector<N, T>& v2)
	{ return acos(Dot(v1, v2) / (Magnitude(v1)*Magnitude(v2))); }

	template<int N, typename T>
	inline T GetSignedAngle(const Vector<N, T>& v1, const Vector<N, T>& v2, const Vector<N, T>& axis)
	{ return asin((Dot(Cross(axis, v1), v2)) / (Magnitude(v1)*Magnitude(v2))); }

	template<int N, typename T>
	inline Vector<N, T> Lerp(float t, const Vector<N, T>& v1, const Vector<N, T>& v2)
	{ return v2 + ((v2 - v1) * static_cast<T>(t)); }
}
#endif