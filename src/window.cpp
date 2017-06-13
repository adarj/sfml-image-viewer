/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "window.h"

void Window::create()
{
    init();
    draw();
}

void Window::init()
{
    window.create(sf::VideoMode(640, 480), "SFML Image Viewer");
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
        window.display();
    }
}
