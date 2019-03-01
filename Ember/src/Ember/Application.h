#pragma once

#include "Core.h"

namespace Ember
{
	class EMBER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication(); 
}