#pragma once

#include <string>
#include <unordered_map>

#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/Vec4.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"

namespace HoneyBadger
{
	class Texture;

	class Shader
	{
		HBString _fragmentFilePath;
		HBString _vertexFilePath;
		std::unordered_map<HBString, int, HBString::HBStringHasher> _uniformLocationCache;

		unsigned int _id;

	public:
		Shader(HBString fragmentFilePath, HBString vertexFilePath);
		~Shader();

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
		void SetVPMatrix(Mat4 m);
		void SetCameraPosition(Vec3 pos);
		void SetLightPosition(Vec3 pos);
		void SetLightColor(Vec4 color);

	private:
		int GetUniformLocation(HBString name);
		unsigned int CreateShader();
		unsigned int CompileShader(unsigned int type, const std::string& source);
	};
}