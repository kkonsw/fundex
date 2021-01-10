// Copyright 2021 Kuznetsov Konstantin
/**
 * @file subcommand_show.h
 */
#ifndef SRC_CLI_SUBCOMMAND_SHOW_H_
#define SRC_CLI_SUBCOMMAND_SHOW_H_

#include <CLI11/CLI11.hpp>

namespace fundex {

struct Options {
    int p;
};

void setup_option_p(CLI::App *app);
void callback(const Options& opt);

};  // namespace fundex

#endif  // SRC_CLI_SUBCOMMAND_SHOW_H_
