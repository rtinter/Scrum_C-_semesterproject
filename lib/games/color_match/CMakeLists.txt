set(LIBRARY_NAME color_match)

file(GLOB SOURCES *.cpp)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${IMGUI_DIR}
        ${SFML_INCLUDE_DIRS}
        ${ImGui-SFML_INCLUDE_DIRS}
)

set(CUSTOM_LIBS

)

target_link_libraries(${LIBRARY_NAME} PUBLIC
        ${CUSTOM_LIBS}
        abstract_game
        commons
        ui_elements
        ImGui-SFML::ImGui-SFML
        sfml-graphics
        box2d
)
