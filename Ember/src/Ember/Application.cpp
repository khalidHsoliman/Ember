#include "Epch.h"

#include "Application.h"
#include "Log.h" 
#include "Events\ApplicationEvent.h" 

#include "GLFW\glfw3.h"

namespace Ember
{
	Application::Application( )
	{
		m_Window = std::unique_ptr<Window>( Window::Create( ) );
	}


	Application::~Application( )
	{
	}

	void Application::Run( )
	{
		while (m_Running)
		{
			glClearColor( 0.5, 0.5, 0.5, 1 );
			glClear( GL_COLOR_BUFFER_BIT );
			m_Window->OnUpdate( );
		}
	}
}