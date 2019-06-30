#pragma once

#include <string>
#include <imgui.h>
#include <imgui_internal.h>

namespace Ember
{

	class Widget
	{
	public:
		Widget() { m_window = nullptr; }
		virtual ~Widget() = default;

		virtual bool Begin()
		{
			if (!m_isWindow || !m_isVisible)
				return false;

			ImGui::SetNextWindowSize(ImVec2(m_xMin, m_yMin), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSizeConstraints(ImVec2(m_xMin, m_yMin), ImVec2(m_xMax, m_yMax));
			ImGui::Begin(m_title.c_str(), &m_isVisible, m_windowFlags);
			m_windowBegun = true;

			return true;
		}

		virtual void Tick(float deltaTime = 0.0f) = 0;

		virtual bool End()
		{
			if ((!m_isWindow || !m_isVisible) && !m_windowBegun)
				return false;

			m_window = ImGui::GetCurrentWindow();
			m_height = ImGui::GetWindowHeight();
			ImGui::End();
			m_windowBegun = false;

			return true;

		}

		bool IsWindow() { return m_isWindow; }
		bool& GetVisible() { return m_isVisible; }
		void SetVisible(bool isVisible) { m_isVisible = isVisible; }
		float GetHeight() { return m_height; }
		ImGuiWindow* GetWindow() { return m_window; }
		const std::string& GetTitle() { return m_title; }

	protected:
		bool m_isVisible = true;
		bool m_isWindow = true;
		int m_windowFlags = ImGuiWindowFlags_NoCollapse;
		float m_xMin = 0;
		float m_xMax = FLT_MAX;
		float m_yMin = 0;
		float m_yMax = FLT_MAX;
		float m_height = 0;

		std::string m_title;
		ImGuiWindow* m_window;
	private:
		bool m_windowBegun = false;
	};
}