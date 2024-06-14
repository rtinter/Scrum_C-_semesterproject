set(LIBRARY_NAME commons)

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
        ImGui-SFML::ImGui-SFML
        sfml-graphics
        sfml-audio
        box2d
)


file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/sounds/*")

foreach (FILE ${SOURCE_FILES})
    file(COPY ${FILE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sounds)
endforeach()