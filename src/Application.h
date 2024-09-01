#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Blocks.h"
#include "Util/Array2D.h"

class Keyboard;

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
    ActiveBlock next_preview_;

    sf::RectangleShape sprite_;

    sf::Clock block_move_timer_;
    sf::Clock input_delay_;

    sf::Font font_;
    sf::Text text_;
};