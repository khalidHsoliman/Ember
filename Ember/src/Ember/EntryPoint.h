#pragma once

#ifdef EMBER_PLATFORM_WINDOWS

extern Ember::Application* Ember::CreateApplication(); 

int main(int argc, char** argv)
{
	auto app = Ember::CreateApplication(); 
	app->Run(); 
	delete app;
}

#endif // EMBER_PLATFORM_WINDOWS
