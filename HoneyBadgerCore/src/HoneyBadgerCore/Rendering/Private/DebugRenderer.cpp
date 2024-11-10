#include "hbpch.h"
#include <glad/glad.h>

#include "HoneyBadgerCore/Rendering/Public/DebugRenderer.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

namespace HoneyBadger
{
	bool DebugRenderer::Init()
	{
		// TODO: Assets registry
		_shader = std::make_unique<Shader>("shaders/debug.frag", "shaders/debug.vert");
		_shader->Bind();

		_lineVao = std::make_unique<VertexArrayObject>();
		_lineVao->Bind();
		_lineVbo = std::make_unique<VertexBufferObject>((float*)_lineVertices, MAX_LINE_COUNT * 6 * 4);
		_lineEbo = std::make_unique<ElementBufferObject>(_lineIndices, MAX_LINE_COUNT * 2 * 4);
		// position
		_lineVao->LinkAttrib(*_lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		// color
		_lineVao->LinkAttrib(*_lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		DrawNet(1000, 0.1f, 100.0f, Vec3(0.3f, 0.3f, 0.3f));
		DrawNet(100, 1.0f, 100.0f, Vec3(0.6f, 0.6f, 0.6f));
	

		return true;
	}

	void DebugRenderer::Render()
	{
		_shader->Bind();
		_shader->SetModelMatrix(Mat4());
		_shader->SetVPMatrix(_camera->GetVPMatrix());
		_lineVao->Bind();
		glDrawElements(GL_LINES, sizeof(_lineIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}

	void DebugRenderer::AddLine(Vec3 start, Vec3 end, Vec3 color)
	{
		if (_lineCount == MAX_LINE_COUNT)
		{
			HB_LOG_ERROR("Exceeded maximum debug line count of %d Can't draw any more lines", MAX_LINE_COUNT)
			return;
		}

		_lineVertices[_lineCount * 2] = { start, color };
		_lineVertices[_lineCount * 2 + 1] = { end, color };

		_lineIndices[_lineCount * 2] = _lineCount * 2;
		_lineIndices[_lineCount * 2 + 1] = _lineCount * 2 + 1;

		_lineCount++;
	}

	void DebugRenderer::DrawNet(unsigned count, float stride, float size, Vec3 color)
	{
		//TODO: Allow adding lines in batch
		for (int i = 0; i <= count; i++)
		{
			AddLine(Vec3(size / 2, 0.0f, i * stride - count * stride / 2), Vec3(-size / 2, 0.0f, i * stride - count * stride / 2), color);
			AddLine(Vec3(i * stride - count * stride / 2, 0.0f, size / 2), Vec3(i * stride - count * stride / 2, 0.0f, -size / 2), color);
		}

		_lineVao->Bind();
		_lineVbo->Init((float*)_lineVertices, _lineCount * 2 * 6 * 4);
		_lineEbo->Init(_lineIndices, MAX_LINE_COUNT * 2 * 4);
		// position
		_lineVao->LinkAttrib(*_lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		// color
		_lineVao->LinkAttrib(*_lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	}
}