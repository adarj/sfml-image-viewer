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
    Window(const std::string&& filename);

private:
    void load();
    void init();
    void draw();

    void checkEvents();
    void getLetterboxView();

    sf::RenderWindow window;
    sf::View view;
    sf::VideoMode videoMode;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string filename;
    bool isFullscreen;
};

#endif
