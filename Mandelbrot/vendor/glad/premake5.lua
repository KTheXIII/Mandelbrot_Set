project "glad"
  kind "StaticLib"
  language "C"

  targetdir ("%{wks.location}/bin/" .. outdir .. "/%{prj.name}")
  objdir ("%{wks.location}/obj/" .. outdir .. "/%{prj.name}")

  files {
    "include/glad/glad.h",
    "include/KHR/khrplatform.h",
    "src/glad.c"
  }

  includedirs {
    "include"
  }

  filter "system:windows"
    systemversion "latest"
    staticruntime "On"
  
  filter { "system:windows", "configurations:Release" }
    buildoptions "/MT"
