// Copyright 2021 Kuznetsov Konstantin

#include <iostream>

#include <CLI11/CLI11.hpp>

#include "db/db_manager.h"
#include "cli/subcommand_show.h"

int main(int argc, char *argv[]) {
    CLI::App app{"fundex - CLI expense tracker"};
    fundex::setup_option_p(&app);
    CLI11_PARSE(app, argc, argv);
    return 0;
}
