#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"

#include <glad/glad.h>

#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Rendering/Public/Texture.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

namespace HoneyBadger
{
	Shader::Shader(HBString fragmentFilePath, HBString vertexFilePath)
		: _fragmentFilePath(fragmentFilePath), _vertexFilePath(vertexFilePath)
	{
		_id = CreateShader();
	}

	Shader::~Shader()
	{
		glDeleteProgram(_id);
	}

	void Shader::Bind() const
	{
		glUseProgram(_id);
	}

	void Shader::Delete()
	{
		glDeleteProgram(_id);
	}

	void Shader::SetUniform4f(HBString name, float v0, float v1, float v2, float v3)
	{
		Bind();
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniform1f(HBString name, float v0)
	{
		Bind();
		glUniform1f(GetUniformLocation(name), v0);
	}

	void Shader::SetUniform2f(HBString name, float v0, float v1)
	{
		Bind();
		glUniform2f(GetUniformLocation(name), v0, v1);
	}

	void Shader::SetUniform3f(HBString name, float v0, float v1, float v2)
	{
		Bind();
		glUniform3f(GetUniformLocation(name), v0, v1, v2);
	}

	void Shader::SetUniform1i(HBString name, int v0)
	{
		Bind();
		glUniform1i(GetUniformLocation(name), v0);
	}

	void Shader::SetUniformMat4f(HBString name, const Mat4& mat)
	{
		Bind();
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat.v[0]);
	}

	void Shader::AssignDiffuseMap(Texture& texture)
	{
		Bind();
		texture.Bind();
		SetUniform1i("diffuseMap", 0);
	}

	void Shader::AssignSpecularMap(Texture& texture)
	{
		Bind();
		texture.Bind();
		SetUniform1i("specularMap", 1);
	}

	void Shader::SetModelMatrix(Mat4 m)
	{
		Bind();
		SetUniformMat4f("model", m);
	}

	void Shader::SetVPMatrix(Mat4 m)
	{
		Bind();
		SetUniformMat4f("viewProj", m);
	}

	void Shader::SetCameraPosition(Vec3 pos)
	{
		Bind();
		SetUniform3f("cameraPos", pos.x, pos.y, pos.z);
	}

	void Shader::SetLightPosition(Vec3 pos)
	{
		Bind();
		SetUniform3f("lightPos", pos.x, pos.y, pos.z);
	}

	void Shader::SetLightColor(Vec4 color)
	{
		Bind();
		SetUniform4f("lightColor", color.x, color.y, color.z, color.w);
	}

	int Shader::GetUniformLocation(HBString name)
	{
		Bind();

		const char* nameChar = name.Get();

		if (_uniformLocationCache.find(nameChar) != _uniformLocationCache.end())
		{
			return _uniformLocationCache[nameChar];
		}

		const int location = glGetUniformLocation(_id, nameChar);
		_uniformLocationCache[nameChar] = location;

		if (location < 0)
		{
			HB_LOG_WARNING("Trying to retrieve invalid uniform location of name %s", nameChar)
		}

		return 1;
	}

	unsigned int Shader::CreateShader()
	{
		File vertexShaderFile(_vertexFilePath.Get());

		if (!vertexShaderFile.IsValid())
		{
			HB_LOG_ERROR("Failed to create vertex shader")
			return 0;
		}

		File fragmentShaderFile(_fragmentFilePath.Get());

		if (!fragmentShaderFile.IsValid())
		{
			HB_LOG_ERROR("Failed to create fragment shader")
			return 0;
		}

		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, *vertexShaderFile.GetFileContents());
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, *fragmentShaderFile.GetFileContents());

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* scr = source.c_str();
		glShaderSource(id, 1, &scr, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = static_cast<char*>(alloca(length * sizeof(char)));
			glGetShaderInfoLog(id, length, &length, message);

			HB_LOG_ERROR(message)
			glDeleteShader(id);

			return 0;
		}

		return id;
	}
}