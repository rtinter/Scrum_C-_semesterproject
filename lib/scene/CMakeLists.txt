set(LIBRARY_NAME scene)

file(GLOB SOURCES *.cpp)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC .)

target_link_libraries(${LIBRARY_NAME} PRIVATE sfml-graphics sfml-window ImGui-SFML::ImGui-SFML box2d)
