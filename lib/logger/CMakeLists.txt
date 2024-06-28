set(LIBRARY_NAME logger)

file(GLOB SOURCES *.cpp)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIBRARY_NAME} PUBLIC
)
