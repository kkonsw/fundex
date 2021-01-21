// Copyright 2021 Kuznetsov Konstantin

/**
 * @file flags.h
 * This file defines flags for CLI app.
 *
 * Flags can be passed to program to get specific results.
 * For example, `--list-cat` will output all possible expense categories.
 */

#ifndef SRC_CLI_FLAGS_H_
#define SRC_CLI_FLAGS_H_

#include <CLI11/CLI11.hpp>

#include "db/database.h"

namespace fundex {

/**
 * Adds flags to program.
 *
 * If flags are found, callback functions are called.
 */
void setup_flags(CLI::App *app);

};  // namespace fundex

#endif  // SRC_CLI_FLAGS_H_
