#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

	static const char* selectedMesh = nullptr;
	std::vector<const char*> meshNames; 
	for (const std::string& s : HoneyBadger::AssetsRegistry::Instance->MeshNames)
	{
		meshNames.emplace_back(s.c_str());
	}

	if (ImGui::BeginCombo("##meshCombo", selectedMesh))
	{
		for (int n = 0; n < meshNames.size(); n++)
		{
			bool isSelected = (selectedMesh == meshNames[n]);
			if (ImGui::Selectable(meshNames[n], isSelected))
			{
				selectedMesh = meshNames[n];
				MeshGuid = HoneyBadger::AssetsRegistry::Instance->GetMeshByName(selectedMesh)->GetGuid();
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	static const char* selectedMaterial = nullptr;
	std::vector<const char*> materialNames;
	for (const std::string& s : HoneyBadger::AssetsRegistry::Instance->MaterialNames)
	{
		materialNames.emplace_back(s.c_str());
	}

	if (ImGui::BeginCombo("##meshMaterialCombo", selectedMaterial))
	{
		for (int n = 0; n < materialNames.size(); n++)
		{
			bool isSelected = (selectedMaterial == materialNames[n]);
			if (ImGui::Selectable(materialNames[n], isSelected))
			{
				selectedMaterial = materialNames[n];
				MaterialGuid = HoneyBadger::AssetsRegistry::Instance->GetMaterialGuid(selectedMaterial).Get();
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	RTTI_PROPERTY(Guid, MeshGuid)
	RTTI_PROPERTY(Verts, GetVerts())
	RTTI_END()
}