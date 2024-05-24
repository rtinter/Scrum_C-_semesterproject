file(GLOB SOURCES *.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES}
        SceneManager.cpp
        SceneManager.hpp)

set(GAME_LIBS
        calc
        reaction
        test
)

set(CUSTOM_LIBS
        commons
        ui_elements
        abstract_game
        views
        scene
        ${GAME_LIBS}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        sfml-graphics ImGui-SFML::ImGui-SFML box2d views scene abstract_game commons ui_elements scene
        ${CUSTOM_LIBS}
)


if (WIN32)
    add_custom_command(
            TARGET ${CMAKE_PROJECT_NAME}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Athena>
            VERBATIM)
endif ()
