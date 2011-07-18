solution "paketo"
    configurations { "Debug", "Release" }
    location "build"
    targetdir "bin"
    libdirs { "bin" }

    -- set c99 flags for gcc
    configuration { "linux", "gmake" }
        buildoptions { "-ansi", "-std=c99", "-fPIC" }

    -- libosal: OS Abstraction Layer
    project "libosal"
        kind "StaticLib"
        language "C"
        includedirs { "libosal/include" }
        files { "libosal/src/**.c" }
        targetname "osal"

    -- libpkto: Paketo Library
    project "libpkto"
        kind "SharedLib"
        language "C"
        includedirs { "libosal/include", "libpkto/include" }
        files { "libpkto/src/**.c" }
        links { "osal", "yajl", "curl", "archive" } -- kyotocabinet, gpgme
        targetname "pkto"

    -- repoman: Repository Manager
    project "repoman"
        kind "ConsoleApp"
        language "C"
        includedirs { "libpkto/include" }
        files { "repoman/src/**.c" }
        links { "pkto" }
        -- postbuildcommands { "cp default.conf bin/" }

    -- paketo: Package Manager
    project "paketo"
        kind "ConsoleApp"
        language "C"
        includedirs { "libpkto/include" }
        files { "paketo/src/**.c" }
        links { "pkto" }

