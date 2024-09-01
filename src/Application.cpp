#include "Application.h"

#include <iostream>

#include "Util/Keyboard.h"
#include "Util/Util.h"

void ActiveBlock::reset(Block new_block)
{
    block = new_block;
    location = {0, 0};
}


Application::Application()
    : board_(BOARD_WIDTH, BOARD_HEIGHT)
{
    srand(std::time(nullptr));
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
            }
    }
}

void Application::on_update(const Keyboard& keyboard, sf::Time dt)
{
    // Handle left-right block move inputs
    auto delay_ok = input_delay_.getElapsedTime() > sf::seconds(0.1f);
    if ((keyboard.is_key_down(sf::Keyboard::A) || keyboard.is_key_down(sf::Keyboard::Left)) &&
        delay_ok)
    {
        if (active_block_can_move_to({-1, 0}))
        {
            active_block_.location.x--;
            input_delay_.restart();
        }
    }
    else if ((keyboard.is_key_down(sf::Keyboard::D) || keyboard.is_key_down(sf::Keyboard::Right)) &&
             delay_ok)
    {
        if (active_block_can_move_to({1, 0}))
        {
            active_block_.location.x++;
            input_delay_.restart();
        }
    }

    // Move faster if "down" pressed
    sf::Time move_down_delay = sf::seconds(0.4f);
    if (keyboard.is_key_down(sf::Keyboard::S) || keyboard.is_key_down(sf::Keyboard::Down))
    {
        move_down_delay = sf::seconds(0.1f);
    }

    // Try to move the block down
    if (block_move_timer_.getElapsedTime() > move_down_delay)
    {
        if (!active_block_can_move_to({0, 1}))
        {
            active_block_.for_each(
                [&](int32_t square, const sf::Vector2i& location)
                {
                    if (square > 0)
                    {
                        board_.set(location.x, location.y, square);
                    }
                });
            active_block_.reset(ALL_BLOCKS[rand() % ALL_BLOCKS.size()]);
        }
        else
        {
            active_block_.location.y++;
        }
        block_move_timer_.restart();
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
            auto square = board_.get(x, y);
            if (square > 0)
            {
                sprite_.setFillColor(get_block_colour(square));
                sprite_.setPosition(x * SQUARE_SIZE + BOARD_X, y * SQUARE_SIZE + BOARD_Y);
                window.draw(sprite_);
            }
        }
    }

    // Draw the active block
    active_block_.for_each(
        [&](int32_t square, const sf::Vector2i& location)
        {
            if (square > 0)
            {
                sprite_.setFillColor(get_block_colour(square));
                sprite_.setPosition(location.x * SQUARE_SIZE + BOARD_X,
                                    location.y * SQUARE_SIZE + BOARD_Y);
                window.draw(sprite_);
            }
        });
}

bool Application::active_block_can_move_to(const sf::Vector2i& offset)
{
    bool can_move = true;

    active_block_.for_each(
        [&](int32_t square, const sf::Vector2i& location)
        {
            if (!can_move || !square)
            {
                return;
            }
            auto new_position = offset + location;

            // Check for out of bounds and already placed block collisions
            if (new_position.x >= BOARD_WIDTH || new_position.x < 0 ||
                new_position.y >= BOARD_HEIGHT || board_.get(new_position.x, new_position.y))
            {
                can_move = false;
                return;
            }
        });
    return can_move;
}
