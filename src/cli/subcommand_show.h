// Copyright 2021 Kuznetsov Konstantin

/**
 * @file subcommand_show.h
 * This file defines options and actions for subcommand Show.
 */

#ifndef SRC_CLI_SUBCOMMAND_SHOW_H_
#define SRC_CLI_SUBCOMMAND_SHOW_H_

#include <CLI11/CLI11.hpp>

namespace fundex {

/** All options for subcommand Show.
  *
  */
struct SubcommandShowOptions {
    /// Number of records to show
    int num_records;
};

/** Sets up a subcommand and captures a shared_ptr to a struct
  * that holds all its options. The variables of the struct are
  * bound to the CLI options. Also sets the run function as callback
  * to be called when this subcommand is issued.
  */
void setup_subcommand_show(CLI::App *app);

};  // namespace fundex

#endif  // SRC_CLI_SUBCOMMAND_SHOW_H_
