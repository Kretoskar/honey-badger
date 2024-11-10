#pragma once

namespace HoneyBadger
{
	class MathCore
	{
	public:
		static inline float DegToRad(float Deg) { return Deg * 0.0174532925f; }
		static inline float RadToDeg(float Rad) { return Rad * 57.2957795f; }
		static inline float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
		static inline float Min(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
		static inline float NearlyEqual(float lhs, float rhs) { return std::abs(lhs - rhs) <= FloatEpsilon; }

		 static float PI;
		 static float FloatEpsilon;
	};
}