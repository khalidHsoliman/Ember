#pragma once

#ifdef EMBER_PLATFORM_WINDOWS
#ifdef EMBER_BUILD_DLL
#define EMBER_API __declspec(dllexport)
#else
#define EMBER_API __declspec(dllimport)
#endif // EMBER_BUILD_DLL
#else 
#error Ember only support Windows!
#endif // EMBER_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
