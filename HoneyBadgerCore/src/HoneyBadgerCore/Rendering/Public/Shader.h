#pragma once

#include <string>
#include <unordered_map>

#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/Vec4.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"

#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"

namespace HoneyBadger
{
	struct ShaderData
	{
		ShaderData() = default;

		ShaderData(std::string f, std::string v)
		{
			FragmentShaderPath = f;
			VertexShaderPath = v;
			Guid = GenerateGUID();
		}

		std::string Guid;
		std::string FragmentShaderPath;
		std::string VertexShaderPath;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ShaderData, Guid, FragmentShaderPath, VertexShaderPath)
	};

	class Texture;

	class Shader
	{
		HBString _fragmentFilePath;
		HBString _vertexFilePath;
		HBString _guid;
		std::unordered_map<HBString, int, HBString::HBStringHasher> _uniformLocationCache;

		unsigned int _id;

	public:
		Shader(HBString fragmentFilePath, HBString vertexFilePath);
		Shader(const ShaderData& shaderData);
		~Shader();

		HBString GetGuid() const { return _guid; }

		static std::shared_ptr<Shader> LoadShader(HBString path);

		void Bind() const;

		void Delete();

		void SetUniform4f(HBString name, float v0, float v1, float v2, float v3);
		void SetUniform1f(HBString name, float v0);
		void SetUniform2f(HBString name, float v0, float v1);
		void SetUniform3f(HBString name, float v0, float v1, float v2);
		void SetUniform1i(HBString name, int v0);

		void SetUniformMat4f(HBString name, const Mat4& mat);

		void AssignDiffuseMap(Texture& texture);
		void AssignSpecularMap(Texture& texture);

		void SetModelMatrix(Mat4 m);
		void SetRotModelMatrix(Mat4 m);
		void SetVPMatrix(Mat4 m);
		void SetCameraPosition(Vec3 pos);
		void SetLightPosition(Vec3 pos);
		void SetLightColor(Vec4 color);
		void SetLightDirection(const Vec3& dir);

	private:
		int GetUniformLocation(HBString name);
		unsigned int CreateShader();
		unsigned int CompileShader(unsigned int type, const std::string& source);
	};
}