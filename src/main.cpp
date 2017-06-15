/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "cxxopts.hpp"
#include "window.h"
#include <exception>
#include <iostream>
#include <string>
#include <utility>

int main(int argc, char* argv[])
{
    try {
        cxxopts::Options options("SFML Image Viewer", "One line description of MyProgram");
        options.add_options()("f,file", "File", cxxopts::value<std::string>());

        options.parse_positional("file");
        options.parse(argc, argv);

        if (options.count("file")) {
            Window window(std::move(options["file"].as<std::string>()));
            std::cout << std::endl;
        }

    } catch (const cxxopts::OptionException& e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
