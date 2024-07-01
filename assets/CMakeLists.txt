# source directory for the assets
set(ASSETS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# destination directory for the assets within the bin directory
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR}/bin/assets)

# List all the directories in the assets folder
file(GLOB ASSET_DIRECTORIES RELATIVE ${ASSETS_SOURCE_DIR} ${ASSETS_SOURCE_DIR}/*)

# Create a custom target for copying the assets
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSETS_DEST_DIR}
)

# Loop through each directory and add a custom command to copy it to the destination
foreach(DIR ${ASSET_DIRECTORIES})
    if(IS_DIRECTORY ${ASSETS_SOURCE_DIR}/${DIR})
        add_custom_command(TARGET copy_assets POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${ASSETS_SOURCE_DIR}/${DIR} ${ASSETS_DEST_DIR}/${DIR}
                COMMENT "Copying asset directory: ${DIR} to ${ASSETS_DEST_DIR}/${DIR}"
        )
    endif()
endforeach()

# Add a dependency to ensure assets are copied before the Athena target is built
add_dependencies(Athena copy_assets)
