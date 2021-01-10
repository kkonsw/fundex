// Copyright 2021 Kuznetsov Konstantin

#include <iostream>
#include <memory>

#include "cli/subcommand_show.h"

namespace fundex {

void setup_subcommand_show(CLI::App *app) {
    auto opt = std::make_shared<SubcommandShowOptions>();
    app->add_option("-n", opt->num_records, "Number of records to show");
    app->callback([opt]() { run_subcommand_show(*opt); });
}

void run_subcommand_show(const SubcommandShowOptions& opt) {
    std::cout << "Number of records to show: " << opt.num_records << std::endl;
}

};  // namespace fundex
