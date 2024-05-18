cmake_minimum_required(VERSION 3.16)
project(Athena LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Fetch SFML
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Fetch ImGui
FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

# Fetch ImGui-SFML
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

# Fetch Box2D
option(BOX2D_BUILD_UNIT_TESTS OFF)
FetchContent_Declare(box2d
    GIT_REPOSITORY https://github.com/erincatto/Box2D.git
    GIT_TAG v2.4.1)
FetchContent_MakeAvailable(box2d)

# MariaDB OS default install paths
if(WIN32)
    set(DEFAULT_MARIADB_CONNECTOR_CPP_INSTALL_DIR "C:/Program Files/MariaDB/MariaDB C++ Connector 64-bit")
elseif(APPLE)
    set(DEFAULT_MARIADB_CONNECTOR_CPP_INSTALL_DIR "/usr/local/opt/mariadb-connector-cpp")
else()
    set(DEFAULT_MARIADB_CONNECTOR_CPP_INSTALL_DIR "/usr/local")
endif()

set(MARIADB_CONNECTOR_CPP_INSTALL_DIR "${DEFAULT_MARIADB_CONNECTOR_CPP_INSTALL_DIR}" CACHE PATH "Path to the MariaDB Connector/C++ installation")

include_directories(
    "${MARIADB_CONNECTOR_CPP_INSTALL_DIR}/include"
    "${MARIADB_CONNECTOR_CPP_INSTALL_DIR}/include/mariadb"
    "${MARIADB_CONNECTOR_CPP_INSTALL_DIR}/include/mariadb/conncpp"
)

set(MARIADB_CONNECTOR_CPP_LIB_DIRS "${MARIADB_CONNECTOR_CPP_INSTALL_DIR}" "${MARIADB_CONNECTOR_CPP_INSTALL_DIR}/lib")

link_directories(${MARIADB_CONNECTOR_CPP_LIB_DIRS})

if(WIN32)
    set(MARIADB_CONNECTOR_CPP_LIBRARY_NAMES mariadbcpp mariadbcpp-static)
elseif(APPLE OR UNIX)
    set(MARIADB_CONNECTOR_CPP_LIBRARY_NAMES mariadbcpp mariadbcpp_static libmariadbcpp.a)
endif()

find_library(MARIADB_CONNECTOR_CPP_LIB NAMES ${MARIADB_CONNECTOR_CPP_LIBRARY_NAMES} HINTS ${MARIADB_CONNECTOR_CPP_LIB_DIRS})

if(MARIADB_CONNECTOR_CPP_LIB)
    message(STATUS "Found MariaDB Connector/C++ lib: ${MARIADB_CONNECTOR_CPP_LIB}")
else()
    message(FATAL_ERROR "MariaDB Connector/C++ lib not found")
endif()

if(NOT WIN32)
    find_package(OpenSSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

add_subdirectory(lib)
add_subdirectory(src)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

install(TARGETS ${CMAKE_PROJECT_NAME})
