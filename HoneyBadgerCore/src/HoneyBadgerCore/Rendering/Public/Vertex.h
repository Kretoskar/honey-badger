#pragma once

#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/Vec2.h"

namespace HoneyBadger
{
	struct Vertex
	{
		Vec3 Position;
		Vec3 Normal;
		Vec3 Color;
		Vec2 TexUV;
	};
}