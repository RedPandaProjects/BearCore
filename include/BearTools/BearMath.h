#pragma once
class BearMath
{
	BEAR_CLASS_STATIC(BearMath);
public:
	constexpr static float PI = 3.141592653589793238463f;
	inline static float cos(float a)
	{
		return cosf(a);
	}

	inline static float sin(float a)
	{
		return sinf(a);
	}

	inline static float sqrt(float a)
	{
		return sqrtf(a);
	}
	inline static float qrt(float a)
	{
		return a * a;
	}
	inline static float round(float a)
	{
		return roundf(a);
	}

	inline static float floor(float a)
	{
		return floorf(a);
	}

	template<typename T>
	inline static T abs(T a)
	{
		return a<0>-a:a;
	}
	template<>
	inline static float abs<float>(float a)
	{
		return floorf(a);
	}
};