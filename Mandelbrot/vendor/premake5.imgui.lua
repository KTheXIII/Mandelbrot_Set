project "ImGui"
  kind "StaticLib"
  language "C++"

  targetdir("bin/" ..outdir.. "/%{prj.name}")
  objdir("obj/" ..outdir.. "/%{prj.name}")

  files {
    "imgui/imconfig.h",
    "imgui/imgui_demo.cpp",
    "imgui/imgui_draw.cpp",
    "imgui/imgui_internal.h",
    "imgui/imgui_tables.cpp",
    "imgui/imgui_widgets.cpp",
    "imgui/imgui.cpp",
    "imgui/imgui.h",
    "imgui/imstb_rectpack.h",
    "imgui/imstb_textedit.h",
    "imgui/imstb_truetype.h",
  }

  filter "system:macosx"
    system "macosx"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"

  filter "system:windows"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"

  filter "system:linux"
    pic "On"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"

  filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    runtime "Release"
    optimize "on"
  
  filter { "system:windows", "configurations:Release" }
    buildoptions "/MT"