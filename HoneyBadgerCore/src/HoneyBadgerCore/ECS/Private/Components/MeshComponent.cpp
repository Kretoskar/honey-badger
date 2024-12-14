#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
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
	std::vector<const char*> names; 
	for (const std::string& s : HoneyBadger::AssetsRegistry::Instance->MeshNames)
	{
		names.emplace_back(s.c_str());
	}

	if (ImGui::BeginCombo("##meshCombo", selectedMesh))
	{
		for (int n = 0; n < names.size(); n++)
		{
			bool isSelected = (selectedMesh == names[n]);
			if (ImGui::Selectable(names[n], isSelected))
			{
				selectedMesh = names[n];
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	ImGui::SameLine();
	if (ImGui::Button("Set", ImVec2(100.0f, 20.0f)))
	{
		if (selectedMesh)
		{
			MeshGuid = HoneyBadger::AssetsRegistry::Instance->GetMeshByName(selectedMesh)->GetGuid();
		}
	}

	RTTI_PROPERTY(Guid, MeshGuid)
	RTTI_PROPERTY(Verts, GetVerts())
	RTTI_END()
}