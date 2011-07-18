solution "paketo"
    configurations { "Debug", "Release" }
    location "build"
    targetdir "bin"
    libdirs { "bin" }

    -- set c99 flags for gcc
    configuration { "linux", "gmake" }
        buildoptions { "-ansi", "-std=c99" }


    -- libpkto
    project "libpkto"
        kind "SharedLib"
        language "C"
        includedirs { "libpkto/include" }
        files { "libpkto/src/**.c" }
        links { "yajl", "curl", "archive" } -- kyotocabinet, gpgme
        targetname "pkto"

    -- repoman
    project "repoman"
        kind "ConsoleApp"
        language "C"
        includedirs { "libpkto/include" }
        files { "repoman/src/**.c" }
        links { "pkto" }
        -- postbuildcommands { "cp default.conf bin/" }

    -- paketo
    project "paketo"
        kind "ConsoleApp"
        language "C"
        includedirs { "libpkto/include" }
        files { "paketo/src/**.c" }
        links { "pkto" }

