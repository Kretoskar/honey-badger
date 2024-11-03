#pragma once

namespace HoneyBadger
{
	class MathCore
	{
	public:
		static inline float DegToRad(float Deg) { return Deg * 0.0174532925f; }
		static inline float RadToDeg(float Rad) { return Rad * 57.2957795f; }

		static inline float PI() { return 3.1415926535f; }
	};
}