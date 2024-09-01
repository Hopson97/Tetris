#include "Application.h"

#include "Util/Keyboard.h"

Application::Application()
{
    sprite_.setSize({64.0f, 64.0f});
}

void Application::on_event(const sf::RenderWindow& window, const sf::Event& e)
{
}

void Application::on_update(const Keyboard& keyboard, sf::Time dt)
{
    constexpr static float SPEED = 100.0f;
    sf::Vector2f move;
    if (keyboard.is_key_down(sf::Keyboard::W))
    {
        move.y -= SPEED;
    }
    else if (keyboard.is_key_down(sf::Keyboard::S))
    {
        move.y += SPEED;
    }
    if (keyboard.is_key_down(sf::Keyboard::A))
    {
        move.x -= SPEED;
    }
    else if (keyboard.is_key_down(sf::Keyboard::D))
    {
        move.x += SPEED;
    }
    move *= dt.asSeconds();
    sprite_.move(move);
}

void Application::on_fixed_update(sf::Time dt)
{
}

void Application::on_render(sf::RenderWindow& window)
{
    window.draw(sprite_);
}
