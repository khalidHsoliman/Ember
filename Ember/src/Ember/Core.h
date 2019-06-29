#pragma once

#ifdef EMBER_PLATFORM_WINDOWS
#if EMBER_DYNAMIC_LINK
#ifdef EMBER_BUILD_DLL
#define EMBER_API __declspec(dllexport)
#else
#define EMBER_API __declspec(dllimport)
#endif // EMBER_BUILD_DLL
#else
#define EMBER_API 
#endif
#else 
#error Ember only support Windows!
#endif // EMBER_PLATFORM_WINDOWS


#ifdef EMBER_DEBUG
#define EMBER_ENABLE_ASSERTS
#endif

// Windows specific assert 
#ifdef EMBER_ENABLE_ASSERTS
#define EMBER_ASSERT(x, ...) { if(!(x)) { EMBER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define EMBER_CORE_ASSERT(x, ...) { if(!(x)) { EMBER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define EMBER_ASSERT(x, ...)
#define EMBER_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define EMBER_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 
