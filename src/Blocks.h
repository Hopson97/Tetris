#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

struct Block
{
    int size;
    std::vector<int32_t> layout;

    int32_t get(int x, int y) const;
};

// Empty default block
const Block BLOCK_NONE{0, {}};


/// Represents a block with a given position on the board
struct ActiveBlock
{
    sf::Vector2i location;
    Block block = BLOCK_NONE;

    ActiveBlock rotate();
    void reset(Block new_block);

    template <typename F>
    void for_each(F callback) const
    {
        for (int y = 0; y < block.size; y++)
        {
            for (int x = 0; x < block.size; x++)
            {
                auto tile = block.get(x, y);
                auto board_x = x + location.x;
                auto board_y = y + location.y;
                callback(tile, sf::Vector2i{board_x, board_y});
            }
        }
    }

    void draw(sf::RenderTarget& renderer, sf::RectangleShape& sprite, const sf::Vector2f& board_offset);
};


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

const std::vector<Block> ALL_BLOCKS{BLOCK_SQUARE, BLOCK_I, BLOCK_T, BLOCK_S,
                                    BLOCK_Z,      BLOCK_J, BLOCK_L, BLOCK_O};

sf::Color get_block_colour(int square);
