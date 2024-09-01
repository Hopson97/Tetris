#include "Application.h"

#include "Constants.h"
#include "Util/Keyboard.h"

Application::Application()
    : board_(BOARD_WIDTH, BOARD_HEIGHT)
{
    srand(std::time(nullptr));
    board_.fill(0);
    sprite_.setOutlineColor(sf::Color::White);
    sprite_.setOutlineThickness(1);

    active_block_.reset(ALL_BLOCKS[rand() % ALL_BLOCKS.size()]);
    next_preview_.reset(ALL_BLOCKS[rand() % ALL_BLOCKS.size()]);

    font_.loadFromFile("assets/Amity_Jack.ttf");
    text_.setFont(font_);
}

void Application::on_event(const sf::RenderWindow& window, const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::KeyReleased:
            switch (e.key.code)
            {
                case sf::Keyboard::W:
                {
                    auto new_block = active_block_.rotate();
                    if (block_can_move(new_block, {0, 0}))
                    {
                        active_block_ = new_block;
                    }
                }
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
        if (block_can_move(active_block_, {-1, 0}))
        {
            active_block_.location.x--;
            input_delay_.restart();
        }
    }
    else if ((keyboard.is_key_down(sf::Keyboard::D) || keyboard.is_key_down(sf::Keyboard::Right)) &&
             delay_ok)
    {
        if (block_can_move(active_block_, {1, 0}))
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
        if (!block_can_move(active_block_, {0, 1}))
        {
            active_block_.for_each(
                [&](int32_t square, const sf::Vector2i& location)
                {
                    if (square > 0)
                    {
                        board_.set(location.x, location.y, square);
                    }
                });

            // Check columns for a clearance
            for (int y = 0; y < BOARD_HEIGHT; y++)
            {
                bool clear = true;
                for (int x = 0; x < BOARD_WIDTH; x++)
                {
                    if (!board_.get(x, y))
                    {
                        clear = false;
                        break;
                    }
                }

                // Propagate upwards, moving all blocks down
                if (clear)
                {
                    for (int clear_y = y; clear_y > 0; clear_y--)
                    {
                        for (int x = 0; x < BOARD_WIDTH; x++)
                        {
                            board_.set(x, clear_y, board_.get(x, clear_y - 1));
                        }
                    }
                }
            }

            // Reset the active block
            active_block_ = next_preview_;
            next_preview_.reset(ALL_BLOCKS[rand() % ALL_BLOCKS.size()]);
        }
        else
        {
            active_block_.location.y++;
        }
        block_move_timer_.restart();
    }
}

void Application::on_render(sf::RenderWindow& window)
{
    // Render the board outline
    sprite_.setFillColor(sf::Color::Black);
    sprite_.setPosition(BOARD_X, BOARD_Y);
    sprite_.setSize({SQUARE_SIZE * BOARD_WIDTH, SQUARE_SIZE * BOARD_HEIGHT});
    window.draw(sprite_);

    // Render the preview outline and text
    sprite_.setPosition({PREVIEW_BOARD_X, PREVIEW_BOARD_Y});
    sprite_.setSize({SQUARE_SIZE * 6, SQUARE_SIZE * 6});
    window.draw(sprite_);

    // The text
    text_.setString("Next Block");
    text_.setPosition({PREVIEW_BOARD_X + SQUARE_SIZE * 3 - text_.getLocalBounds().getSize().x / 2, PREVIEW_BOARD_Y});
    window.draw(text_);

    // Render the board itself
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
        
    // Render the block being currently moved and the next block preview
    active_block_.draw(window, sprite_, {BOARD_X, BOARD_Y});
    next_preview_.draw(window, sprite_,
                       {PREVIEW_BOARD_X + SQUARE_SIZE, PREVIEW_BOARD_Y + SQUARE_SIZE * 2});
}

bool Application::block_can_move(const ActiveBlock& block, const sf::Vector2i& offset)
{
    bool can_move = true;

    block.for_each(
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
