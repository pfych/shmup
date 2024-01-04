cmake_minimum_required(VERSION 3.27)
project(shmup__)

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0148 NEW)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Load dependencies
add_subdirectory(dependencies)

# Configure the resources directory
set(RESOURCES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(RESOURCES_DEST_DIR ${CMAKE_BINARY_DIR}/bin/resources)

# Recursively copy resources
file(COPY ${RESOURCES_SOURCE_DIR}/ DESTINATION ${RESOURCES_DEST_DIR})

add_executable(shmup__ main.cpp
        src/Game/Game.cpp
        src/Game/Game.h
        src/BulletPattern/BulletPattern.cpp
        src/BulletPattern/BulletPattern.h
        src/BulletPattern/BulletDesigner/BulletDesigner.cpp
        src/BulletPattern/BulletDesigner/BulletDesigner.h
        src/Point/Point.h
        src/utils/bezierUtils.cpp
        src/utils/bezierUtils.h
        src/Point/Point.cpp)
target_link_libraries(shmup__ PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML SQLiteCpp)
target_compile_features(shmup__ PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET shmup__
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
            VERBATIM)
endif ()

install(TARGETS shmup__)
