// Copyright 2021 Kuznetsov Konstantin

#include <iostream>

#include <CLI11/CLI11.hpp>

#include "cli/flags.h"
#include "cli/subcommand_add.h"
#include "cli/subcommand_show.h"

int main(int argc, char *argv[]) {
    CLI::App app{"fundex - CLI expense tracker"};
    fundex::setup_flags(&app);
    fundex::setup_subcommand_add(&app);
    fundex::setup_subcommand_show(&app);
    CLI11_PARSE(app, argc, argv);
    return 0;
}
