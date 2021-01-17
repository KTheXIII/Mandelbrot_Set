workspace "Mandelbrot"
  architecture "x64"

  startproject "Mandelbrot"

  configurations {
    "Debug",
    "Release",
  }

  flags {
    "MultiProcessorCompile"
  }

  configuration "**.gl.*"
   buildaction "Copy"

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
indirs = {}
indirs["GLFW"] = "%{wks.location}/Mandelbrot/vendor/GLFW/include/"
indirs["glad"] = "%{wks.location}/Mandelbrot/vendor/glad/include"
indirs["glm"] = "%{wks.location}/Mandelbrot/vendor/glm"
indirs["ImGui"] = "%{wks.location}/Mandelbrot/vendor/imgui"

group "Denpendencies"
  include "Mandelbrot/vendor/premake5.glfw.lua"
  include "Mandelbrot/vendor/glad"
  include "Mandelbrot/vendor/premake5.imgui.lua"
group ""

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
    "%{prj.name}/vendor/stb/**.h",
    "%{prj.name}/vendor/stb/**.cpp",
    "%{prj.name}/vendor/glm/glm/**.hpp",
    "%{prj.name}/vendor/glm/glm/**.inl",
    "%{prj.name}/asset/**",

    imgui_files
  }

  includedirs {
    "%{prj.name}/asset",
    "%{prj.name}/src",
    "%{prj.name}/src/Engine",
    "%{prj.name}/vendor",
    "%{indirs.GLFW}",
    "%{indirs.glad}",
    "%{indirs.glm}",
    "%{indirs.ImGui}",
    "%{indirs.ImGui}/backends",
  }

  links {
    "GLFW",
    "glad",
  }

  filter "system:macosx"
    system "macosx"
    systemversion "latest"

    defines {
      "GL_SILENCE_DEPRECATION"
    }

    links {
      "Cocoa.framework",
      "IOKit.framework",
      "CoreVideo.framework",
      "OpenGL.framework"
    }
  
  filter "system:linux"
    system "linux"
    systemversion "latest"

    links {
      "pthread",
      "dl",
      "m",
      "GL",
      "X11"
    }
  
  filter "system:Windows"
    system "Windows"
    systemversion "latest"

    links {
      "OpenGL32.lib",
    }

  filter "configurations:Debug"
    symbols "On"
    debugdir "%{prj.name}"

  filter "configurations:Release"
    optimize "On"