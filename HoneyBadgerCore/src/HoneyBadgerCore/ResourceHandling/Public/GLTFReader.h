#pragma once


#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

struct cgltf_data;
struct cgltf_accessor;
struct cgltf_attribute;
struct cgltf_skin;
struct cgltf_node;
struct MeshData;

namespace HoneyBadger
{
	namespace GLTFReader
	{
		// TODO: shared ptr, or free?
		cgltf_data* Read(const char* filePath);
		std::vector<MeshData> LoadMeshes(cgltf_data* data);
		void MeshFromAttribute(MeshData& md, cgltf_attribute& attribute, cgltf_skin* skin, cgltf_node* nodes, unsigned nodeCount);

		std::vector<float> GetFloats(unsigned inComponentCount, const cgltf_accessor& inAccessor);
	};
}