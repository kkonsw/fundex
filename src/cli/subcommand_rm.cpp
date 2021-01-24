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
        return;
    }

    // Remove Transactions with selected ids
    TransactionTable transactions;
    for (const auto& id : opt.ids) {
        transactions.remove(id);
    }
}

void setup_subcommand_rm(CLI::App *app) {
    auto opt = std::make_shared<SubcommandRmOptions>();
    auto sub = app->add_subcommand("rm", "Remove Transactions");
    auto remove_all = sub->add_flag("--all", opt->remove_all,
            "Remove all Transactions");
    sub->add_option("ids", opt->ids,
            "Remove Transactions with passed ids")->excludes(remove_all);
    sub->callback([opt]() { run_subcommand_rm(*opt); });
}

};  // namespace fundex
