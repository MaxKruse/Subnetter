workspace "Subnetter"
	startproject "Subnetter"

	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
	}

outputDir = "/%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

project "Subnetter"
	location "Subnetter"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	characterset "Unicode"
	vectorextensions "AVX"

	targetdir ("bin/%{prj.name}" .. outputDir)
	objdir ("bin/%{prj.name}/intermediates" .. outputDir)

	pchheader "pch.h"
	pchsource "Subnetter/src/pch.cpp"

	files
	{
		"%{prj.name}/src/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src/include",
		"submodules/CommandParser/CP/src/include"
	}

	defines
	{
		""
	}

	links
	{
		
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		optimize "Debug"
		symbols "Full"

	filter "configurations:Release"
		optimize "On"
		symbols "Off"