#include "hbpch.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>

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

void HoneyBadger::DrawEditorPropertyEditable(const char* name, Vec3& value)
{
	PrintName(name);
	ImGui::SameLine();
	ImGui::PushItemWidth(75);
	ImGui::DragFloat("x", &value.x, 0.01f, 0.0f, 0.0f, "%.2f");
	ImGui::SameLine();
	ImGui::DragFloat("y", &value.y, 0.01f, 0.0f, 0.0f, "%.2f");
	ImGui::SameLine();
	ImGui::DragFloat("z", &value.z, 0.01f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
}
