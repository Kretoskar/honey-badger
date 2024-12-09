#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/GLTFReader.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/vendor/cgltf.h"

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

		// std;: move?
		std::vector<float> values = GetFloats(componentCount, accessor);
		
		unsigned int acessorCount = static_cast<unsigned>(accessor.count);

		std::vector<Vec3> positions;

		for (unsigned i = 0; i < acessorCount; ++i)
		{
			int index = i * componentCount;
			switch (attribType)
			{
			case cgltf_attribute_type_position:
				positions.push_back(Vec3(values[index + 0], values[index + 1], values[index + 2]));
				break;
			}
		}

		for (auto& pos : positions)
		{
			md._vertices.push_back({ pos, {}, {1.0f, 0.0f, 0.0f}, {} });
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