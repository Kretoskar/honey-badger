#pragma once

#include "HoneyBadgerCore/Math/Public/Vec4.h"

namespace HoneyBadger
{
	/* 
	 * Column major matrix
	 * |0-4--8-12|
	 * |1-5--9-13|
	 * |2-6-10-14|
	 * |3-7-11-15|
	 * right to left multiplication
	 * 
	 * position is stored in column
	 * |r.x-u.x-f.x-p.x|
	 * |r.y-u.y-f.y-p.y|
	 * |r.z-u.z-f.z-p.z|
	 * |--0---0---0---1|
	 */
	struct Mat4
	{
		union
		{
			float v[16];

			struct
			{
				Vec4 right;
				Vec4 up;
				Vec4 forward;
				Vec4 position;
			};

			struct  
			{
				/*
				* |0-4--8-12|
				* |1-5--9-13|
				* |2-6-10-14|
				* |3-7-11-15|
				*/
				float c0r0; // 0
				float c0r1; // 1
				float c0r2; // 2
				float c0r3; // 3
				float c1r0; // 4
				float c1r1; // 5
				float c1r2; // 6
				float c1r3; // 7
				float c2r0; // 8
				float c2r1; // 9
				float c2r2; // 10
				float c2r3; // 11
				float c3r0; // 12
				float c3r1; // 13
				float c3r2; // 14
				float c3r3; // 15
			};
		};
	};
}