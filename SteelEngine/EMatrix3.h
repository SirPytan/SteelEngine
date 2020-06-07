/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EMatrix3.h: Column Major Matrix3x3 struct
/*=============================================================================*/
#ifndef ELITE_MATH_MATRIX3
#define	ELITE_MATH_MATRIX3

#include "EMatrix.h"
#include "EVector.h"
#include "EMathUtilities.h"

namespace Elite
{
	//=== MATRIX3x3 SPECIALIZATION ===
	template<typename T>
	struct Matrix<3, 3, T>
	{		
		//=== Data ===
		T data[3][3];

		//=== Constructors ===
#pragma region Constructors
		Matrix<3, 3, T>() = default;
		//Every "row" of values passed here is a row in our matrix!
		Matrix<3, 3, T>(T _00, T _01, T _02,
						T _10, T _11, T _12,
						T _20, T _21, T _22)
		{
			data[0][0] = _00; data[0][1] = _10; data[0][2] = _20;
			data[1][0] = _01; data[1][1] = _11; data[1][2] = _21;
			data[2][0] = _02; data[2][1] = _12; data[2][2] = _22;
		}
		//Every vector passed here is a column in our matrix!
		Matrix<3, 3, T>(const Vector<3, T>& a, const Vector<3, T>& b, const Vector<3, T>& c)
		{
			data[0][0] = a.x; data[0][1] = a.y; data[0][2] = a.z;
			data[1][0] = b.x; data[1][1] = b.y; data[1][2] = b.z;
			data[2][0] = c.x; data[2][1] = c.y; data[2][2] = c.z;
		}
		Matrix<3, 3, T>(const Matrix<2, 2, T>& m)
		{
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = 0;
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = 0;
			data[2][0] = 0; data[2][1] = 0; data[2][2] = 1;
		}
		Matrix<3, 3, T>(const Matrix<3, 3, T>& m)
		{
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = m.data[0][2];
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = m.data[1][2];
			data[2][0] = m.data[2][0]; data[2][1] = m.data[2][1]; data[2][2] = m.data[2][2];
		}
		Matrix<3, 3, T>(const Matrix<4, 4, T>& m)
		{
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = m.data[0][2];
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = m.data[1][2];
			data[2][0] = m.data[2][0]; data[2][1] = m.data[2][1]; data[2][2] = m.data[2][2];
		}
		Matrix<3, 3, T>(Matrix<3, 3, T>&& m) noexcept
		{
			data[0][0] = std::move(m.data[0][0]); data[0][1] = std::move(m.data[0][1]); data[0][2] = std::move(m.data[0][2]);
			data[1][0] = std::move(m.data[1][0]); data[1][1] = std::move(m.data[1][1]); data[1][2] = std::move(m.data[1][2]);
			data[2][0] = std::move(m.data[2][0]); data[2][1] = std::move(m.data[2][1]); data[2][2] = std::move(m.data[2][2]);
		}
		Matrix<3, 3, T>(Matrix<4, 4, T>&& m) noexcept
		{
			data[0][0] = std::move(m.data[0][0]); data[0][1] = std::move(m.data[0][1]); data[0][2] = std::move(m.data[0][2]);
			data[1][0] = std::move(m.data[1][0]); data[1][1] = std::move(m.data[1][1]); data[1][2] = std::move(m.data[1][2]);
			data[2][0] = std::move(m.data[2][0]); data[2][1] = std::move(m.data[2][1]); data[2][2] = std::move(m.data[2][2]);
		}
#pragma endregion

		//=== Arithmetic Operators ===
#pragma region ArithmeticOperators
		inline Matrix<3, 3, T> operator+(const Matrix<3, 3, T>& m) const
		{ 
			return Matrix<3, 3, T>(
				data[0][0] + m.data[0][0], data[0][1] + m.data[0][1], data[0][2] + m.data[0][2],
				data[1][0] + m.data[1][0], data[1][1] + m.data[1][1], data[1][2] + m.data[1][2],
				data[2][0] + m.data[2][0], data[2][1] + m.data[2][1], data[2][2] + m.data[2][2]);
		}

		inline Matrix<3, 3, T> operator-(const Matrix<3, 3, T>& m) const
		{ 
			return Matrix<3, 3, T>(
				data[0][0] - m.data[0][0], data[0][1] - m.data[0][1], data[0][2] - m.data[0][2],
				data[1][0] - m.data[1][0], data[1][1] - m.data[1][1], data[1][2] - m.data[1][2],
				data[2][0] - m.data[2][0], data[2][1] - m.data[2][1], data[2][2] - m.data[2][2]);
		}

		template<typename U>
		inline Matrix<3, 3, T> operator*(U scale) const
		{
			const T s = static_cast<T>(scale);
			return Matrix<3, 3, T>(
				data[0][0] * s, data[0][1] * s, data[0][2] * s,
				data[1][0] * s, data[1][1] * s, data[1][2] * s,
				data[2][0] * s, data[2][1] * s, data[2][2] * s);
		}

		template<typename U>
		inline Matrix<3, 3, T> operator/(U scale) const
		{
			const T revS = static_cast<T>(1.0f / scale);
			return Matrix<3, 3, T>(
				data[0][0] * revS, data[0][1] * revS, data[0][2] * revS,
				data[1][0] * revS, data[1][1] * revS, data[1][2] * revS,
				data[2][0] * revS, data[2][1] * revS, data[2][2] * revS);
		}

		inline Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& rm)
		{
			const Matrix<3, 3, T>& lm = (*this);
			return Matrix<3, 3, T>(
				lm(0, 0) * rm(0, 0) + lm(0, 1) * rm(1, 0) + lm(0, 2) * rm(2, 0),
				lm(0, 0) * rm(0, 1) + lm(0, 1) * rm(1, 1) + lm(0, 2) * rm(2, 1),
				lm(0, 0) * rm(0, 2) + lm(0, 1) * rm(1, 2) + lm(0, 2) * rm(2, 2),
				
				lm(1, 0) * rm(0, 0) + lm(1, 1) * rm(1, 0) + lm(1, 2) * rm(2, 0),
				lm(1, 0) * rm(0, 1) + lm(1, 1) * rm(1, 1) + lm(1, 2) * rm(2, 1),
				lm(1, 0) * rm(0, 2) + lm(1, 1) * rm(1, 2) + lm(1, 2) * rm(2, 2),
				
				lm(2, 0) * rm(0, 0) + lm(2, 1) * rm(1, 0) + lm(2, 2) * rm(2, 0),
				lm(2, 0) * rm(0, 1) + lm(2, 1) * rm(1, 1) + lm(2, 2) * rm(2, 1),
				lm(2, 0) * rm(0, 2) + lm(2, 1) * rm(1, 2) + lm(2, 2) * rm(2, 2));
		}

		inline Vector<3, T> operator*(const Vector<3, T>& v)
		{
			const Matrix<3, 3, T>& m = (*this);
			return Vector<3, T>(
				m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
				m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
				m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z);
		}

		inline Point<3, T> operator*(const Point<3, T>& p)
		{
			const Matrix<3, 3, T>& m = (*this);
			return Point<3, T>(
				m(0, 0) * p.x + m(0, 1) * p.y + m(0, 2),
				m(1, 0) * p.x + m(1, 1) * p.y + m(1, 2), 1);
		}
#pragma endregion

		//=== Compound Assignment Operators ===
#pragma region CompoundAssignmentOperators
		inline Matrix<3, 3, T>& operator=(const Matrix<3, 3, T>& m)
		{ 
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = m.data[0][2];
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = m.data[1][2];
			data[2][0] = m.data[2][0]; data[2][1] = m.data[2][1]; data[2][2] = m.data[2][2];
			return *this; 
		}

		inline Matrix<3, 3, T>& operator+=(const Matrix<3, 3, T>& m)
		{ 
			data[0][0] += m.data[0][0]; data[0][1] += m.data[0][1]; data[0][2] += m.data[0][2];
			data[1][0] += m.data[1][0]; data[1][1] += m.data[1][1]; data[1][2] += m.data[1][2];
			data[2][0] += m.data[2][0]; data[2][1] += m.data[2][1]; data[2][2] += m.data[2][2];
			return *this; 
		}

		inline Matrix<3, 3, T>& operator-=(const Matrix<3, 3, T>& m)
		{ 
			data[0][0] -= m.data[0][0]; data[0][1] -= m.data[0][1]; data[0][2] -= m.data[0][2];
			data[1][0] -= m.data[1][0]; data[1][1] -= m.data[1][1]; data[1][2] -= m.data[1][2];
			data[2][0] -= m.data[2][0]; data[2][1] -= m.data[2][1]; data[2][2] -= m.data[2][2];
			return *this; 
		}

		template<typename U>
		inline Matrix<3, 3, T>& operator*=(U scale)
		{
			const T s = static_cast<T>(scale);
			data[0][0] *= s; data[0][1] *= s; data[0][2] *= s;
			data[1][0] *= s; data[1][1] *= s; data[1][2] *= s;
			data[2][0] *= s; data[2][1] *= s; data[2][2] *= s;
			return *this;
		}

		template<typename U>
		inline Matrix<3, 3, T>& operator/=(U scale)
		{
			const T revS = static_cast<T>(1.0f / scale);
			data[0][0] *= revS; data[0][1] *= revS; data[0][2] *= revS;
			data[1][0] *= revS; data[1][1] *= revS; data[1][2] *= revS;
			data[2][0] *= revS; data[2][1] *= revS; data[2][2] *= revS;
			return *this;
		}

		inline Matrix<3, 3, T>& operator*=(const Matrix<3, 3, T>& m)
		{
			//Copy is necessary! :( 
			*this = *this * m;
			return *this;
		}
#pragma endregion

		//=== Relational Operators ===
#pragma region RelationalOperators
		inline bool operator==(const Matrix<3, 3, T>& m) const
		{ return ((*this)[0] == m[0]) && ((*this)[1] == m[1]) && ((*this)[2] == m[2]); }

		inline bool operator!=(const Matrix<3, 3, T>& m) const
		{ return !(*this == m); }
#pragma endregion 

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		//Access parameter order still happens as row,column indexing (standard in programming)
		inline T operator()(uint8_t r, uint8_t c) const
		{
			assert((r < 3 && c < 3) && "ERROR: indices of Matrix3x3 () const operator are out of bounds!");
			return (data[c][r]);
		}

		inline T& operator()(uint8_t r, uint8_t c)
		{
			assert((r < 3 && c < 3) && "ERROR: indices of Matrix3x3 () operator are out of bounds!");
			return (data[c][r]);
		}

		//Get a vector representation of a column (usage), but internally returns one of the rows
		inline const Vector<3, T>& operator[](uint8_t c) const
		{
			assert((c < 3) && "ERROR: index of Matrix3x3 [] operator is out of bounds!");
			return *((Vector<3, T>*)data[c]);
		}

		inline Vector<3, T>& operator[](uint8_t c)
		{
			assert((c < 3) && "ERROR: index of Matrix3x3 [] operator is out of bounds!");
			return *((Vector<3, T>*)data[c]);
		}
#pragma endregion

		//=== Static Functions ===
		static Matrix<3, 3, T> Identity();
	};

	//--- VECMATRIX3 FUNCTIONS ---
#pragma region GlobalOperators
#pragma endregion

#pragma region GlobalFunctions
	template<typename T>
	inline Matrix<3, 3, T> Matrix<3, 3, T>::Identity()
	{
		return Matrix<3, 3, T>(
			1,0,0,
			0,1,0,
			0,0,1);
	}

	template<typename T>
	inline Matrix<3, 3, T> Transpose(const Matrix<3, 3, T>& m)
	{
		Matrix<3, 3, T> t = {};
		t(0, 0) = m(0, 0);
		t(0, 1) = m(1, 0);
		t(0, 2) = m(2, 0);
		t(1, 0) = m(0, 1);
		t(1, 1) = m(1, 1);
		t(1, 2) = m(2, 1);
		t(2, 0) = m(0, 2);
		t(2, 1) = m(1, 2);
		t(2, 2) = m(2, 2);
		return t;
	}

	template<typename T>
	inline T Determinant(const Matrix<3, 3, T>& m)
	{
		return 
			+ m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1))
			- m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0))
			+ m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
	}

	template<typename T>
	inline Matrix<3, 3, T> Inverse(const Matrix<3, 3, T>& m)
	{
		//Optimized Inverse as explained in FGED1 - used widely in other libraries too.
		//This avoids the unnecessary calculation of all the cofactors as for the determinant! -> See below in comment
		const Vector<3, T>& a = m[0];
		const Vector<3, T>& b = m[1];
		const Vector<3, T>& c = m[2];

		Vector<3, T> r0 = Cross(b, c);
		Vector<3, T> r1 = Cross(c, a);
		Vector<3, T> r2 = Cross(a, b);

		T det = Dot(r2, c);
		assert((!AreEqual(det, static_cast<T>(0))) && "ERROR: determinant is 0, there is no INVERSE!");
		T invDet = static_cast<T>(1.0f / det);

		return Matrix<3, 3, T>(
			r0.x * invDet, r0.y * invDet, r0.z * invDet,
			r1.x * invDet, r1.y * invDet, r1.z * invDet,
			r2.x * invDet, r2.y * invDet, r2.z * invDet);

		/* //----- Approach with cofactors ------
		T invDet = static_cast<T>(1.0f / Determinant(m));
		Matrix<3, 3, T> inv = {};
		inv(0, 0) = +(m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) * invDet;
		inv(0, 1) = -(m(0, 1) * m(2, 2) - m(0, 2) * m(2, 1)) * invDet;
		inv(0, 2) = +(m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invDet;
		inv(1, 0) = -(m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) * invDet;
		inv(1, 1) = +(m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invDet;
		inv(1, 2) = -(m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) * invDet;
		inv(2, 0) = +(m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)) * invDet;
		inv(2, 1) = -(m(0, 0) * m(2, 1) - m(0, 1) * m(2, 0)) * invDet;
		inv(2, 2) = +(m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * invDet;
		return inv;
		*/
	}

	//Rotations with a positive angle are considered a counterclockwise rotations around the axis pointing towards
	//the viewer. Think of the axis as the "normal" of the planes (x -> yz-plane, y -> xz-plane , z -> xy-plane)!
	template<typename T>
	inline Matrix<3, 3, T> MakeRotationX(T t)
	{
		T c = static_cast<T>(cos(t));
		T s = static_cast<T>(sin(t));

		return Matrix<3, 3, T>(
			static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
			static_cast<T>(0), c, -s,
			static_cast<T>(0), s, c);
	}

	template<typename T>
	inline Matrix<3, 3, T> MakeRotationY(T t)
	{
		T c = static_cast<T>(cos(t));
		T s = static_cast<T>(sin(t));

		return Matrix<3, 3, T>(
			c, static_cast<T>(0), s,
			static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
			-s, static_cast<T>(0), c);
	}

	template<typename T>
	inline Matrix<3, 3, T> MakeRotationZ(T t)
	{
		T c = static_cast<T>(cos(t));
		T s = static_cast<T>(sin(t));

		return Matrix<3, 3, T>(
			c, -s, static_cast<T>(0),
			s, c, static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	template<typename T>
	inline Matrix<3, 3, T> MakeRotationZYX(T x, T y, T z)
	{
		Matrix<3, 3, T> mX = MakeRotationX(x);
		Matrix<3, 3, T> mY = MakeRotationY(y);
		Matrix<3, 3, T> mZ = MakeRotationZ(z);
		return mZ * mY * mX;
	}

	template<typename T>
	inline Matrix<3, 3, T> MakeRotation(T t, const Vector<3, T>& axis)
	{
		T c = static_cast<T>(cos(t));
		T s = static_cast<T>(sin(t));
		T oneMinusC = static_cast<T>(1 - c);

		T xy = axis.x * axis.y;
		T yz = axis.y * axis.z;
		T xz = axis.x * axis.z;
		T sx = s * axis.x;
		T sy = s * axis.y;
		T sz = s * axis.z;

		return Matrix<3, 3, T>(
			c + oneMinusC * (axis.x * axis.x), oneMinusC * xy - sz, oneMinusC * xz + sy,
			oneMinusC * xy + sz, c + oneMinusC * (axis.y * axis.y), oneMinusC * yz - sx,
			oneMinusC * xz - sy, oneMinusC * yz + sx, c + oneMinusC * (axis.z * axis.z));
	}

	template<typename T>
	inline Matrix<3, 3, T> MakeScale(T x, T y, T z)
	{
		return Matrix<3, 3, T>(
			x, static_cast<T>(0), static_cast<T>(0),
			static_cast<T>(0), y, static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(0), z);
	}

	template<typename T>
	inline Matrix<3, 3, T> MakeScale(T s, const Vector<3, T>& axis)
	{
		T sMinusOne = s - static_cast<T>(1);
		T xy = axis.x * axis.y;
		T yz = axis.y * axis.z;
		T xz = axis.x * axis.z;

		return Matrix<3, 3, T>(
			sMinusOne * (axis.x * axis.x) + 1, sMinusOne * xy, sMinusOne * xz,
			sMinusOne * xy, sMinusOne * (axis.y * axis.y) + 1, sMinusOne * yz,
			sMinusOne * xz, sMinusOne * yz, sMinusOne * (axis.z * axis.z) + 1);
	}

	template<typename T>
	inline Matrix<3, 3, T> MakeTranslation(const Vector<2, T>& v)
	{
		return Matrix<3, 3, T>(
			1, 0, v.x,
			0, 1, v.y,
			0, 0, 1);
	}

	//Can be used to change from right-handed coordinate system (the "assumption" of these rotation matrices is
	//a right-handed system) to a left-handed coordinate system.
	template<typename T>
	inline Matrix<3, 3, T> MakeReflection(const Vector<3, T>& axis)
	{
		T xy = axis.x * axis.y;
		T yz = axis.y * axis.z;
		T xz = axis.x * axis.z;

		return Matrix<3, 3, T>(
			1 - 2 * (axis.x * axis.x), -2 * xy, -2 * xz,
			-2 * xy, 1 - 2 * (axis.y * axis.y), -2 * yz,
			-2 * xz, -2 * yz, 1 - 2 * (axis.z * axis.z));
	}
#pragma endregion
}
#endif