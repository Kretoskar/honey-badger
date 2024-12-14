#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/GLTFReader.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/vendor/cgltf.h"
#include <HoneyBadgerCore/Math/Public/Mat4.h>
#include <HoneyBadgerCore/ECS/Public/Components/TransformComponent.h>

namespace HoneyBadger
{
	cgltf_data* GLTFReader::Read(const char* filePath)
	{
		MeshData md;

		cgltf_options options;
		memset(&options, 0, sizeof(cgltf_options));
		cgltf_data* data = nullptr;

		cgltf_result result = cgltf_parse_file(&options, filePath, &data);
		if (result != cgltf_result_success)
		{
			cgltf_free(data);
			HB_LOG_ERROR("Couldn't read gltf file from path %s", filePath)
			return nullptr;
		}

		result = cgltf_load_buffers(&options, data, filePath);
		if (result != cgltf_result_success)
		{
			cgltf_free(data);
			HB_LOG_ERROR("Couldn't read gltf buffers from path %s", filePath)
			return nullptr;
		}
		
		result = cgltf_validate(data);
		if (result != cgltf_result_success)
		{
			cgltf_free(data);
			HB_LOG_ERROR("Invalid GLTF file from path %s", filePath)
			return nullptr;
		}
		
		return data;
	}

	std::vector<MeshData> GLTFReader::LoadMeshes(cgltf_data* data)
	{
		std::vector<MeshData> result;
		cgltf_node* nodes = data->nodes;
		const unsigned nodeCount = static_cast<unsigned>(data->nodes_count);

		for (unsigned n = 0; n < nodeCount; ++n)
		{
			const cgltf_node* node = &nodes[n];
			if (node->mesh == nullptr)// || node->skin == nullptr)
			{
				continue;
			}

			const unsigned numPrimitives = static_cast<unsigned>(node->mesh->primitives_count);
			for (unsigned p = 0; p < numPrimitives; ++p)
			{
				MeshData md;
				
				const cgltf_primitive* primitive = &node->mesh->primitives[p];

				const unsigned numAttributes = static_cast<unsigned>(primitive->attributes_count);
				for (unsigned a = 0; a < numAttributes; ++a)
				{
					cgltf_attribute* attribute = &primitive->attributes[a];
					MeshFromAttribute(md, *attribute, node->skin, nodes, nodeCount);
				}
				if (primitive->indices != nullptr)
				{
					const unsigned int indexCount = static_cast<unsigned>(primitive->indices->count);
					md._indices.resize(indexCount);

					for (unsigned int k = 0; k < indexCount; ++k)
					{
						md._indices[k] = static_cast<unsigned>(cgltf_accessor_read_index(primitive->indices, k));
					}
				}

				result.push_back(md);
			}
		}

		return result;
	}

	std::vector<TransformComponent> GLTFReader::LoadLocalTransforms(cgltf_data* data)
	{
		std::vector<TransformComponent> result;
		cgltf_node* nodes = data->nodes;
		const unsigned nodeCount = static_cast<unsigned>(data->nodes_count);

		for (unsigned n = 0; n < nodeCount; ++n)
		{
			TransformComponent transform;

			const cgltf_node* node = &nodes[n];

			// TODO: node->has_matrix?

			if (node->has_translation)
			{
				transform.Position = { node->translation[0], node->translation[1], node->translation[2] };
			}

			if (node->has_rotation)
			{
				transform.Rotation = {node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3] };
			}

			if (node->has_scale)
			{
				transform.Scale = { node->scale[0], node->scale[1], node->scale[2] };
			}

			result.push_back(std::move(transform));
		}

		return result;
	}

	void GLTFReader::MeshFromAttribute(MeshData& md, cgltf_attribute& attribute, cgltf_skin* skin, cgltf_node* nodes, unsigned nodeCount)
	{
		cgltf_attribute_type attribType = attribute.type;
		cgltf_accessor& accessor = *attribute.data;

		unsigned componentCount = 0;
		if (accessor.type == cgltf_type_vec2)
		{
			componentCount = 2;
		}
		else if (accessor.type == cgltf_type_vec3)
		{
			componentCount = 3;
		}
		else if (accessor.type == cgltf_type_vec4)
		{
			componentCount = 4;
		}

		std::vector<float> values = std::move(GetFloats(componentCount, accessor));
		
		unsigned int acessorCount = static_cast<unsigned>(accessor.count);

		std::vector<Vec3> positions;
		std::vector<Vec3> normals;
		std::vector<Vec2> texUvs;

		for (unsigned i = 0; i < acessorCount; ++i)
		{
			int index = i * componentCount;
			switch (attribType)
			{
			case cgltf_attribute_type_position:
				positions.push_back(Vec3(values[index + 0], values[index + 1], values[index + 2]));
				break;
			case cgltf_attribute_type_texcoord:
				texUvs.push_back(Vec2(values[index + 0], values[index + 1]));
				break;
			case cgltf_attribute_type_normal:
				normals.push_back(Vec3(values[index + 0], values[index + 1], values[index + 2]));
				break;
			}
		}

		if (positions.size() > 0)
		{
			for (int32_t i = 0; i < positions.size(); i++)
			{
				int32_t verts = md._vertices.size() - 1;
				if (i >= verts)
				{
					md._vertices.push_back({
						positions[i], 
						{0.0f, 0.0f, 0.0f},
						{0.0f,0.0f,0.0f},
						{0.0f,0.0f}});
				}
				else
				{
					md._vertices[i].Position = positions[i];
				}
			}
		}

		if (normals.size() > 0)
		{
			for (int32_t i = 0; i < normals.size(); i++)
			{
				int32_t verts = md._vertices.size() - 1;
				if (i >= verts)
				{
					md._vertices.push_back({
						{0.0f, 0.0f, 0.0f},
						normals[i],
						{0.0f,0.0f,0.0f},
						{0.0f,0.0f} });
				}
				else
				{
					md._vertices[i].Normal = normals[i];
				}
			}
		}

		if (texUvs.size() > 0)
		{
			for (int32_t i = 0; i < texUvs.size(); i++)
			{
				int32_t verts = md._vertices.size() - 1;
				if (i >= verts)
				{
					md._vertices.push_back({
						{0.0f, 0.0f, 0.0f},
						{0.0f, 0.0f, 0.0f},
						{0.0f,0.0f,0.0f},
						texUvs[i]});
				}
				else
				{
					md._vertices[i].TexUV = texUvs[i];
				}
			}
		}
	}

	std::vector<float> GLTFReader::GetFloats(unsigned inComponentCount, const cgltf_accessor& inAccessor)
	{
		std::vector<float> floats;
		floats.resize(inAccessor.count * inComponentCount);
		for (cgltf_size i = 0; i < inAccessor.count; ++i)
		{
			cgltf_accessor_read_float(&inAccessor, i, &floats[i * inComponentCount], inComponentCount);
		}

		return floats;
	}
}