#pragma once

#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/Quat.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"

#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	struct TransformComponent
	{
		Vec3 Position;
		Quat Rotation;
		Vec3 Scale = {1,1,1};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformComponent, Position, Rotation, Scale)

		Mat4 ToMat4()
		{
			// First, extract the rotation basis of the transform
			Vec3 x = Rotation * Vec3(1, 0, 0);
			Vec3 y = Rotation * Vec3(0, 1, 0);
			Vec3 z = Rotation * Vec3(0, 0, 1);

			// Next, scale the basis vectors
			x = x * Scale.x;
			y = y * Scale.y;
			z = z * Scale.z;

			// Extract the position of the transform
			Vec3 p = Position;

			// Create matrix
			return Mat4(
				x.x, x.y, x.z, 0, // X basis (& Scale)
				y.x, y.y, y.z, 0, // Y basis (& scale)
				z.x, z.y, z.z, 0, // Z basis (& scale)
				p.x, p.y, p.z, 1 // Position
			);
		}
	};
}