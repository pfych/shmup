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
        GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03 # 1.82
)

FetchContent_MakeAvailable(imgui)

# ImGui-SFML
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35 # 2.3
)
add_subdirectory(imgui-sfml)

FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp
        GIT_TAG 3.3.1
)
FetchContent_MakeAvailable(SQLiteCpp)
