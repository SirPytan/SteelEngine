#pragma once

#pragma region
//*****************************************************************************
//Declare templates for deleting objects and useful macros 
//*****************************************************************************
template<class T>
inline void SafeDelete(T& pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

template<typename T>
inline void Clamp(T& value, T hi, T lo)
{
	if (value > hi)
		value = hi;

	if (value < lo)
		value = lo;
}
#pragma endregion Templates & Macros