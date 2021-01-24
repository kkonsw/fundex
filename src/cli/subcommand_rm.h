// Copyright 2021 Kuznetsov Konstantin

/**
 * @file subcommand_rm.h
 * This file defines options and actions for subcommand rm (Remove).
 */

#ifndef SRC_CLI_SUBCOMMAND_RM_H_
#define SRC_CLI_SUBCOMMAND_RM_H_

#include <vector>

#include <CLI11/CLI11.hpp>

namespace fundex {

/**
 * All options for subcommand Remove.
 */
struct SubcommandRmOptions {
    /**
     * Flag to remove all Transactions.
     */
    bool remove_all;

    /**
     * Structure to store ids for removed Transactions.
     */
    std::vector<int> ids;
};

/**
 * Sets up a subcommand and captures a shared_ptr to a struct
 * that holds all its options. The variables of the struct are
 * bound to the CLI options. Also sets the run function as callback
 * to be called when this subcommand is issued.
 */
void setup_subcommand_rm(CLI::App *app);

};  // namespace fundex

#endif  // SRC_CLI_SUBCOMMAND_RM_H_
