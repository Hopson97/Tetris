#include <cassert>
#include <vector>

#include <SFML/Graphics/Color.hpp>

struct Block
{
    int size;
    std::vector<int32_t> layout;

    int32_t get(int x, int y)
    {
        assert(x >= 0 && x < size && y >= 0 && y < size);
        return layout[(y * size + x)];
    }
};

const Block BLOCK_NONE{0, {}};

// clang-format off
const Block BLOCK_SQUARE  {
    2, 
    {
        1, 1, 
        1, 1
    }
};

const Block BLOCK_I  {
    4, 
    {
        2, 0, 0, 0, 
        2, 0, 0, 0,
        2, 0, 0, 0,
        2, 0, 0, 0,
    }
};

const Block BLOCK_T  {
    3, 
    {
        3, 3, 3,
        0, 3, 0,
        0, 0, 0,
    }
};
// clang-format on

const std::vector<sf::Color> BLOCK_COLOURS = {
    sf::Color::Yellow,
    sf::Color::Green,
    sf::Color::Blue,
};

#include <iostream>

inline sf::Color get_block_colour(int square)
{
    square--;
    if ((square < 0) || (square >= BLOCK_COLOURS.size()))
    {
        return sf::Color::Magenta;
    }

    return BLOCK_COLOURS[square];
}

// clang-format on
const std::vector<Block> ALL_BLOCKS{BLOCK_SQUARE, BLOCK_I, BLOCK_T};