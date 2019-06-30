#pragma once

#include "Core.h"

#include "Window.h"
#include "Ember/LayerStack.h"
#include "Ember/Events/Event.h"
#include "Ember/Events/ApplicationEvent.h"

#include "Ember/Renderer/Shader.h"
#include "Ember/Renderer/Buffer.h"

#include "Ember/ImGui/ImGuiLayer.h"

namespace Ember
{

	class EMBER_API Application
	{
	public:
		Application( );
		virtual ~Application( ) = default;

		void Run( );

		void OnEvent( Event& e );

		void PushLayer( Layer* layer );
		void PushOverlay( Layer* layer );

		inline Window& GetWindow( )
		{
			return *m_Window;
		}

		inline static Application& Get( )
		{
			return *s_Instance;
		}

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	private:
		bool OnWindowClose( WindowCloseEvent& e );

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication( );

}