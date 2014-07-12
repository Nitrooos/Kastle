solution "OpenGL"

    project "Castle2"
        configurations { "debug", "release" }
            language "C++"
            kind "ConsoleApp"
            files "src/*.cpp"
            buildoptions { "-w -Wall -std=c++11" }
            linkoptions { "-lGL -lsfml-window -lsfml-system -lGLEW" }
            objdir "obj"

        configuration { "debug" }
            targetdir "debug"
            flags "Symbols"

        configuration { "release" }
            targetdir "release"
            flags "OptimizeSpeed"

        if _ACTION == "clean" then
            os.rmdir("debug")
            os.rmdir("release")
            os.rmdir("obj")
        end
