project "glad"
  kind "StaticLib"
  language "C"

  targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{cfg.system}-%{cfg.architecture}/%{prj.name}")
  objdir ("%{wks.location}/obj/%{cfg.buildcfg}/%{cfg.system}-%{cfg.architecture}/%{prj.name}")

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
