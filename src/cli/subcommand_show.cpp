// Copyright 2021 Kuznetsov Konstantin

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "cli/subcommand_show.h"
#include "db/transaction_table.h"
#include "db/utilities.h"

namespace fundex {

/**
 * Returns SortOrder based on string from user.
 *
 * @param sort_option
 *   Option passed by User.
 * @return
 *   SortOrder for Transactions.
 * @note
 *   Throws exception if user passed invalid option.
 */
static SortOrder get_sort_order(const std::string &sort_option) {
    SortOrder sort_order;
    std::unordered_map<std::string, SortOrder> map = {
        {"first", SortOrder::id},
        {"last", SortOrder::id_desc},
        {"old", SortOrder::date},
        {"new", SortOrder::date_desc}
    };

    auto it = map.find(sort_option);
    if (it == map.end()) {
        throw std::runtime_error("Invalid sort option");
    }

    sort_order = it->second;
    return sort_order;
}

/**
 * Function that runs code after Show subcommand is issued.
 */
static void run_subcommand_show(const SubcommandShowOptions& opt) {
    // Show most recent Transactions by default
    SortOrder sort_order = SortOrder::date_desc;
    if (!opt.sort_order.empty()) {
        sort_order = get_sort_order(opt.sort_order);
    }

    // Print all transactions
    TransactionTable transactions;
    if (opt.show_all) {
        auto all_transactions = transactions.get_transactions(sort_order);
        print_transactions(all_transactions);
        return;
    }

    // Print n transactions
    int n = opt.num_records;
    if (n >= 0) {
        auto last_transactions = transactions.get_transactions(sort_order, n);
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
        "\tfirst    show first added Transactions\n"
        "\tlast     show last added Transactions\n"
        "\told      show oldest Transactions\n"
        "\tnew      show most recent Transactions\n";
    sub->add_option("-s,--sort", opt->sort_order, sort_help_msg);
    sub->callback([opt]() { run_subcommand_show(*opt); });
}

};  // namespace fundex
