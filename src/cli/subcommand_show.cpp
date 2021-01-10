// Copyright 2021 Kuznetsov Konstantin

#include <iostream>
#include <memory>

#include "cli/subcommand_show.h"

namespace fundex {

void setup_option_p(CLI::App *app) {
    auto opt = std::make_shared<Options>();
    app->add_option("-p", opt->p, "Parameter");
    app->callback([opt]() { callback(*opt); });
}

void callback(const Options& opt) {
    std::cout << "Parameter value: " << opt.p << std::endl;
}

};  // namespace fundex
