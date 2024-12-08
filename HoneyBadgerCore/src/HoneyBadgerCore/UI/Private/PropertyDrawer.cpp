#include "hbpch.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>
#include <HoneyBadgerCore/Math/Public/MathCore.h>
#include "HoneyBadgerCore/Core/Public/EventSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/Components.h"

// TODO: Handle test concat better

void PrintName(const char* name)
{
	char result[100];

	strcpy(result, name);
	strcat(result, ": ");

	ImGui::Text(result);
}

void HoneyBadger::DrawEditorComponentName(const char* name)
{
	ImGui::Separator();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
	ImGui::Text(name);
	ImGui::PopStyleColor();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
	ImGui::SameLine();
	std::string buff = "##";
	buff += name;
	buff += "X";

	if (ImGui::Button(buff.c_str(), ImVec2(20, 20)))
	{
		RemoveComponentEvent::RemoveComponentEventPayload payload = 
			{ HoneyBadger::Components::ComponentsNameTypeIdNameMap[name] };
		HB_POST_EVENT(RemoveComponentEvent::Type(), &payload);
	}
	ImGui::PopStyleColor();

	ImGui::Separator();
}

void HoneyBadger::DrawEditorProperty(const char* name, const std::string& value)
{
	PrintName(name);

	ImGui::SameLine();
	ImGui::Text(value.c_str());
}

void HoneyBadger::DrawEditorProperty(const char* name, int32_t value)
{
	PrintName(name);

	ImGui::SameLine();

	if (value > 0)
	{
		ImGui::Text(std::to_string(value).c_str());
	}
	else
	{
		ImGui::Text("INVALID");
	}
}

void HoneyBadger::DrawEditorPropertyEditable(const char* name, std::string& value)
{
	static char Prop[128] = "";
	if (value.size() > 0)
	{
		for (int32_t i = 0; i < value.size(); i++)
		{
			Prop[i] = value[i];
		}
	
	}

	Prop[value.size()] = '\0';

	ImGui::InputTextWithHint("##name", name, Prop, IM_ARRAYSIZE(Prop));

	value = Prop;
}

void HoneyBadger::DrawEditorPropertyEditable(const char* name, Vec3& value)
{
	std::string propBase = "##";
	propBase += name;

	PrintName(name);
	ImGui::SameLine();
	ImGui::PushItemWidth(50);
	ImGui::DragFloat((propBase + "_x").c_str(), &value.x, 0.01f, 0.0f, 0.0f, "%.2f");
	ImGui::SameLine();
	ImGui::DragFloat((propBase + "_y").c_str(), &value.y, 0.01f, 0.0f, 0.0f, "%.2f");
	ImGui::SameLine();
	ImGui::DragFloat((propBase + "_z").c_str(), &value.z, 0.01f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
}

void HoneyBadger::DrawEditorPropertyEditable(const char* name, Quat& value)
{
	float pitch = HoneyBadger::MathCore::RadToDeg(value.GetPitch());
	float yaw = HoneyBadger::MathCore::RadToDeg(value.GetYaw());
	float roll = HoneyBadger::MathCore::RadToDeg(value.GetRoll());
	
	PrintName(name);
	ImGui::SameLine();
	ImGui::PushItemWidth(50);
	ImGui::DragFloat("##roll", &roll, 1.0f, 0.0f, 0.0f, "%.2f");
	ImGui::SameLine();
	ImGui::DragFloat("##pitch", &pitch, 1.0f, 0.0f, 0.0f, "%.2f");
	ImGui::SameLine();
	ImGui::DragFloat("##yaw", &yaw, 1.0f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	value = HoneyBadger::Quat::FromRPY(
		HoneyBadger::MathCore::DegToRad(roll),
		HoneyBadger::MathCore::DegToRad(pitch),
		HoneyBadger::MathCore::DegToRad(yaw));
}
