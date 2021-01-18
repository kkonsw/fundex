// Copyright 2021 Kuznetsov Konstantin
/**
 * @file subcommand_add.h
 * This file defines options and actions for subcommand Add.
 */
#ifndef SRC_CLI_SUBCOMMAND_ADD_H_
#define SRC_CLI_SUBCOMMAND_ADD_H_

#include <CLI11/CLI11.hpp>
#include "db/database.h"

namespace fundex {

/** All options for subcommand Add.
  *
  */
struct SubcommandAddOptions {
    /// Category id.
    int cat_id;

    /// Transaction amount.
    int amount;
};

/** Sets up a subcommand and captures a shared_ptr to a struct
  * that holds all its options. The variables of the struct are
  * bound to the CLI options. Also sets the run function as callback
  * to be called when this subcommand is issued.
  */
void setup_subcommand_add(CLI::App *app);

/** Function that runs code after Add subcommand is issued.
  * \param opt Subcommand Add options values.
  */
void run_subcommand_add(const SubcommandAddOptions& opt);

/** Creates new Transaction from subcommand Add options.
  * \param opt Subcommand Add options values.
  * \param transaction Pointer to new Transaction
  * \returns true, if new Transaction was created successfully,
  * false otherwise.
  */
static bool setup_new_transaction(const SubcommandAddOptions& opt,
        Transaction *transaction);

};  // namespace fundex

#endif  // SRC_CLI_SUBCOMMAND_ADD_H_
