#pragma once

#pragma region
//*****************************************************************************
//Declare templates for deleting objects and useful macros
//Author: Matthieu Delaere
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
inline void Clamp(T& value, T high, T low)
{
	if (value > high)
		value = high;

	if (value < low)
		value = low;
}
#pragma endregion Templates & Macros