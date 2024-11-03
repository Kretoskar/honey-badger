#pragma once

#include <memory>

#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/Rendering/Public/ElementBufferObject.h"
#include "HoneyBadgerCore/Rendering/Public/VertexArrayObject.h"
#include "HoneyBadgerCore/Rendering/Public/VertexBufferObject.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"

namespace HoneyBadger
{
	struct LineVertex
	{
		LineVertex() = default;

		LineVertex(Vec3 pos, Vec3 color)
			: X(pos.x), Y(pos.y), Z(pos.z), R(color.r), G(color.g), B(color.b) {}
		LineVertex(float x, float y, float z, float r, float g, float b)
			: X(x), Y(y), Z(z), R(r), G(g), B(b) {}

		float X{}, Y{}, Z{};
		float R{}, G{}, B{};
	};

	class DebugRenderer
	{
	public:
		DebugRenderer(std::shared_ptr<Camera> camera) 
			: _camera(camera) {}

		bool Init();
		void Render();
		void AddLine(Vec3 start, Vec3 end, Vec3 color);
		void DrawNet(unsigned count, float stride, float size, Vec3 color);

	private:
		std::unique_ptr<Shader> _shader;
		std::unique_ptr<VertexBufferObject> _lineVbo;
		std::unique_ptr<ElementBufferObject> _lineEbo;
		std::unique_ptr<VertexArrayObject> _lineVao;

		static constexpr unsigned MAX_LINE_COUNT = 4096;
		uint32_t _lineCount = 0;
		LineVertex _lineVertices[MAX_LINE_COUNT * 2];

		unsigned _lineIndices[MAX_LINE_COUNT * 2];

		std::shared_ptr<Camera> _camera;
	};

}