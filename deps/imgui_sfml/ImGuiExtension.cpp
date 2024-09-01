#include "ImGuiExtension.h"

#include <imgui.h>

namespace ImGui
{
    void TextSFMLVector2(const std::string& label, const sf::Vector2f& vector)
    {
        ImGui::Text("%s: (%.3f, %.3f)", label.c_str(), vector.x, vector.y);
    }

    void TextSFMLVector2(const std::string& label, const sf::Vector2i& vector)
    {
        ImGui::Text("%s: (%d, %d)", label.c_str(), vector.x, vector.y);
    }
} // namespace ImGui