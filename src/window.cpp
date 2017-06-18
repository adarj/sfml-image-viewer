/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "window.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <exception>
#include <future>
#include <iterator>
#include <utility>

struct path_leaf_string {
    std::string operator()(const boost::filesystem::directory_entry& entry) const
    {
        return entry.path().leaf().string();
    }
};

Window::Window(const std::string&& filename)
{
    this->isFullscreen = false;
    this->filename = filename;

    // Run a seperate thread to get a list of all files in the directory
    auto f = std::async(std::launch::async, &Window::getFilesInDirectory, this);

    load();
    init();

    files = f.get();

    draw();
}

void Window::load()
{
    sf::Image image;
    if (!image.loadFromFile(filename)) {
        throw std::runtime_error("Error: Image not found");
    }

    texture.loadFromImage(image);
    texture.setSmooth(true);
    texture.update(image);

    sprite.setTexture(texture);
}

void Window::init()
{
    desktop = sf::VideoMode::getDesktopMode();

    window.create(sf::VideoMode(640, 480), "SFML Image Viewer");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(framerate);

    // Initialize view
    view.reset(sf::FloatRect(
        0.0f,
        0.0f,
        static_cast<float>(texture.getSize().x),
        static_cast<float>(texture.getSize().y)));
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
            if (event.key.code == sf::Keyboard::F) {
                if (!isFullscreen) {
                    window.create(desktop, "SFML Image Viewer", sf::Style::Fullscreen);
                } else {
                    window.create(sf::VideoMode(640, 480), "SFML Image Viewer");
                }
                isFullscreen = !isFullscreen;
            }
            if ((event.key.code == sf::Keyboard::P) || (event.key.code == sf::Keyboard::N)) {
                auto it = find(files.begin(), files.end(), filename);
                if (it != files.end()) {
                    // Get position of current image
                    auto pos = std::distance(files.begin(), it);
                    auto size = static_cast<int>(files.size());
                    auto original = files.at(pos);

                    if ((event.key.code == sf::Keyboard::P) && (pos > 0)) {
                        filename = files.at(pos - 1);
                    }

                    if ((event.key.code == sf::Keyboard::N) && (pos < (size - 1))) {
                        filename = files.at(pos + 1);
                    }

                    try {
                        texture = sf::Texture();
                        sprite = sf::Sprite();
                        load();
                        view.reset(sf::FloatRect(
                            0,
                            0,
                            static_cast<float>(texture.getSize().x),
                            static_cast<float>(texture.getSize().y)));
                        getLetterboxView();
                    } catch (std::exception& e) {
                        files.erase(std::remove(files.begin(), files.end(), filename), files.end());
                        filename = original;
                        load();
                    }
                }
            }

        default:
            break;
        }
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
        pos.x = (1.0f - size.x) / 2.0f;
        size.y = 1.0f;
        pos.y = 0.0f;
    } else {
        size.y = windowRatio / viewRatio;
        pos.y = (1.0f - size.y) / 2.0f;
        size.x = 1.0f;
        pos.x = 0.0f;
    }

    view.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
}

std::vector<std::string> Window::getFilesInDirectory()
{
    std::vector<std::string> v;
    auto dir = boost::filesystem::current_path();

    boost::filesystem::path p(dir);
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(v), path_leaf_string());
    std::sort(v.begin(), v.end());

    return v;
}
