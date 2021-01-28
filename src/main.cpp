// Copyright 2021 Kuznetsov Konstantin

#include <CLI11/CLI11.hpp>

#include "cli/utilities.h"

int main(int argc, char *argv[]) {
    CLI::App app{"fundex - CLI expense tracker"};
    fundex::setup_all_options(&app);
    try {
        CLI11_PARSE(app, argc, argv);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
