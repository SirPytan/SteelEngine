/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EMatrix.h: base Column-Major Matrix struct stored in Row-Major Order for locality + general matrix template functions
/*=============================================================================*/
#ifndef ELITE_MATH_MATRIX
#define	ELITE_MATH_MATRIX

namespace Elite
{
	//========================= LAYOUT ==========================
	//------ LAYOUT IN MEMORY ---------- "LAYOUT" FOR USAGE -----
	// |xx|	 c0	 |	 c1	 |	c2	|	c3	|    |xx|	 c0	 |	 c1	 |	c2	|	c3	|
	// ---------------------------------------------------------------------------
	// |r0|  a.x |  a.y	 |  a.z	|  a.w  |	 |r0|   a.x	 |  b.x	 |  c.x	|  d.x	|
	// |r1|	 b.x |  b.y	 |  b.z	|  b.w  |	 |r1|	a.y	 |  b.y	 |  c.y	|  d.y	|
	// |r2|	 c.x |  c.y	 |  c.z	|  c.w  |	 |r2|	a.z	 |  b.z	 |  c.z	|  d.z	|
	// |r3|	 d.x |  d.y	 |  d.z	|  d.w	|	 |r3|	a.w	 |  b.w	 |  c.w	|  d.w	|
	// ----------------------------------------------------------
	// So access indices are reversed --> operator(r,c), example usage:
	// (row 1, column 2) we expect value c.y, this is referenced in memory as [2][1] == row 2, column 1,
	// which is also c.y!

	//=== CORE VECTOR TYPE ===
	template<int N, int M, typename T>
	struct Matrix
	{
		//=== Data ===
		//Double array in C++ has row based layout ([row][column])!
		//we use store vectors in row based layout for good locality BUT we index them as column major matrices!
		T data[N][M];

		//=== Member Access Operators ===
#pragma region MemberAccessOperators
		//Access parameter order still happens as row,column indexing (standard in programming)
		inline T operator()(uint8_t r, uint8_t c) const
		{
			assert((r < M && c < N) && "ERROR: indices of Matrix () const operator are out of bounds!");
			return (data[c][r]);
		}

		inline T& operator()(uint8_t r, uint8_t c)
		{
			assert((r < M && c < N) && "ERROR: indices of Matrix () operator are out of bounds!");
			return (data[c][r]);
		}

		//Get a vector representation of a column (usage), but internally returns one of the rows
		inline const Vector<N, T>& operator[](uint8_t c) const
		{
			assert((c < N) && "ERROR: index of Matrix [] operator is out of bounds!");
			return (*reinterpret_cast<Vector<N, T>*>(data[c]));
		}

		inline Vector<N, T>& operator[](uint8_t c)
		{
			assert((c < N) && "ERROR: index of Matrix [] operator is out of bounds!");
			return (*reinterpret_cast<Vector<N, T>*>(data[c]));
		}
#pragma endregion
	};
}
#endif