#pragma once

#ifdef EMBER_PLATFORM_WINDOWS

extern Ember::Application* Ember::CreateApplication( );

int main( int argc, char** argv )
{
	Ember::Log::Init( );
	EMBER_CORE_WARN( "Initialized Log!" );
	int a = 5;
	EMBER_CORE_INFO( "Hello! Var={0}", a );

	auto app = Ember::CreateApplication( );
	app->Run( );
	delete app;
}

#endif // EMBER_PLATFORM_WINDOWS
