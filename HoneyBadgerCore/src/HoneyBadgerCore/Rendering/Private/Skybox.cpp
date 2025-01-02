#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Skybox.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include <glad/glad.h>
#include <stb_image.h>

using namespace HoneyBadger;

float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};


void Skybox::Init(Camera* cam)
{
	camera = cam;
	if (!camera)
	{
		HB_LOG_ERROR("Invalid camera passed to skybox")
		return;
	}

	int32_t width, height, nChannels;

	std::vector<std::string> faces = 
	{
		File::GetPathInRes("skybox/right.jpg"),
		File::GetPathInRes("skybox/left.jpg"),
		File::GetPathInRes("skybox/top.jpg"),
		File::GetPathInRes("skybox/bottom.jpg"),
		File::GetPathInRes("skybox/front.jpg"),
		File::GetPathInRes("skybox/back.jpg")
	};


	glGenTextures(1, &_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _tex);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	unsigned char* data;
	for (uint32_t i = 0; i < faces.size(); ++i)
	{
		data = stbi_load(faces[i].c_str(), &width, &height, &nChannels, 0);
		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}
		else
		{
			HB_LOG_ERROR("Failed to load cubemap face at path %s", faces[i])
			return;
		}
	}

	shader = AssetsRegistry::Instance->GetShaderByName("skybox");
	if (shader)
	{
		shader->SetUniform1f("skybox", 0);
	}
	else
	{
		HB_LOG_ERROR("Failed to find skybox shader")
		return;
	}

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::Render()
{
	glDepthFunc(GL_LEQUAL);

	Mat4 view = camera->GetViewMatrix();
	Mat4 viewNoTranslation = 
	{
		view.v[0], view.v[1], view.v[2],  0.0f,
		view.v[4], view.v[5], view.v[6],  0.0f,
		view.v[8], view.v[9], view.v[10], 0.0f,
		0.0f,      0.0f,      0.0f,       1.0f
	};

	// TODO: No translation here
	shader->SetUniformMat4f("projection", camera->GetProjectionMatrix());
	shader->SetUniformMat4f("view", viewNoTranslation);

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _tex);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}
