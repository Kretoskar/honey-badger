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

	{
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
				std::shared_ptr<ModelData> Model = HoneyBadger::AssetsRegistry::Instance->GetModelByName(selectedModel);
				Guid = Model->_guid;
				MaterialsGuids.clear();
				for (int32_t i = 0; i < Model->_meshesGuids.size(); ++i)
				{
					// resize?
					MaterialsGuids.push_back("");
				}
			}
		}
	}

	RTTI_PROPERTY(Guid, Guid)
	ImGui::Text("---Meshes---");

	std::shared_ptr<ModelData> Model = HoneyBadger::AssetsRegistry::Instance->GetModelByGuid(Guid);
	if (Model)
	{
		for (const std::string& meshGuid : Model->_meshesGuids)
		{
			
			ImGui::Text(HoneyBadger::AssetsRegistry::Instance->GetMeshName(meshGuid).Get());
			ImGui::SameLine();

			static const char* selectedMaterial = nullptr;
			int32_t selectedMatIdx = 0;
			std::vector<const char*> matNames;

			for (const std::string& s : HoneyBadger::AssetsRegistry::Instance->MaterialNames)
			{
				matNames.emplace_back(s.c_str());
			}

			if (ImGui::BeginCombo("##meshMatCombo", selectedMaterial))
			{
				for (int32_t n = 0; n < matNames.size(); n++)
				{
					bool isSelected = (selectedMaterial == matNames[n]);

					if (ImGui::Selectable(matNames[n], isSelected))
					{
						selectedMaterial = matNames[n];
						selectedMatIdx = n;
					}

					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::SameLine();
			if (ImGui::Button("Set Mat", ImVec2(100.0f, 20.0f)))
			{
				if (selectedMaterial)
				{
					MaterialsGuids[selectedMatIdx] = HoneyBadger::AssetsRegistry::Instance->GetMaterialGuid(selectedMaterial).Get();
				}
			}
		}
	}

	RTTI_END()
}