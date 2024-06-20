set(LIBRARY_NAME memory)

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

# Copy images to the build directory
file(GLOB IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/images/*")

foreach (FILE ${IMAGE_FILES})
    file(COPY ${FILE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/images)
endforeach()
