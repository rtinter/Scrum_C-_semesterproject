add_library(commons StyleManager.cpp)
target_link_libraries(commons PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML box2d)
