workspace "Ember"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["glm"] = "Ember/vendor/glm"

include "Ember/vendor/GLFW"
include "Ember/vendor/Glad"
include "Ember/vendor/imgui"

project "Ember"
	location "Ember"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Epch.h"
	pchsource "Ember/src/Epch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

		links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EMBER_PLATFORM_WINDOWS",
			"EMBER_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "EMBER_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EMBER_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EMBER_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Ember/src",
		"Ember/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Ember"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EMBER_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EMBER_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EMBER_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EMBER_DIST"
		runtime "Release"
		optimize "on"