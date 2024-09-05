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
		defines "CS_WINDOWS"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
end

group "Core"
	project "CyberSerpent"
		links { "Shell" }
		kind "ConsoleApp"

		includedirs
		{
			"%{prj.name}/include",
			"Shell/include",
			"vendor/spdlog/include"
		}
		CommonConfig()

group "Shell"
	project "Shell"
		kind "StaticLib"

		includedirs
		{
			"%{prj.name}/include",
			"vendor/spdlog/include"
		}

		CommonConfig()
--[[
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
				"{COPYFILE} ../bin/" .. outputdir .. "/%{prj.name}/lib%{prj.name}.so ../bin/" .. outputdir .. "/CyberSerpent/%{prj.name}.so"
			}
]]--