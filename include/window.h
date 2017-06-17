/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>

class Window {
public:
    Window(const std::string&& filename);

private:
    void load();
    void init();
    void draw();

    void checkEvents();
    void getLetterboxView();
    std::vector<std::string> getFilesInDirectory();

    sf::RenderWindow window;
    sf::View view;
    sf::VideoMode desktop;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string filename;
    bool isFullscreen;

    std::vector<std::string> files;

    static const int framerate = 60;
};

#endif
