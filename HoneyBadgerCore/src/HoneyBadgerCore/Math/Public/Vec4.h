#pragma once

#include "HoneyBadgerCore/Math/Public/Vec3.h"

namespace HoneyBadger
{
	struct Vec4
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};

			struct
			{
				float r;
				float g;
				float b;
				float a;
			};

			float v[4];
		};

		Vec4() : x(0), y(0), z(0), w(0) {}
		Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		Vec3 ToVec3() 
		{
			return Vec3(x,y,z);
		}
	};
}