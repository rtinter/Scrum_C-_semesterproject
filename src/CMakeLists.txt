file(GLOB SOURCES *.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

set(GAME_LIBS
        calc
        reaction
)

set(CUSTOM_LIBS
        commons
        ui_elements
        abstract_game
        views
        ${GAME_LIBS}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        sfml-graphics ImGui-SFML::ImGui-SFML box2d
        ${CUSTOM_LIBS}
)
