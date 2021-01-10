// Copyright 2021 Kuznetsov Konstantin

#include <iostream>

#include "CLI11.hpp"

#include "db/db_manager.h"

int main(int argc, char *argv[]) {
    CLI::App app{"fundex - CLI expense tracker"};

    // define options
    int p = 0;
    app.add_option("-p", p, "Parameter");

    CLI11_PARSE(app, argc, argv);

    std::cout << "Parameter value: " << p << std::endl;
    return 0;
}
