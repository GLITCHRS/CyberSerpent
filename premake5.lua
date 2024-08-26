workspace "CyberSerpent_WS"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "CyberSerpent"
	location "CyberSerpent"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/include/**.h"
	}

	includedirs
	{
		"%{prj.name}/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CS_DIST"
		optimize "On"
