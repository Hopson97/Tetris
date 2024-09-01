#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Blocks.h"
#include "Util/Array2D.h"

class Keyboard;

constexpr float SQUARE_SIZE = 32;
constexpr auto BOARD_WIDTH = 20;
constexpr auto BOARD_HEIGHT = 25;
constexpr auto BOARD_X = 800 - (BOARD_WIDTH * SQUARE_SIZE / 2);
constexpr auto BOARD_Y = 450 - (BOARD_HEIGHT * SQUARE_SIZE / 2);

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
};

class Application
{
  public:
    Application();

    void on_event(const sf::RenderWindow& window, const sf::Event& e);
    void on_update(const Keyboard& keyboard, sf::Time dt);
    void on_fixed_update(sf::Time dt);
    void on_render(sf::RenderWindow& window);

  private:
    bool block_can_move(const ActiveBlock& block, const sf::Vector2i& offset);
    Array2D<int32_t> board_;

    ActiveBlock active_block_;

    sf::RectangleShape sprite_;

    sf::Clock block_move_timer_;
    sf::Clock input_delay_;
};