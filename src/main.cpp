/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "window.h"
#include <string>

int main(int argc, char const* argv[])
{
    Window window;

    if (argc > 1) {
        std::string filename = argv[1];
        window.create(filename);
    } else {
        window.create();
    }

    return 0;
}
