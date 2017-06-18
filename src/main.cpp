/*
 * Copyright (c) 2017 Akil Darjean (adarjean@uh.edu)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "window.h"
#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <utility>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{

    try {
        po::options_description desc("Arguments");
        desc.add_options()("help,h", "Print this help message and exit")("input", po::value<std::string>(), "Image to display");

        po::positional_options_description p;
        p.add("input", -1);

        po::variables_map args;
        po::store(
            po::command_line_parser(argc, argv).options(desc).positional(p).run(),
            args);
        po::notify(args);

        if (argc == 1) {
            std::cout << "SFML Image Viewer (C) 2017" << std::endl;
            std::cout << std::endl;
        }
        if ((args.count("help")) || (argc == 1)) {
            std::cout << "Usage:   sfiv [options] filename" << std::endl;
            std::cout << std::endl;
            std::cout << desc << std::endl;
            return 0;
        }
        if (args.count("input")) {
            std::string file = args["input"].as<std::string>();
            Window window(std::move(file));
        }

    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
