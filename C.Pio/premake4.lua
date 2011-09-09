solution "pio"
    configurations { "Debug", "Release" }
    location "build"
    targetdir "bin"
    libdirs { "bin" }

    -- set c99 flags for gcc
    configuration { "linux", "gmake" }
        buildoptions { "-ansi", "-std=c99", "-fPIC" }

    --include libcpr
    include "libcpr"

    -- libpio - Personal Information Objects Library
    project "libpio"
        kind "SharedLib"
        language "C"
        includedirs { "libcpr/include", "libpio/include" }
        files { "libpio/src/**.c" }
        links { "cpr", "kyotocabinet" }
        targetname "pio"

    -- repoman: Repository Manager
    project "pioc"
        kind "ConsoleApp"
        language "C"
        includedirs { "libcpr/include", "libpio/include" }
        files { "pioc/src/**.c" }
        links { "cpr", "pio", "kyotocabinet" }

