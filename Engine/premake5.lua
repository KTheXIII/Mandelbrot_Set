include "vendor/premake5.imgui.lua"

group "Denpendencies"
  include "vendor/premake5.glfw.lua"
  include "vendor/glad"
group ""

project "Engine"
  kind "StaticLib"
  language "C++"
  staticruntime "on"
  cppdialect "C++17"

  defines {
    "IMGUI_IMPL_OPENGL_LOADER_GLAD"
  }

  targetdir("bin/" ..outdir.. "/%{prj.name}")
  objdir("obj/" ..outdir.. "/%{prj.name}")

  files {
    "src/**.h",
    "src/**.hpp",
    "src/**.cpp",
    "vendor/stb/**.h",
    "vendor/stb/**.cpp",
    "vendor/glm/glm/**.hpp",
    "vendor/glm/glm/**.inl",

    imgui_files
  }

  includedirs {
    "src",
    "vendor",
    "%{indirs.GLFW}",
    "%{indirs.glad}",
    "%{indirs.glm}",
    "%{indirs.ImGui}",
  }

  links {
    "GLFW",
    "glad",
    -- "ImGui"
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

  filter "configurations:Release"
    optimize "On"

  filter "configurations:Dist"
    optimize "On"