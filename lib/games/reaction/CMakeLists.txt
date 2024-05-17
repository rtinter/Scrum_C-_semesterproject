set(LIBRARY_NAME reaction)

file(GLOB SOURCES *.cpp)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC .)

set(CUSTOM_LIBS
        commons
        ui_elements
        abstract_game
)

target_link_libraries(${LIBRARY_NAME} PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML box2d ${CUSTOM_LIBS})
