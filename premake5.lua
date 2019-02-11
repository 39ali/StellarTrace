workspace "StellarTrace"
	architecture "x64"

	configurations{
		"Debug","Release"
		}


outdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir={}



project "StellarTrace"
	location "StellarTrace"
	kind "ConsoleApp"
	language "C++"
	

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-init/" .. outdir .. "/%{prj.name}")

	files {
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor",	
	}



	filter "system:windows"
		cppdialect "c++17"	
		systemversion "latest"
	
	
		
	filter "configurations:Debug"
			
			symbols "On"
			runtime "Debug"

	filter "configurations:Release"
			
			optimize "Speed"
			runtime "Release"
			 





