workspace "CyberSerpent_WS"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

function CommonConfig()
	location "%{prj.name}"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/include/**.h"
	}

	filter "configurations:Debug"
			defines "CS_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "CS_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "CS_DIST"
			optimize "On"

		filter "system:linux"
			cppdialect "gnu++20"

		filter "system:windows"
			cppdialect "C++20"
			staticruntime "On"
			systemversion "latest"
			defines "CS_WINDOWS"
end

group "Core"
	project "CyberSerpent"
		CommonConfig()
		kind "ConsoleApp"
		links "Shell"

		includedirs
		{
			"%{prj.name}/include",
			"Shell/include"
		}

group "Shell"
	project "Shell"
		CommonConfig()
		kind "SharedLib"
		defines "DLLExport"
		links "Log"

		includedirs
		{
			"%{prj.name}/include",
			"Log/include",
			"vendor/spdlog/include"
		}

		filter "system:windows"
			postbuildcommands
			{
				"{MKDIR} ../bin/" .. outputdir .. "/CyberSerpent",
				"{COPYFILE} ../bin/" .. outputdir .. "/%{prj.name}/%{prj.name}.dll ../bin/" .. outputdir .. "/CyberSerpent/%{prj.name}.dll"
			}

		filter "system:linux"
			postbuildcommands
			{
				"{MKDIR} ../bin/" .. outputdir .. "/CyberSerpent",
				"{COPYFILE} ../bin/" .. outputdir .. "/%{prj.name}/%{prj.name}.so ../bin/" .. outputdir .. "/CyberSerpent/%{prj.name}.so"
			}

	project "Log"
		CommonConfig()
		location "Log"
		kind "StaticLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		includedirs
		{
			"%{prj.name}/include",
			"vendor/spdlog/include"
		}
		