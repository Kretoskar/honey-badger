#pragma once

#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMesh.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/Vec2.h"

namespace HoneyBadger
{
	class PlaneMesh : public SimpleMesh
	{
	public:
		PlaneMesh(Vec3 color) :
			SimpleMesh(
				{
					// position normal color texuv
					Vertex{Vec3(-1.0f, 0.0f,  1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.0f, 0.0f)},
					Vertex{Vec3(-1.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(0.0f, 1.0f)},
					Vertex{Vec3(1.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(1.0f, 1.0f)},
					Vertex{Vec3(1.0f, 0.0f,  1.0f), Vec3(0.0f, 1.0f, 0.0f), color, Vec2(1.0f, 0.0f)}

				},
				{
					 0, 1, 2,
					 0, 2, 3
				}) {}
	};
}