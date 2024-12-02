#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"

namespace HoneyBadger
{
	int32_t MeshComponent::GetVerts()
	{
		if (AssetsRegistry* assetsRegistry = AssetsRegistry::Instance)
		{
			if (std::shared_ptr<Mesh> mesh = assetsRegistry->GetMeshByGuid(MeshGuid))
			{
				return mesh->GetData()._vertices.size();
			}
		}
		
		return -1;
	}

	RTTI_BEGIN(MeshComponent)
	RTTI_PROPERTY(Guid, MeshGuid)
	RTTI_PROPERTY(Verts, GetVerts())
	RTTI_END()
}