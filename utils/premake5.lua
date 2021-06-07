project "NCgenJS"
    language "C++"
    architecture "x86_64"
    cppdialect "C++17"
    kind "StaticLib"

    warnings "Extra"

    location ""
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    -- for #include with ""
    includedirs {
        "src"
    }

    -- for #include with <>
    sysincludedirs {
    }

    links {
    }

