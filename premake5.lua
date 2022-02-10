workspace "OPENGL-TEMPLATE"
  startproject "App"

  architecture "x86_64"

  configurations { "Debug", "Release" }


  filter { "configurations:Debug" }
  symbols "On"


  filter { "configurations:Release" }
  optimize "On"

  filter { }

  outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

  IncludeDir = {}
  IncludeDir["GLFW"] = "app/vendor/GLFW/include/"
  IncludeDir["Khr"] = "app/vendor/KHR/include/"
  IncludeDir["Glad"] = "app/vendor/"

project "App"

  kind "ConsoleApp"

  language "C++"
  cppdialect "C++17"

  targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
  objdir ("./bin-int/" .. outputdir .. "/%{prj.name}")

  files {"app/src/**.cpp", "app/src/renderer/**.cpp" , "app/src/window/**.cpp", "app/vendor/glad/**.c"}

  includedirs {
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.Khr}",
    "app/src/renderer/",
    "app/src/window/"
  }
  libdirs "vendor/GLFW/lib"

  links {"glfw3", "opengl32" , "gdi32"}





