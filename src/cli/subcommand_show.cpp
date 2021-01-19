// Copyright 2021 Kuznetsov Konstantin

#include <memory>

#include "cli/subcommand_show.h"
#include "db/transaction_table.h"
#include "db/utilities.h"

namespace fundex {

/** Function that runs code after Show subcommand is issued.
 *
 */
static void run_subcommand_show(const SubcommandShowOptions& opt) {
    TransactionTable transactions;
    // print all transactions
    if (opt.all_transactions) {
        print_transactions(transactions.get_all());
        return;
    }

    // print last transactions
    int n = opt.num_records;
    if (n >= 0) {
        auto last_transactions = transactions.get_last_transactions(n);
        print_transactions(last_transactions);
    }
}

void setup_subcommand_show(CLI::App *app) {
    auto opt = std::make_shared<SubcommandShowOptions>();
    auto sub = app->add_subcommand("show", "Show Transactions");
    sub->add_option("-n,--num_records", opt->num_records, "Number of records to show");
    sub->add_flag("--all", opt->all_transactions, "Show all Transactions");
    sub->callback([opt]() { run_subcommand_show(*opt); });
}

};  // namespace fundex
