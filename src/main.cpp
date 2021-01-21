// Copyright 2021 Kuznetsov Konstantin

#include <CLI11/CLI11.hpp>

#include "cli/utilities.h"

int main(int argc, char *argv[]) {
    CLI::App app{"fundex - CLI expense tracker"};
    fundex::setup_all_options(&app);
    CLI11_PARSE(app, argc, argv);
    return 0;
}
