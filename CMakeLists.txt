cmake_minimum_required(VERSION 3.16)
project(Athena LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

option(BOX2D_BUILD_UNIT_TESTS OFF)
FetchContent_Declare(box2d
        GIT_REPOSITORY https://github.com/erincatto/Box2D.git
        GIT_TAG v2.4.1)
FetchContent_MakeAvailable(box2d)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(rapidcsv
        GIT_REPOSITORY https://github.com/d99kris/rapidcsv
        GIT_TAG v8.82
)
FetchContent_MakeAvailable(rapidcsv)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(assets)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

install(TARGETS ${CMAKE_PROJECT_NAME})
