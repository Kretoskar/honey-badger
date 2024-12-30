#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"
#include "HoneyBadgerEditor/Core/Public/EditorUI.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"
#include "HoneyBadgerCore/ECS/Public/Components/Components.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>

char HoneyBadgerEditor::EditorUI::SceneName[512] = "";

void HoneyBadgerEditor::EditorUI::CreateWidgets()
{
	CreateLoggerWidget();
	CreateSceneWidget();
	CreateDetailsWidget();
	CreateToolbarWidget();
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

void HoneyBadgerEditor::EditorUI::CreateSceneWidget()
{
	ImVec2 SceneWindowSize = ImGui::GetMainViewport()->Size;
	SceneWindowSize.x /= 6;
	SceneWindowSize.y = (SceneWindowSize.y / 4) * 3;

	ImGuiWindowFlags flags = 0;

	ImGui::SetNextWindowBgAlpha(0.8f);
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(SceneWindowSize, ImGuiCond_Always);
	ImGui::Begin("SCENE", nullptr, flags);

	if (ImGui::Button("---New---", ImVec2((SceneWindowSize.x - 15.0f) / 2, 50.0f)))
	{
		_editor->NewEntity();
	}

	for (auto& entity : _entityMap)
	{
		if (ImGui::Button(entity.second.Get(), ImVec2(SceneWindowSize.x - 15.0f, 50.0f)))
		{
			_anyEntitySelected = true;
			_selectedEntity = entity.first;
		}
	}


	ImGui::End();
}

void HoneyBadgerEditor::EditorUI::CreateDetailsWidget()
{
	ImVec2 DetailsWindowSize = ImGui::GetMainViewport()->Size;
	DetailsWindowSize.x /= 6;
	DetailsWindowSize.y = (DetailsWindowSize.y / 4) * 3;

	ImGuiWindowFlags flags = 0;

	ImGui::SetNextWindowBgAlpha(0.8f);
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x, 0.0f), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
	ImGui::SetNextWindowSize(DetailsWindowSize, ImGuiCond_Always);
	ImGui::Begin("DETAILS", nullptr, flags);

	if (!_anyEntitySelected) 
	{
		ImGui::End();
		return; 
	}

	static const char* selectedComponent = nullptr;
	const std::vector<char*> names = HoneyBadger::Components::Names;

	if (ImGui::BeginCombo("##addComponentCombo", selectedComponent))
	{
		for (int n = 0; n < names.size(); n++)
		{
			bool isSelected = (selectedComponent == names[n]);
			if (ImGui::Selectable(names[n], isSelected))
			{
				selectedComponent = names[n];
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	ImGui::SameLine();
	if (ImGui::Button("Add ", ImVec2(100.0f, 20.0f)))
	{
		HoneyBadger::Components::AddComponent(selectedComponent, *_editor->GetECS(), _selectedEntity);
	}

	HoneyBadger::Components::DrawAllComponents(*_editor->GetECS(), _selectedEntity);

	ImGui::End();
}

void HoneyBadgerEditor::EditorUI::CreateToolbarWidget()
{
	ImVec2 TopWindowSize = ImGui::GetMainViewport()->Size;
	TopWindowSize.x /= 6;
	TopWindowSize.x *= 4;
	TopWindowSize.y /= 14;

	ImGuiWindowFlags flags = 0;

	ImGui::SetNextWindowBgAlpha(0.8f);
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x / 2, 0.0f), ImGuiCond_Always, ImVec2(0.5f, 0.0f));
	ImGui::SetNextWindowSize(TopWindowSize, ImGuiCond_Always);
	ImGui::Begin("TOOLBAR", nullptr, flags);
	if (ImGui::Button("SAVE", ImVec2(ImGui::GetMainViewport()->Size.x / 16, ImGui::GetMainViewport()->Size.y / 32)))
	{
		_editor->SaveScene(SceneName);
	}
	ImGui::SameLine();
	if (ImGui::Button("LOAD", ImVec2(ImGui::GetMainViewport()->Size.x / 16, ImGui::GetMainViewport()->Size.y / 32)))
	{
		_editor->LoadScene(SceneName);
		
	}
	ImGui::SameLine();
	ImGui::InputTextWithHint("##scenePath", "scene path", SceneName, IM_ARRAYSIZE(SceneName));
	ImGui::SameLine();

	std::string fpsText = "FPS: ";
	fpsText += std::to_string(1000 / dt);

	ImGui::Text(fpsText.c_str());

	ImGui::End();
}

void HoneyBadgerEditor::EditorUI::RemoveComponent(void* payload)
{
	HoneyBadger::HBString* name = reinterpret_cast<HoneyBadger::HBString*>(payload);
	_editor->GetECS()->RemoveComponent(_selectedEntity, *name);
}

void HoneyBadgerEditor::EditorUI::SetEntityMap(std::map<HoneyBadger::Entity, HoneyBadger::HBString> map)
{
	_entityMap = std::move(map);
}
