#include <cassert>
#include <vector>

#include <SFML/Graphics/Color.hpp>

struct Block
{
    int size;
    std::vector<int32_t> layout;

    int32_t get(int x, int y) const
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

const Block BLOCK_S  {
    3, 
    {
        0, 4, 4,
        4, 4, 0,
        0, 0, 0,
    }
};

const Block BLOCK_Z  {
    3, 
    {
        5, 5, 0,
        0, 5, 5,
        0, 0, 0,
    }
};


const Block BLOCK_J  {
    3, 
    {
        6, 0, 0,
        6, 6, 6,
        0, 0, 0,
    }
};

const Block BLOCK_L  {
    3, 
    {
        0, 0, 7,
        7, 7, 7,
        0, 0, 0,
    }
};

const Block BLOCK_O  {
    3, 
    {
        1, 2, 3,
        2, 0, 4,
        3, 4, 5,
    }
};
// clang-format on

const std::vector<sf::Color> BLOCK_COLOURS = {
    sf::Color::Yellow, sf::Color::Green, sf::Color::Blue,
    sf::Color::Cyan,   sf::Color::Red,   sf::Color::Black,
};

inline sf::Color get_block_colour(int square)
{
    square -= 1;

    if ((square < 0) || (square >= BLOCK_COLOURS.size()))
    {
        return sf::Color::Magenta;
    }

    return BLOCK_COLOURS[square];
}

const std::vector<Block> ALL_BLOCKS{BLOCK_SQUARE, BLOCK_I, BLOCK_T, BLOCK_S,
                                    BLOCK_Z,      BLOCK_J, BLOCK_L, BLOCK_O};