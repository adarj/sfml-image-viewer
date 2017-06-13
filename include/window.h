/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
    void create();
    void create(std::string filename);

private:
    void load();
    void init();
    void draw();

    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string filename;
};

#endif
