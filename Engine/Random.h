#pragma once

#include <cstdlib>

namespace nu
{

	inline int RandomInt()
	{
		return rand();
	}

	/// <summary>
	/// Get random integer value [0, max)
	/// </summary>
	/// <param name="max">exclusive max</param>
	/// <returns></returns>
	inline int RandomInt(int max)
	{
		return rand() % max;
	}
	
	/// <summary>
	/// Get random integer value [min, max)
	/// </summary>
	/// <param name="min">inclusive</param>
	/// <param name="max">inclusive</param>
	/// <returns></returns>
	inline int RandomInt(int min, int max)
	{
		return min + RandomInt((max - min) + 1);
	}

	inline float RandomFloat()
	{
		return rand() / (float)RAND_MAX;
	}

	inline float RandomFloat(float max)
	{
		return RandomFloat() * max;
	}

	inline float RandomFloat(float min, float max)
	{
		return min + RandomFloat() * (max - min);
	}

}
