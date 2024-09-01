#pragma once

#pragma once

#include <filesystem>
#include <ostream>
#include <string_view>
#include <vector>

#include <SFML/System/Vector2.hpp>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector)
{
    stream << '(' << vector.x << ", " << vector.y << ')';
    return stream;
}

std::string read_file_to_string(const std::filesystem::path& file_path);
std::vector<std::string> split_string(const std::string& string, char delim = ' ');