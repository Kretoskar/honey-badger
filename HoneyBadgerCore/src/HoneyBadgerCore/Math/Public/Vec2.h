#pragma once

namespace HoneyBadger
{
	struct Vec2
	{
		union
		{
			struct
			{
				float x;
				float y;
			};

			float v[2];
		};

		Vec2() : x(0), y(0) {}
		Vec2(float x, float y) : x(x), y(y) {}
	};
}