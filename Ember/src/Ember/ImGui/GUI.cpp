#include "Epch.h"
#include "GUI.h"

//-->Should be Seperated
#include <filesystem>
#include <fstream>

namespace Ember
{
	bool dialog_new_active = false;
	bool dialog_open_active = false;
	bool inspector_active = true;
	
	void ShowMainMenuBar()
	{
		//MainMenu
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					dialog_new_active = true;
				}
				if (ImGui::MenuItem("Open", "Ctrl+O"))
				{
					static char str0[128] = "C:/";
					ImGui::Begin("Open File");
					ImGui::Text("Directory");
					ImGui::SameLine();
					ImGui::InputText("Input", str0, IM_ARRAYSIZE(str0));
					ImGui::End();
				}
				if (ImGui::BeginMenu("Open Recent"))
				{
					ImGui::MenuItem("fish_hat.c");
					ImGui::MenuItem("fish_hat.inl");
					ImGui::MenuItem("fish_hat.h");
					if (ImGui::BeginMenu("More.."))
					{
						ImGui::MenuItem("Hello");
						ImGui::MenuItem("Sailor");

						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {}
				if (ImGui::MenuItem("Save As..")) {}
				ImGui::Separator();
				if (ImGui::BeginMenu("Options"))
				{
					static bool enabled = true;
					ImGui::MenuItem("Enabled", "", &enabled);
					ImGui::BeginChild("child", ImVec2(0, 60), true);
					for (int i = 0; i < 10; i++)
						ImGui::Text("Scrolling Text %d", i);
					ImGui::EndChild();
					static float f = 0.5f;
					static int n = 0;
					static bool b = true;
					ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
					ImGui::InputFloat("Input", &f, 0.1f);
					ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
					ImGui::Checkbox("Check", &b);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Colors"))
				{
					float sz = ImGui::GetTextLineHeight();
					for (int i = 0; i < ImGuiCol_COUNT; i++)
					{
						const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
						ImVec2 p = ImGui::GetCursorScreenPos();
						ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
						ImGui::Dummy(ImVec2(sz, sz));
						ImGui::SameLine();
						ImGui::MenuItem(name);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Disabled", false)) // Disabled
				{
					IM_ASSERT(0);
				}
				if (ImGui::MenuItem("Checked", NULL, true)) {}
				if (ImGui::MenuItem("Quit", "Alt+F4")) {}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				//...
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				//...
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void ShowNewFileDialog(bool* dialog_new_active)
	{
		static char str0[128] = "D:/New Ember Project";
		static char str1[128] = "Project1.Ember";
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin("New Project");
		//ImGui::Text("Directory");
		//ImGui::SameLine();
		ImGui::InputText("Directory", str0, IM_ARRAYSIZE(str0));
		ImGui::SameLine();
		ImGui::Button("Browse", ImVec2(100, 25));
		ImGui::NewLine();
		//ImGui::Text("Project Name");
		//ImGui::SameLine();
		ImGui::InputText("Project Name", str1, IM_ARRAYSIZE(str1));
		ImGui::NewLine();
		if (ImGui::Button("Create New Project", ImVec2(150, 50)))
		{
			//-->Should be Seperated in FileSystem script
			std::filesystem::create_directory(str0);
			std::ofstream newFile;
			//newFile.open("D:/New Ember Project/Project1.Ember");
		}
		
		ImGui::End();
	}

	void ShowOpenFileDialog(bool* dialog_open_active)
	{
		static char str0[128] = "C:/";
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin("Open File");
		ImGui::Text("Directory");
		ImGui::SameLine();
		ImGui::InputText("", str0, IM_ARRAYSIZE(str0));
		ImGui::SameLine();
		ImGui::Button("Browse", ImVec2(100, 25));
		ImGui::NewLine();
		ImGui::Button("Open File", ImVec2(150, 50));
		ImGui::End();
	}

	void ShowLogWindow()
	{
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin("Example: Log");

		

		ImGui::End();
	}

	void ShowInspector(bool * inspector_active)
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin("Inspector", inspector_active);
		ImGui::BeginChild("Transport");

		ImGui::InputFloat("X", &x, 0.01, 1.0, "%.3f");
		ImGui::InputFloat("Y", &y, 0.01, 1.0, "%.3f");
		ImGui::InputFloat("Z", &z, 0.01, 1.0, "%.3f");
		ImGui::EndChild();
		ImGui::End();
	}

	void ShowGUI(bool * p_open)
	{
		ShowMainMenuBar();
		ShowInspector(&inspector_active);
		ShowLogWindow();
		if (dialog_new_active)
		{
			ShowNewFileDialog(&dialog_new_active);
		}
	}

}