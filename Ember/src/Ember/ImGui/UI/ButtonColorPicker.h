#pragma once

#include "imgui.h"

namespace Ember
{
	class ButtonColorPicker
	{
	public:
		ButtonColorPicker(const std::string& windowTitle);
		void Update();
		void SetColor(const ImVec4& color) { m_color = color; }
		const ImVec4& GetColor() { return m_color; }
		
	private:
		void ShowColorPicker();
		std::string m_windowTitle;
		bool m_isVisible;
		ImVec4 m_color;
	};
}


