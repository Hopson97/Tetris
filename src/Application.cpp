#include "Application.h"
#include "Util/Keyboard.h"
#include "Util/Util.h"
#include <iostream>

Application::Application()
    : board_(BOARD_WIDTH, BOARD_HEIGHT)
{
    board_.fill(0);
    sprite_.setOutlineColor(sf::Color::White);
    sprite_.setOutlineThickness(1);

    active_block_.reset(BLOCK_I);
}

void Application::on_event(const sf::RenderWindow& window, const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::KeyReleased:
            switch (e.key.code)
            {
                case sf::Keyboard::W:
                    // rotate
                    break;

                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    if (active_block_.location.x > 0)
                    {
                        active_block_.location.x--;
                    }
                    break;

                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    if (active_block_.location.x <  BOARD_WIDTH-1)
                    {
                        active_block_.location.x++;
                    }
                    break;
            }
    }
}

void Application::on_update(const Keyboard& keyboard, sf::Time dt)
{
    if (block_move_timer_.getElapsedTime() > sf::seconds(0.2f))
    {
        active_block_.location.y++;
        block_move_timer_.restart();

        // Check for board collision
        bool reset_block = false;
        active_block_.for_each(
            [&](int32_t square, const sf::Vector2i& location)
            {
                if (reset_block)
                    return;

                if (square > 0 && location.y == BOARD_HEIGHT - 1)
                {
                    active_block_.for_each(
                        [&](int32_t square, const sf::Vector2i& location)
                        {
                            if (square > 0)
                            {
                                board_.set(location.x, location.y, square);
                                std::cout << "Setting " << location << " to " << (int)square
                                          << '\n';
                            }
                        });
                    reset_block = true;
                }
            });

        if (reset_block)
        {
            std::cout << "Reset the block...\n";
            active_block_.reset(BLOCK_SQUARE);
        }
    }
}

void Application::on_fixed_update(sf::Time dt)
{
}

void Application::on_render(sf::RenderWindow& window)
{
    sprite_.setFillColor(sf::Color::Black);
    sprite_.setPosition(BOARD_X, BOARD_Y);
    sprite_.setSize({SQUARE_SIZE * BOARD_WIDTH, SQUARE_SIZE * BOARD_HEIGHT});
    window.draw(sprite_);

    sprite_.setSize({SQUARE_SIZE, SQUARE_SIZE});
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (board_.get(x, y) > 0)
            {
                sprite_.setPosition(x * SQUARE_SIZE + BOARD_X, y * SQUARE_SIZE + BOARD_Y);
                sprite_.setFillColor(sf::Color::Red);
                window.draw(sprite_);
            }
        }
    }

    // Draw the blocc
    active_block_.for_each(
        [&](int32_t square, const sf::Vector2i& location)
        {
            if (square > 0)
            {
                sprite_.setPosition(location.x * SQUARE_SIZE + BOARD_X,
                                    location.y * SQUARE_SIZE + BOARD_Y);
                sprite_.setFillColor(sf::Color::Red);
                window.draw(sprite_);
            }
        });
}
