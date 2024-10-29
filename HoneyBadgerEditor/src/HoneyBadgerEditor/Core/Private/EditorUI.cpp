#include "HoneyBadgerEditor/Core/Public/EditorUI.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void HoneyBadgerEditor::EditorUI::CreateWidgets()
{
	CreateLoggerWidget();
}

void HoneyBadgerEditor::EditorUI::CreateLoggerWidget()
{
	ImVec2 HorCenterVerBottomPos = ImGui::GetMainViewport()->GetCenter();
	HorCenterVerBottomPos.y = ImGui::GetMainViewport()->Size.y;

	ImVec2 ConsoleWindowSize = ImGui::GetMainViewport()->Size;
	ConsoleWindowSize.y /= 4;

	ImGuiWindowFlags flags = 0;
	ImGui::SetNextWindowBgAlpha(0.9f);
	ImGui::SetNextWindowPos(HorCenterVerBottomPos, ImGuiCond_Always, ImVec2(0.5f, 1.0f));
	ImGui::SetNextWindowSize(ConsoleWindowSize, ImGuiCond_Always);
	ImGui::Begin("CONSOLE", nullptr, flags);

	for (unsigned int i = 0; i < HoneyBadger::Logger::loggedLineBufferCurrCount; i++)
	{
		switch (HoneyBadger::Logger::logLinesVerbosity[i]) {
		case HoneyBadger::Error:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
			break;
		case HoneyBadger::Warning:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
			break;
		case HoneyBadger::Message:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
			break;
		}

		ImGui::Text(HoneyBadger::Logger::logLines[i].c_str());

		ImGui::PopStyleColor();
	}

	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
	{
		ImGui::SetScrollHereY(0.0f);
	}

	ImGui::End();
}