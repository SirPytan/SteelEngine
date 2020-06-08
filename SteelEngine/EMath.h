/*=============================================================================*/
// Copyright 2019 Elite Engine 2.0
// Authors: Matthieu Delaere
/*=============================================================================*/
// EMath.h: General Math header that includes all math types and utilities
/*=============================================================================*/
#ifndef ELITE_MATH
#define ELITE_MATH

/* --- STANDARD --- */
#include <math.h>
#include <cassert>
/* --- UTILITIES --- */
#include "EMathUtilities.h"
/* --- TYPES --- */
#include "EVector.h"
#include "EVector2.h"
#include "EVector3.h"
#include "EVector4.h"
#include "EPoint.h"
#include "EPoint2.h"
#include "EPoint3.h"
#include "EPoint4.h"
#include "EMatrix.h"
#include "EMatrix2.h"
#include "EMatrix3.h"
#include "EMatrix4.h"

namespace Elite
{
	/* --- TYPE DEFINES --- */
	using FVector2 = Vector<2, float>;
	using DVector2 = Vector<2, double>;
	using IVector2 = Vector<2, int>;
	using FVector3 = Vector<3, float>;
	using DVector3 = Vector<3, double>;
	using IVector3 = Vector<3, int>;
	using FVector4 = Vector<4, float>;
	using DVector4 = Vector<4, double>;
	using IVector4 = Vector<4, int>;

	using FPoint2 = Point<2, float>;
	using DPoint2 = Point<2, double>;
	using IPoint2 = Point<2, int>;
	using FPoint3 = Point<3, float>;
	using DPoint3 = Point<3, double>;
	using IPoint3 = Point<3, int>;
	using FPoint4 = Point<4, float>;
	using DPoint4 = Point<4, double>;
	using IPoint4 = Point<4, int>;

	using FMatrix2 = Matrix<2, 2, float>;
	using DMatrix2 = Matrix<2, 2, double>;
	using FMatrix3 = Matrix<3, 3, float>;
	using DMatrix3 = Matrix<3, 3, double>;
	using FMatrix4 = Matrix<4, 4, float>;
	using DMatrix4 = Matrix<4, 4, double>;
}
#endif
