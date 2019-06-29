#include "Epch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Ember
{

	OpenGLContext::OpenGLContext( GLFWwindow* windowHandle )
		: m_WindowHandle( windowHandle )
	{
		EMBER_CORE_ASSERT( windowHandle, "Window handle is null!" )
	}

	void OpenGLContext::Init( )
	{
		glfwMakeContextCurrent( m_WindowHandle );
		int status = gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );
		EMBER_CORE_ASSERT( status, "Failed to initialize Glad!" );
	}

	void OpenGLContext::SwapBuffers( )
	{
		glfwSwapBuffers( m_WindowHandle );
	}

}