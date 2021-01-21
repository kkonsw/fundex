// Copyright 2021 Kuznetsov Konstantin

/**
 * @file utilities.h
 * This file contains utility functions.
 */

#ifndef SRC_CLI_UTILITIES_H_
#define SRC_CLI_UTILITIES_H_

#include <CLI11/CLI11.hpp>

namespace fundex {

/**
 * Sets up all options for CLI App.
 *
 */
void setup_all_options(CLI::App *app);

};  // namespace fundex

#endif  // SRC_CLI_UTILITIES_H_
