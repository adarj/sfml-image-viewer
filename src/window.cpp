/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "window.h"
#include <iostream>

Window::Window(std::string filename)
{
    this->filename = filename;

    load();
    init();
    draw();
}

void Window::load()
{
    if (!texture.loadFromFile(filename)) {
        std::cout << "Error: file does not exist" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

void Window::init()
{
    window.create(sf::VideoMode(640, 480), "SFML Image Viewer");
    window.setKeyRepeatEnabled(false);

    // Initialize view
    view.reset(sf::FloatRect(
        0,
        0,
        static_cast<float>(texture.getSize().x),
        static_cast<float>(texture.getSize().y)));
}

void Window::checkEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::EventType::Closed:
            window.close();
            break;

        case sf::Event::EventType::Resized:
            getLetterboxView();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Q) {
                window.close();
            }

        default:
            break;
        }
    }
}

void Window::draw()
{
    while (window.isOpen()) {
        checkEvents();

        window.clear();
        window.setView(view);
        window.draw(sprite);
        window.display();
    }
}

void Window::getLetterboxView()
{
    float windowRatio = window.getSize().x / static_cast<float>(window.getSize().y);
    float viewRatio = view.getSize().x / static_cast<float>(view.getSize().y);

    sf::Vector2f size;
    sf::Vector2f pos;

    if (windowRatio > viewRatio) {
        size.x = viewRatio / windowRatio;
        pos.x = (1 - size.x) / 2.f;
        size.y = 1;
        pos.y = 0;
    } else {
        size.y = windowRatio / viewRatio;
        pos.y = (1 - size.y) / 2.f;
        size.x = 1;
        pos.x = 0;
    }

    view.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
}
