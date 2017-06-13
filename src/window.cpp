/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "window.h"
#include <iostream>

void Window::create()
{
    this->filename = "";

    init();
    draw();
}

void Window::create(std::string filename)
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
    sprite.setTexture(texture);
}

void Window::init()
{
    window.create(sf::VideoMode(640, 480), "SFML Image Viewer");

    // Scale view to the size of the image
    view.reset(sf::FloatRect(
        0,
        0,
        static_cast<float>(texture.getSize().x),
        static_cast<float>(texture.getSize().y)));
}

void Window::draw()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.setView(view);
        window.draw(sprite);
        window.display();
    }
}
