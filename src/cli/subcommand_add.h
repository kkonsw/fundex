// Copyright 2021 Kuznetsov Konstantin

/**
 * @file subcommand_add.h
 * This file defines options and actions for subcommand Add.
 */

#ifndef SRC_CLI_SUBCOMMAND_ADD_H_
#define SRC_CLI_SUBCOMMAND_ADD_H_

#include <string>

#include <CLI11/CLI11.hpp>

namespace fundex {

/**
 * All options for subcommand Add.
 */
struct SubcommandAddOptions {
    /**
     * Category's id.
     */
    int cat_id;

    /**
     * Transaction's amount.
     */
    int amount;

    /**
     * Note about Transaction.
     */
    std::string note;

    /**
     * Date of Transaction.
     * Current supported format is %d/%m/%Y (day/month/year).
     */
    std::string date;
};

/**
 * Sets up a subcommand and captures a shared_ptr to a struct
 * that holds all its options. The variables of the struct are
 * bound to the CLI options. Also sets the run function as callback
 * to be called when this subcommand is issued.
 */
void setup_subcommand_add(CLI::App *app);

};  // namespace fundex

#endif  // SRC_CLI_SUBCOMMAND_ADD_H_
