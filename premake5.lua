workspace "Mandelbrot"
  architecture "x64"

  startproject "Mandelbrot"

  configurations {
    "Debug",
    "Release",
    "Dist"
  }

  flags {
    "MultiProcessorCompile"
  }

  configuration "**.gl.*"
   buildaction "Copy"

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
indirs = {}
indirs["GLFW"] = "%{wks.location}/Engine/vendor/GLFW/include"
indirs["glad"] = "%{wks.location}/Engine/vendor/glad/include"
indirs["glm"] = "%{wks.location}/Engine/vendor/glm"
indirs["ImGui"] = "%{wks.location}/Engine/vendor/imgui"
indirs["vendor"] = "%{wks.location}/Engine/vendor"
indirs["Engine"] = "%{wks.location}/Engine/src"

include "Engine"

project "Mandelbrot"
  location "Mandelbrot"
  kind "ConsoleApp"
  language "C++"
  staticruntime "on"
  cppdialect "C++17"

  defines {
    "IMGUI_IMPL_OPENGL_LOADER_GLAD"
  }

  targetdir("bin/" ..outdir.. "/%{prj.name}")
  objdir("obj/" ..outdir.. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.hpp",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/asset/**.gl.*",

    imgui_files
  }

  includedirs {
    "%{prj.name}/asset",
    "%{prj.name}/src",
    "%{indirs.Engine}",
    "%{indirs.vendor}",
    "%{indirs.GLFW}",
    "%{indirs.glad}",
    "%{indirs.glm}",
    "%{indirs.ImGui}",
    "%{indirs.ImGui}/backends",
  }

  links {
    "Engine"
  }

  -- postbuildcommands {
  --    ("{COPY} %{prj.name}/asset/* %{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/")
  -- }

  filter "system:macosx"
    system "macosx"
    systemversion "latest"

  filter "system:linux"
    system "linux"
    systemversion "latest"

  filter "system:Windows"
    system "Windows"
    systemversion "latest"

  filter "configurations:Debug"
    symbols "On"
    debugdir "%{prj.name}"

  filter "configurations:Release"
    optimize "On"

  filter "configurations:Dist"
    optimize "On"
