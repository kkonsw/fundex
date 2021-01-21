// Copyright 2021 Kuznetsov Konstantin

#include "cli/utilities.h"
#include "cli/subcommand_add.h"
#include "cli/subcommand_show.h"
#include "cli/subcommand_rm.h"
#include "cli/flags.h"

namespace fundex {

void setup_all_options(CLI::App *app) {
    setup_flags(app);
    setup_subcommand_show(app);
    setup_subcommand_add(app);
    setup_subcommand_rm(app);
}

};  // namespace fundex
