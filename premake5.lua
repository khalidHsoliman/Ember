workspace "Ember"
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
IncludeDir["GLFW"] = "Ember/vendor/GLFW/include"
IncludeDir["Glad"] = "Ember/vendor/Glad/include"
IncludeDir["ImGui"] = "Ember/vendor/imgui"

include "Ember/vendor/GLFW"
include "Ember/vendor/Glad"
include "Ember/vendor/imgui"


project "Ember"
	location "Ember"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Epch.h"
	pchsource "Ember/src/Epch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

		links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"EMBER_PLATFORM_WINDOWS",
			"EMBER_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Ember/vendor/spdlog/include",
		"Ember/src"
	}

	links
	{
		"Ember"
	}

	filter "system:windows"
		cppdialect "C++17"
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