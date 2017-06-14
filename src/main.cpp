/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "window.h"
#include <iostream>
#include <string>

int main(int argc, char const* argv[])
{
    Window window;

    if (argc > 1) {
        std::string filename = argv[1];
        window.create(filename);
    } else {
        std::cout << "SFML Image Viewer (c) 2017" << std::endl;
        std::cout << std::endl;
        std::cout << "Usage: sfiv FILE" << std::endl;
    }

    return 0;
}
