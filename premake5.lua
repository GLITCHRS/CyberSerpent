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

		includedirs
		{
			"%{prj.name}/include",
			"Shell/include"
		}

		links { "Shell" }

group "Shell"
	project "Shell"
		CommonConfig()
		kind "SharedLib"
		defines "DLLExport"

		includedirs
		{
			"%{prj.name}/include",
			"Log/include",
			"vendor/spdlog/include"
		}

		postbuildcommands
		{
			"{MKDIR} ../bin/" .. outputdir .. "/CyberSerpent",
			"{COPYFILE} ../bin/" .. outputdir .. "/%{prj.name}/%{prj.name}.dll ../bin/" .. outputdir .. "/CyberSerpent/%{prj.name}.dll"
		}

		links { "Log" }

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
		