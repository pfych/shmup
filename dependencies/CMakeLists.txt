include(FetchContent)

# SFML
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)
add_subdirectory(sfml)

# Dear ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.90
)

FetchContent_MakeAvailable(imgui)

# ImGui-SFML
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG v2.6
)
add_subdirectory(imgui-sfml)

# SQLite
FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp
        GIT_TAG 3.3.1
)
FetchContent_MakeAvailable(SQLiteCpp)

# JSON
FetchContent_Declare(
        json
        URL
        https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# FMT
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)