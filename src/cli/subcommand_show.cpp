// Copyright 2021 Kuznetsov Konstantin

#include <algorithm>
#include <memory>

#include "cli/subcommand_show.h"
#include "db/transaction_table.h"
#include "db/utilities.h"

namespace fundex {

/**
 * Function that runs code after Show subcommand is issued.
 *
 */
static void run_subcommand_show(const SubcommandShowOptions& opt) {
    TransactionTable transactions;
    // Print all transactions
    if (opt.show_all) {
        auto all_transactions = transactions.get_transactions();
        print_transactions(all_transactions);
        return;
    }

    // Print last n transactions
    int n = opt.num_records;
    if (n >= 0) {
        auto last_transactions = transactions.get_transactions(n);
        // Reverse vector to print more recent transactions last
        std::reverse(last_transactions.begin(), last_transactions.end());
        print_transactions(last_transactions);
    }
}

void setup_subcommand_show(CLI::App *app) {
    auto opt = std::make_shared<SubcommandShowOptions>();
    auto sub = app->add_subcommand("show", "Show Transactions");
    auto show_all = sub->add_flag("--all", opt->show_all,
            "Show all Transactions");
    sub->add_option("-n,--num_records", opt->num_records,
            "Number of records to show")->excludes(show_all);

    std::string sort_help_msg = "Specify how to sort Transactions\n"
        "\tid       show first added Transactions\n"
        "\tid_d     show last added Transactions\n"
        "\tdate     show oldest Transactions\n"
        "\tdate_d   show most recent Transactions\n";
    sub->add_option("-s,--sort", opt->sort_order, sort_help_msg);
    sub->callback([opt]() { run_subcommand_show(*opt); });
}

};  // namespace fundex
