/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EMatrix4.h: Column Major Matrix4x4 struct
/*=============================================================================*/
#ifndef ELITE_MATH_MATRIX4
#define	ELITE_MATH_MATRIX4

#include "EMatrix.h"
#include "EVector.h"
#include "EMathUtilities.h"

namespace Elite
{
	//=== MATRIX4x4 SPECIALIZATION ===
	template<typename T>
	struct Matrix<4, 4, T>
	{		
		//=== Data ===
		T data[4][4];

		//=== Constructors ===
#pragma region Constructors
		Matrix<4, 4, T>() = default;
		//Every "row" of values passed here is a row in our matrix!
		Matrix<4, 4, T>(T _00, T _01, T _02, T _03,
						T _10, T _11, T _12, T _13,
						T _20, T _21, T _22, T _23,
						T _30, T _31, T _32, T _33)
		{
			data[0][0] = _00; data[0][1] = _10; data[0][2] = _20; data[0][3] = _30;
			data[1][0] = _01; data[1][1] = _11; data[1][2] = _21; data[1][3] = _31;
			data[2][0] = _02; data[2][1] = _12; data[2][2] = _22; data[2][3] = _32;
			data[3][0] = _03; data[3][1] = _13; data[3][2] = _23; data[3][3] = _33;
		}
		//Every vector passed here is a column in our matrix!
		Matrix<4, 4, T>(const Vector<4, T>& a, const Vector<4, T>& b, const Vector<4, T>& c, const Vector<4, T>& d)
		{
			data[0][0] = a.x; data[0][1] = a.y; data[0][2] = a.z; data[0][3] = a.w;
			data[1][0] = b.x; data[1][1] = b.y; data[1][2] = b.z; data[1][3] = b.w;
			data[2][0] = c.x; data[2][1] = c.y; data[2][2] = c.z; data[2][3] = c.w;
			data[3][0] = d.x; data[3][1] = d.y; data[3][2] = d.z; data[3][3] = d.w;
		}
		Matrix<4, 4, T>(const Matrix<3, 3, T>& m, const Vector<3, T>& t)
		{
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = m.data[0][2]; data[0][3] = 0;
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = m.data[1][2]; data[1][3] = 0;
			data[2][0] = m.data[2][0]; data[2][1] = m.data[2][1]; data[2][2] = m.data[2][2]; data[2][3] = 0;
			data[3][0] = t.x; data[3][1] = t.y; data[3][2] = t.z; data[3][3] = 1;
		}
		Matrix<4, 4, T>(const Matrix<3, 3, T>& m)
		{
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = m.data[0][2]; data[0][3] = 0;
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = m.data[1][2]; data[1][3] = 0;
			data[2][0] = m.data[2][0]; data[2][1] = m.data[2][1]; data[2][2] = m.data[2][2]; data[2][3] = 0;
			data[3][0] = 0; data[3][1] = 0; data[3][2] = 0; data[3][3] = 1;
		}
		Matrix<4, 4, T>(const Matrix<4, 4, T>& m)
		{
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = m.data[0][2]; data[0][3] = m.data[0][3];
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = m.data[1][2]; data[1][3] = m.data[1][3];
			data[2][0] = m.data[2][0]; data[2][1] = m.data[2][1]; data[2][2] = m.data[2][2]; data[2][3] = m.data[2][3];
			data[3][0] = m.data[3][0]; data[3][1] = m.data[3][1]; data[3][2] = m.data[3][2]; data[3][3] = m.data[3][3];
		}
		Matrix<4, 4, T>(Matrix<4, 4, T>&& m) noexcept
		{
			data[0][0] = std::move(m.data[0][0]); data[0][1] = std::move(m.data[0][1]); 
			data[0][2] = std::move(m.data[0][2]); data[0][3] = std::move(m.data[0][3]);

			data[1][0] = std::move(m.data[1][0]); data[1][1] = std::move(m.data[1][1]); 
			data[1][2] = std::move(m.data[1][2]); data[1][3] = std::move(m.data[1][3]);

			data[2][0] = std::move(m.data[2][0]); data[2][1] = std::move(m.data[2][1]); 
			data[2][2] = std::move(m.data[2][2]); data[2][3] = std::move(m.data[2][3]);

			data[3][0] = std::move(m.data[3][0]); data[3][1] = std::move(m.data[3][1]);
			data[3][2] = std::move(m.data[3][2]); data[3][3] = std::move(m.data[3][3]);
		}
#pragma endregion

		//=== Arithmetic Operators ===
#pragma region ArithmeticOperators
		inline Matrix<4, 4, T> operator+(const Matrix<4, 4, T>& m) const
		{ 
			return Matrix<4, 4, T>(
				data[0][0] + m.data[0][0], data[0][1] + m.data[0][1], data[0][2] + m.data[0][2], data[0][3] + m.data[0][3],
				data[1][0] + m.data[1][0], data[1][1] + m.data[1][1], data[1][2] + m.data[1][2], data[1][3] + m.data[1][3],
				data[2][0] + m.data[2][0], data[2][1] + m.data[2][1], data[2][2] + m.data[2][2], data[2][3] + m.data[2][3],
				data[3][0] + m.data[3][0], data[3][1] + m.data[3][1], data[3][2] + m.data[3][2], data[3][3] + m.data[3][3]);
		}

		inline Matrix<4, 4, T> operator-(const Matrix<4, 4, T>& m) const
		{ 
			return Matrix<4, 4, T>(
				data[0][0] - m.data[0][0], data[0][1] - m.data[0][1], data[0][2] - m.data[0][2], data[0][3] - m.data[0][3],
				data[1][0] - m.data[1][0], data[1][1] - m.data[1][1], data[1][2] - m.data[1][2], data[1][3] - m.data[1][3],
				data[2][0] - m.data[2][0], data[2][1] - m.data[2][1], data[2][2] - m.data[2][2], data[2][3] - m.data[2][3],
				data[3][0] - m.data[3][0], data[3][1] - m.data[3][1], data[3][2] - m.data[3][2], data[3][3] - m.data[3][3]);
		}

		template<typename U>
		inline Matrix<4, 4, T> operator*(U scale) const
		{
			const T s = static_cast<T>(scale);
			return Matrix<4, 4, T>(
				data[0][0] * s, data[0][1] * s, data[0][2] * s, data[0][3] * s,
				data[1][0] * s, data[1][1] * s, data[1][2] * s, data[1][3] * s,
				data[2][0] * s, data[2][1] * s, data[2][2] * s, data[2][3] * s, 
				data[3][0] * s, data[3][1] * s, data[3][2] * s, data[3][3] * s);
		}

		template<typename U>
		inline Matrix<4, 4, T> operator/(U scale) const
		{
			const T revS = static_cast<T>(1.0f / scale);
			return Matrix<4, 4, T>(
				data[0][0] * revS, data[0][1] * revS, data[0][2] * revS, data[0][3] * revS,
				data[1][0] * revS, data[1][1] * revS, data[1][2] * revS, data[1][3] * revS,
				data[2][0] * revS, data[2][1] * revS, data[2][2] * revS, data[2][3] * revS,
				data[3][0] * revS, data[3][1] * revS, data[3][2] * revS, data[3][3] * revS);
		}

		inline Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& rm) const
		{
			const Matrix<4, 4, T>& lm = (*this);
			return Matrix<4, 4, T>(
				lm(0, 0) * rm(0, 0) + lm(0, 1) * rm(1, 0) + lm(0, 2) * rm(2, 0) + lm(0, 3) * rm(3, 0),
				lm(0, 0) * rm(0, 1) + lm(0, 1) * rm(1, 1) + lm(0, 2) * rm(2, 1) + lm(0, 3) * rm(3, 1),
				lm(0, 0) * rm(0, 2) + lm(0, 1) * rm(1, 2) + lm(0, 2) * rm(2, 2) + lm(0, 3) * rm(3, 2),
				lm(0, 0) * rm(0, 3) + lm(0, 1) * rm(1, 3) + lm(0, 2) * rm(2, 3) + lm(0, 3) * rm(3, 3),

				lm(1, 0) * rm(0, 0) + lm(1, 1) * rm(1, 0) + lm(1, 2) * rm(2, 0) + lm(1, 3) * rm(3, 0),
				lm(1, 0) * rm(0, 1) + lm(1, 1) * rm(1, 1) + lm(1, 2) * rm(2, 1) + lm(1, 3) * rm(3, 1),
				lm(1, 0) * rm(0, 2) + lm(1, 1) * rm(1, 2) + lm(1, 2) * rm(2, 2) + lm(1, 3) * rm(3, 2),
				lm(1, 0) * rm(0, 3) + lm(1, 1) * rm(1, 3) + lm(1, 2) * rm(2, 3) + lm(1, 3) * rm(3, 3),

				lm(2, 0) * rm(0, 0) + lm(2, 1) * rm(1, 0) + lm(2, 2) * rm(2, 0) + lm(2, 3) * rm(3, 0),
				lm(2, 0) * rm(0, 1) + lm(2, 1) * rm(1, 1) + lm(2, 2) * rm(2, 1) + lm(2, 3) * rm(3, 1),
				lm(2, 0) * rm(0, 2) + lm(2, 1) * rm(1, 2) + lm(2, 2) * rm(2, 2) + lm(2, 3) * rm(3, 2),
				lm(2, 0) * rm(0, 3) + lm(2, 1) * rm(1, 3) + lm(2, 2) * rm(2, 3) + lm(2, 3) * rm(3, 3),

				lm(3, 0) * rm(0, 0) + lm(3, 1) * rm(1, 0) + lm(3, 2) * rm(2, 0) + lm(3, 3) * rm(3, 0),
				lm(3, 0) * rm(0, 1) + lm(3, 1) * rm(1, 1) + lm(3, 2) * rm(2, 1) + lm(3, 3) * rm(3, 1),
				lm(3, 0) * rm(0, 2) + lm(3, 1) * rm(1, 2) + lm(3, 2) * rm(2, 2) + lm(3, 3) * rm(3, 2),
				lm(3, 0) * rm(0, 3) + lm(3, 1) * rm(1, 3) + lm(3, 2) * rm(2, 3) + lm(3, 3) * rm(3, 3));
		}

		//Reminder: when transforming normals (like vectors, so no translation), you have to multiply with
		//the transpose of the inverse of the original matrix, because they do not behave in the same way!
		//So vector transformation -> M * v , while normal transformation with same matrix -> inv(transp(M)) * n
		inline Vector<4, T> operator*(const Vector<4, T>& v) const
		{
			const Matrix<4, 4, T>& m = (*this);
			return Vector<4, T>(
				m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
				m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
				m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z, 0);
		}

		//Takes into account translation for a point.
		inline Point<4, T> operator*(const Point<4, T>& p) const
		{
			const Matrix<4, 4, T>& m = (*this);
			return Point<4, T>(
				m(0, 0) * p.x + m(0, 1) * p.y + m(0, 2) * p.z + m(0, 3),
				m(1, 0) * p.x + m(1, 1) * p.y + m(1, 2) * p.z + m(1, 3),
				m(2, 0) * p.x + m(2, 1) * p.y + m(2, 2) * p.z + m(2, 3), 
				m(3, 0) * p.x + m(3, 1) * p.y + m(3, 2) * p.z + m(3, 3));
		}
#pragma endregion

		//=== Compound Assignment Operators ===
#pragma region CompoundAssignmentOperators
		inline Matrix<4, 4, T>& operator=(const Matrix<4, 4, T>& m)
		{ 
			data[0][0] = m.data[0][0]; data[0][1] = m.data[0][1]; data[0][2] = m.data[0][2]; data[0][3] = m.data[0][3];
			data[1][0] = m.data[1][0]; data[1][1] = m.data[1][1]; data[1][2] = m.data[1][2]; data[1][3] = m.data[1][3];
			data[2][0] = m.data[2][0]; data[2][1] = m.data[2][1]; data[2][2] = m.data[2][2]; data[2][3] = m.data[2][3];
			data[3][0] = m.data[3][0]; data[3][1] = m.data[3][1]; data[3][2] = m.data[3][2]; data[3][3] = m.data[3][3];
			return *this; 
		}

		inline Matrix<4, 4, T>& operator+=(const Matrix<4, 4, T>& m)
		{ 
			data[0][0] += m.data[0][0]; data[0][1] += m.data[0][1]; data[0][2] += m.data[0][2]; data[0][3] += m.data[0][3];
			data[1][0] += m.data[1][0]; data[1][1] += m.data[1][1]; data[1][2] += m.data[1][2]; data[1][3] += m.data[1][3];
			data[2][0] += m.data[2][0]; data[2][1] += m.data[2][1]; data[2][2] += m.data[2][2]; data[2][3] += m.data[2][3];
			data[3][0] += m.data[3][0]; data[3][1] += m.data[3][1]; data[3][2] += m.data[3][2]; data[3][3] += m.data[3][3];
			return *this; 
		}

		inline Matrix<4, 4, T>& operator-=(const Matrix<4, 4, T>& m)
		{ 
			data[0][0] -= m.data[0][0]; data[0][1] -= m.data[0][1]; data[0][2] -= m.data[0][2]; data[0][3] -= m.data[0][3];
			data[1][0] -= m.data[1][0]; data[1][1] -= m.data[1][1]; data[1][2] -= m.data[1][2]; data[1][3] -= m.data[1][3];
			data[2][0] -= m.data[2][0]; data[2][1] -= m.data[2][1]; data[2][2] -= m.data[2][2]; data[2][3] -= m.data[2][3];
			data[3][0] -= m.data[3][0]; data[3][1] -= m.data[3][1]; data[3][2] -= m.data[3][2]; data[3][3] -= m.data[3][3];
			return *this; 
		}

		template<typename U>
		inline Matrix<4, 4, T>& operator*=(U scale)
		{
			const T s = static_cast<T>(scale);
			data[0][0] *= s; data[0][1] *= s; data[0][2] *= s; data[0][3] *= s;
			data[1][0] *= s; data[1][1] *= s; data[1][2] *= s; data[1][3] *= s;
			data[2][0] *= s; data[2][1] *= s; data[2][2] *= s; data[2][3] *= s;
			data[3][0] *= s; data[3][1] *= s; data[3][2] *= s; data[3][3] *= s;
			return *this;
		}

		template<typename U>
		inline Matrix<4, 4, T>& operator/=(U scale)
		{
			const T revS = static_cast<T>(1.0f / scale);
			data[0][0] *= revS; data[0][1] *= revS; data[0][2] *= revS;	data[0][3] *= revS;
			data[1][0] *= revS; data[1][1] *= revS; data[1][2] *= revS;	data[1][3] *= revS;
			data[2][0] *= revS; data[2][1] *= revS; data[2][2] *= revS;	data[2][3] *= revS;
			data[3][0] *= revS; data[3][1] *= revS; data[3][2] *= revS;	data[3][3] *= revS;
			return *this;
		}

		inline Matrix<4, 4, T>& operator*=(const Matrix<4, 4, T>& m)
		{
			//Copy is necessary! :( 
			*this = *this * m;
			return *this;
		}
#pragma endregion

		//=== Relational Operators ===
#pragma region RelationalOperators
		inline bool operator==(const Matrix<4, 4, T>& m) const
		{ return ((*this)[0] == m[0]) && ((*this)[1] == m[1]) && ((*this)[2] == m[2]) && ((*this)[3] == m[3]); }

		inline bool operator!=(const Matrix<4, 4, T>& m) const
		{ return !(*this == m); }
#pragma endregion 

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		//Access parameter order still happens as row,column indexing (standard in programming)
		inline T operator()(uint8_t r, uint8_t c) const
		{
			assert((r < 4 && c < 4) && "ERROR: indices of Matrix4x4 () const operator are out of bounds!");
			return (data[c][r]);
		}

		inline T& operator()(uint8_t r, uint8_t c)
		{
			assert((r < 4 && c < 4) && "ERROR: indices of Matrix4x4 () operator are out of bounds!");
			return (data[c][r]);
		}

		//Get a vector representation of a column (usage), but internally returns one of the rows
		inline const Vector<4, T>& operator[](uint8_t c) const
		{
			assert((c < 4) && "ERROR: index of Matrix4x4 [] operator is out of bounds!");
			return *((Vector<4, T>*)data[c]);
		}

		inline Vector<4, T>& operator[](uint8_t c)
		{
			assert((c < 4) && "ERROR: index of Matrix4x4 [] operator is out of bounds!");
			return *((Vector<4, T>*)data[c]);
		}
#pragma endregion

		//=== Static Functions ===
		static Matrix<4, 4, T> Identity();
	};

	//--- VECMATRIX3 FUNCTIONS ---
#pragma region GlobalOperators
#pragma endregion

#pragma region GlobalFunctions
	template<typename T>
	inline Matrix<4, 4, T> Matrix<4, 4, T>::Identity()
	{
		return Matrix<4, 4, T>(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	template<typename T>
	inline Matrix<4, 4, T> Transpose(const Matrix<4, 4, T>& m)
	{
		Matrix<4, 4, T> t = {};
		t(0, 0) = m(0, 0);
		t(0, 1) = m(1, 0);
		t(0, 2) = m(2, 0);
		t(0, 3) = m(3, 0);
		t(1, 0) = m(0, 1);
		t(1, 1) = m(1, 1);
		t(1, 2) = m(2, 1);
		t(1, 3) = m(3, 1);
		t(2, 0) = m(0, 2);
		t(2, 1) = m(1, 2);
		t(2, 2) = m(2, 2);
		t(2, 3) = m(3, 2);
		t(3, 0) = m(0, 3);
		t(3, 1) = m(1, 3);
		t(3, 2) = m(2, 3);
		t(3, 3) = m(3, 3);
		return t;
	}

	template<typename T>
	inline T Determinant(const Matrix<4, 4, T>& m)
	{
		return
			+ m(0, 0) * (
				+ (m(1, 1) * m(2, 2) * m(3, 3)) - (m(1, 1) * m(2, 3) *  m(3, 2))
				+ (m(1, 2) * m(2, 3) * m(3, 1)) - (m(1, 2) * m(2, 1) *  m(3, 3))
				+ (m(1, 3) * m(2, 1) * m(3, 2)) - (m(1, 3) * m(2, 2) *  m(3, 1)))
			+ m(0, 1) * (
				+ (m(1, 0) * m(2, 3) * m(3, 2)) - (m(1, 0) * m(2, 2) *  m(3, 3))
				+ (m(1, 2) * m(2, 0) * m(3, 3)) - (m(1, 2) * m(2, 3) *  m(3, 0))
				+ (m(1, 3) * m(2, 2) * m(3, 0)) - (m(1, 3) * m(2, 0) *  m(3, 2)))
			+ m(0, 2) * (
				+ (m(1, 1) * m(2, 3) * m(3, 0)) - (m(1, 1) * m(2, 0) *  m(3, 3))
				+ (m(1, 0) * m(2, 1) * m(3, 3)) - (m(1, 0) * m(2, 3) *  m(3, 1))
				+ (m(1, 3) * m(2, 0) * m(3, 1)) - (m(1, 3) * m(2, 1) *  m(3, 0)))
			+ m(0, 3) * (
				+ (m(1, 1) * m(2, 0) * m(3, 2)) - (m(1, 1) * m(2, 2) *  m(3, 0))
				+ (m(1, 2) * m(2, 1) * m(3, 0)) - (m(1, 2) * m(2, 0) *  m(3, 1))
				+ (m(1, 0) * m(2, 2) * m(3, 1)) - (m(1, 0) * m(2, 1) *  m(3, 2)));
	}

	template<typename T>
	inline Matrix<4, 4, T> Inverse(const Matrix<4, 4, T>& m)
	{
		//Optimized Inverse as explained in FGED1 - used widely in other libraries too.
		const Vector<3, T>& a = m[0].xyz;
		const Vector<3, T>& b = m[1].xyz;
		const Vector<3, T>& c = m[2].xyz;
		const Vector<3, T>& d = m[3].xyz;

		const float x = m(3, 0);
		const float y = m(3, 1);
		const float z = m(3, 2);
		const float w = m(3, 3);

		Vector<3, T> s = Cross(a, b);
		Vector<3, T> t = Cross(c, d);
		Vector<3, T> u = a * y - b * x;
		Vector<3, T> v = c * w - d * z;

		T det = Dot(s, v) + Dot(t, u);
		assert((!AreEqual(det, static_cast<T>(0))) && "ERROR: determinant is 0, there is no INVERSE!");
		T invDet = static_cast<T>(1.0f / det);

		s *= invDet; t *= invDet; u *= invDet; v *= invDet;

		Vector<3, T> r0 = Cross(b, v) + t * y;
		Vector<3, T> r1 = Cross(v, a) - t * x;
		Vector<3, T> r2 = Cross(d, u) + s * w;
		Vector<3, T> r3 = Cross(u, c) - s * z;

		return Matrix<4, 4, T>(
			r0.x, r0.y, r0.z, -Dot(b, t),
			r1.x, r1.y, r1.z,  Dot(a, t),
			r2.x, r2.y, r2.z, -Dot(d, s),
			r3.x, r3.y, r3.z,  Dot(c, s));
	}
	
	template<typename T>
	inline Matrix<4, 4, T> MakeTranslation(const Vector<3, T>& v)
	{
		return Matrix<4, 4, T>(
			1, 0, 0, v.x,
			0, 1, 0, v.y,
			0, 0, 1, v.z,
			0, 0, 0, 1);
	}
#pragma endregion
}
#endif