#pragma once

#include "Epch.h"

#include "Ember\Core.h"
#include "Ember\Events\Event.h"

namespace Ember
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps( const std::string& title = "Ember Engine",
					 unsigned int width = 1280,
					 unsigned int height = 720 )
			: Title( title ), Width( width ), Height( height )
		{
		}
	};

	// Interface representing a desktop system based Window
	class EMBER_API Window
	{
	public:
		using EventCallbackFn = std::function<void( Event& )>;

		virtual ~Window( ) = default;

		virtual void OnUpdate( ) = 0;

		virtual unsigned int GetWidth( ) const = 0;
		virtual unsigned int GetHeight( ) const = 0;

		// Window attributes
		virtual void SetEventCallback( const EventCallbackFn& callback ) = 0;
		virtual void SetVSync( bool enabled ) = 0;
		virtual bool IsVSync( ) const = 0;

		virtual void* GetNativeWindow( ) const = 0;

		static Window* Create( const WindowProps& props = WindowProps( ) );
	};

}