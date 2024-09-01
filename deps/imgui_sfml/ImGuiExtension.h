#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>

// Adds helpers for ImGUI
namespace ImGui
{
    void TextSFMLVector2(const std::string& label, const sf::Vector2f& vector);
    void TextSFMLVector2(const std::string& label, const sf::Vector2i& vector);
}