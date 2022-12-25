workspace "TexWriter"
	architecture "x64"
	targetdir "build"

	configurations
	{
		"Debug",
		"Release"
	}
	
	startproject "TexWriter"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "TexWriter/vendor/GLFW/include"
IncludeDir["Glad"] = "TexWriter/vendor/Glad/include"
IncludeDir["pugixml"] = "TexWriter/vendor/pugixml"
IncludeDir["ImGui"] = "TexWriter/vendor/imgui"
IncludeDir["glm"] = "TexWriter/vendor/glm"
IncludeDir["stb_image"] = "TexWriter/vendor/stb_image"


group "Dependencies"
	include "TexWriter/vendor/GLFW"
	include "TexWriter/vendor/Glad"
	include "TexWriter/vendor/imgui"
group ""



group ""

project "TexWriter"
	location "TexWriter"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "twpch.h"
	pchsource "TexWriter/src/twpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",

		"%{prj.name}/vendor/pugixml/**.hpp",
		"%{prj.name}/vendor/pugixml/**.cpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.pugixml}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	postbuildcommands 
	{
		'{COPY} "../TexWriter/assets" "%{cfg.targetdir}/assets"'
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TW_RELEASE"
		runtime "Release"
		optimize "on"

