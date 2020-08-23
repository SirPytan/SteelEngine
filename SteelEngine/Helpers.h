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

//Not from Matthieu Delaere
//https://stackoverflow.com/questions/45507041/how-to-check-if-weak-ptr-is-empty-non-assigned
template <typename T>
inline bool IsUninitialized(std::weak_ptr<T> const& weak)
{
	using wt = std::weak_ptr<T>;
	return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}

#pragma endregion Templates & Macros