#include "Epch.h"
#include "ButtonColorPicker.h"

namespace Ember
{
	static std::string g_buttonLabel;
	static std::string g_colorPickerLabel;
	static bool showWheel = false;
	static bool showPreview = true;

	static bool hdr = false;
	static bool alpha_preview = true;
	static bool alpha_half_preview = false;
	static bool options_menu = true;
	static bool showRGB = true;
	static bool showHSV = false;
	static bool showHex = true;


	ButtonColorPicker::ButtonColorPicker(const std::string& windowTitle)
	{
		m_windowTitle = windowTitle;
		g_buttonLabel = "##" + windowTitle + "1";
		g_colorPickerLabel = "##" + windowTitle + "1";

		m_isVisible = false;
		m_color = ImVec4(0, 0, 0, 1);
	}

	void ButtonColorPicker::Update()
	{
		if (ImGui::ColorButton(g_buttonLabel.c_str(), m_color))
		{
			m_isVisible = true;
		}

		if (m_isVisible)
		{
			ShowColorPicker();
		}
	}

	void ButtonColorPicker::ShowColorPicker()
	{
		ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin(m_windowTitle.c_str(), &m_isVisible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowFocus();

		int misc_flags =
			(hdr ? ImGuiColorEditFlags_HDR : 0) |
			(alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf :
			(alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) |
				(options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

		ImGuiColorEditFlags flags = misc_flags;
		flags |= ImGuiColorEditFlags_AlphaBar;
		if (!showPreview)
			flags |= ImGuiColorEditFlags_NoSidePreview;
		flags |= ImGuiColorEditFlags_PickerHueBar;
		if (showWheel)
			flags |= ImGuiColorEditFlags_PickerHueWheel;
		if (showRGB)
			flags |= ImGuiColorEditFlags_RGB;
		if (showHSV)
			flags |= ImGuiColorEditFlags_HSV;
		if (showHex)
			flags |= ImGuiColorEditFlags_HEX;

		ImGui::ColorPicker4(g_colorPickerLabel.c_str(), (float*)&m_color, flags);

		ImGui::Separator();

		// Note: Using hardcoded labels so the settings remain the same for all color pickers

		// WHEEL
		ImGui::Text("Wheel");
		ImGui::SameLine();
		ImGui::Checkbox("##ButtonColorPickerWheel", &showWheel);

		// RGB
		ImGui::SameLine();
		ImGui::Text("RGB");
		ImGui::SameLine();
		ImGui::Checkbox("##ButtonColorPickerRGB", &showRGB);

		// HSV
		ImGui::SameLine();
		ImGui::Text("HSV");
		ImGui::SameLine();
		ImGui::Checkbox("##ButtonColorPickerHSV", &showHSV);

		// HEX
		ImGui::SameLine();
		ImGui::Text("HEX");
		ImGui::SameLine();
		ImGui::Checkbox("##ButtonColorPickerHEX", &showHex);

		ImGui::End();
	}
}