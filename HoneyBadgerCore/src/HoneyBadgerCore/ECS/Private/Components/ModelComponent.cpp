#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/ModelComponent.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Model.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace HoneyBadger
{
	RTTI_BEGIN(ModelComponent)

	static const char* selectedModel = nullptr;
	std::vector<const char*> names;
	for (const std::string& s : HoneyBadger::AssetsRegistry::Instance->ModelNames)
	{
		names.emplace_back(s.c_str());
	}

	if (ImGui::BeginCombo("##modelCombo", selectedModel))
	{
		for (int n = 0; n < names.size(); n++)
		{
			bool isSelected = (selectedModel == names[n]);
			if (ImGui::Selectable(names[n], isSelected))
			{
				selectedModel = names[n];
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
		if (selectedModel)
		{
			Guid = HoneyBadger::AssetsRegistry::Instance->GetModelByName(selectedModel)->_guid;
		}
	}

	RTTI_PROPERTY(Guid, Guid)
	RTTI_END()
}