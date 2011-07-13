solution "paketo"
    configurations { "Debug", "Release" }
    location "build"
    targetdir "bin"
    libdirs { "bin" }

    -- libpkto
    project "libpkto"
        kind "SharedLib"
        language "C"
        includedirs { "libpkto/include" }
        files { "libpkto/src/**.c" }
        targetname "pkto"

    -- repoman
    project "repoman"
        kind "ConsoleApp"
        language "C"
        includedirs { "libpkto/include" }
        files { "repoman/src/**.c" }
        links { "pkto" }

    -- paketo
    project "paketo"
        kind "ConsoleApp"
        language "C"
        includedirs { "libpkto/include" }
        files { "paketo/src/**.c" }
        links { "pkto" }

