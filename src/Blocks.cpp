#include "Blocks.h"

#include <cassert>

#include "Constants.h"

int32_t Block::get(int x, int y) const
{
    assert(x >= 0 && x < size && y >= 0 && y < size);
    return layout[(y * size + x)];
}

ActiveBlock ActiveBlock::rotate()
{
    ActiveBlock b = *this;

    // From https://stackoverflow.com/a/22858585
    int size = block.size;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            b.block.layout[(size - 1 - i) + j * size] = block.layout[i * size + j];

    return b;
}

void ActiveBlock::reset(Block new_block)
{
    block = new_block;
    block = new_block;
    location = {0, 0};
}

void ActiveBlock::draw(sf::RenderTarget& renderer, sf::RectangleShape& sprite,
                       const sf::Vector2f& board_offset)
{
    for_each(
        [&](int32_t square, const sf::Vector2i& location)
        {
            if (square > 0)
            {
                sprite.setFillColor(get_block_colour(square));
                sprite.setPosition(location.x * SQUARE_SIZE + board_offset.x,
                                   location.y * SQUARE_SIZE + board_offset.y);
                renderer.draw(sprite);
            }
        });
}

sf::Color get_block_colour(int square)
{
    square -= 1;

    if ((square < 0) || (square >= BLOCK_COLOURS.size()))
    {
        return sf::Color::Magenta;
    }

    return BLOCK_COLOURS[square];
}
