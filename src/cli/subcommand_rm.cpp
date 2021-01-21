// Copyright 2021 Kuznetsov Konstantin

#include <memory>

#include "cli/subcommand_rm.h"
#include "db/transaction_table.h"

namespace fundex {

/**
 * Function that runs code after Rm (Remove) subcommand is issued.
 *
 */
static void run_subcommand_rm(const SubcommandRmOptions& opt) {
    if (opt.remove_all) {
        TransactionTable().remove_all();
    }
}

void setup_subcommand_rm(CLI::App *app) {
    auto opt = std::make_shared<SubcommandRmOptions>();
    auto sub = app->add_subcommand("rm", "Remove Transactions");
    sub->add_flag("--all", opt->remove_all, "Remove all Transactions");
    sub->callback([opt]() { run_subcommand_rm(*opt); });
}

};  // namespace fundex
