
add_library(
    imgui_sfml
    imgui-SFML.cpp
    ImGuiExtension.cpp
)

target_link_libraries(imgui_sfml PRIVATE
    sfml-system sfml-graphics sfml-window
    imgui::imgui
)