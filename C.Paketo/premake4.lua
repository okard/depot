solution "paketo"
    configurations { "Debug", "Release" }
    location "build"
    targetdir "bin"
    libdirs { "bin" }

    -- set c99 flags for gcc
    configuration { "linux", "gmake" }
        buildoptions { "-ansi", "-std=c99", "-fPIC" }

    --include libcpr
    include "libcpr"

    -- libpkto: Paketo Library
    project "libpkto"
        kind "SharedLib"
        language "C"
        includedirs { "libcpr/include", "libpkto/include" }
        files { "libpkto/src/**.c" }
        links { "cpr", "yajl", "curl", "archive" } -- kyotocabinet, gpgme
        targetname "pkto"

    -- repoman: Repository Manager
    project "repoman"
        kind "ConsoleApp"
        language "C"
        includedirs { "libcpr/include", "libpkto/include" }
        files { "repoman/src/**.c" }
        links { "cpr", "pkto" }
        -- postbuildcommands { "cp default.conf bin/" }

    -- paketo: Package Manager
    project "paketo"
        kind "ConsoleApp"
        language "C"
        includedirs { "libcpr/include", "libpkto/include" }
        files { "paketo/src/**.c" }
        links { "cpr", "pkto" }

