workspace "c-init"
    configurations { "Debug", "Release" }

project "cinit"
    kind "ConsoleApp" -- Here we declare the kind of our project
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.c", "src/**.h" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        
    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "On"
