workspace "EMBER"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "EMBER/vendor/GLFW/include"

include "EMBER/vendor/GLFW"


project "EMBER"
	location "EMBER"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Epch.h"
	pchsource "EMBER/src/Epch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

		links 
	{ 
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EMBER_PLATFORM_WINDOWS",
			"EMBER_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "EMBER_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EMBER_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EMBER_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"EMBER/vendor/spdlog/include",
		"EMBER/src"
	}

	links
	{
		"EMBER"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EMBER_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EMBER_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EMBER_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EMBER_DIST"
		optimize "On"