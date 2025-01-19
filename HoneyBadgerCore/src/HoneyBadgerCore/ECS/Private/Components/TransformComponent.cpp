#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace HoneyBadger
{
	std::vector<HBString> TransformComponent::EntityNames = {};

	RTTI_BEGIN(TransformComponent)

	const char* ParentCStr = Parent.c_str();

	ImGui::Text("Parent: ");
	ImGui::SameLine();
	if (ImGui::BeginCombo("##transformParentCombo", ParentCStr))
	{
		for (int n = 0; n < EntityNames.size(); n++)
		{
			bool isSelected = (ParentCStr == EntityNames[n].Get());
			if (ImGui::Selectable(EntityNames[n].Get(), isSelected))
			{
				Parent = EntityNames[n].Get();
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	
	RTTI_PROPERTY_EDITABLE(pos, Position)
	RTTI_PROPERTY_EDITABLE(rot, Rotation)
	RTTI_PROPERTY_EDITABLE(scale, Scale)
	RTTI_END()
}