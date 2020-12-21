workspace "Mandelbrot"
  architecture "x64"

  startproject "Mandelbrot"

  configurations {
    "Debug",
    "Release",
    "Dist"
  }

  configuration "**.gl.*"
   buildaction "Copy"

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
indirs = {}
indirs["GLFW"] = "Mandelbrot/vendor/GLFW/include/"
indirs["Glad"] = "Mandelbrot/vendor/Glad/include"

group "Denpendencies"
  include "Mandelbrot/vendor/premake5.glfw.lua"
  include "Mandelbrot/vendor/Glad"
group ""

project "Mandelbrot"
  location "Mandelbrot"
  kind "ConsoleApp"
  language "C++"
  staticruntime "on"
  cppdialect "C++17"

  targetdir("bin/" ..outdir.. "/%{prj.name}")
  objdir("obj/" ..outdir.. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.hpp",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/vendor/stb/**.h",
    "%{prj.name}/vendor/stb/**.cpp",
    -- "%{prj.name}/asset/**.gl.*",
  }

  includedirs {
    "%{prj.name}/asset",
    "%{prj.name}/src",
    "%{prj.name}/src/Engine",
    "%{prj.name}/vendor",
    "%{indirs.GLFW}",
    "%{indirs.Glad}",
  }

  links {
    "GLFW",
    "Glad"
  }

  -- postbuildcommands {
  --    ("{COPY} %{prj.name}/asset/* %{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/")
  -- }

  filter "system:macosx"
    systemversion "latest"
    system "macosx"

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

  filter "configurations:Release"
    optimize "On"

  filter "configurations:Dist"
    optimize "On"