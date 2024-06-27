set(LIBRARY_NAME analogy)

file(GLOB SOURCES *.cpp)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${IMGUI_DIR}
        ${SFML_INCLUDE_DIRS}
        ${ImGui-SFML_INCLUDE_DIRS}
)

set(CUSTOM_LIBS
        abstract_game
        commons
        ui_elements
        scene
)

target_link_libraries(${LIBRARY_NAME} PUBLIC
        ${CUSTOM_LIBS}
        ImGui-SFML::ImGui-SFML
        sfml-graphics
        box2d
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/questionnaire.json ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config/games/questionnaire.json COPYONLY)
