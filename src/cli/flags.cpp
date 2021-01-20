// Copyright 2021 Kuznetsov Konstantin

#include "cli/flags.h"
#include "db/utilities.h"
#include "db/transaction_table.h"

namespace fundex {

/**
 * Callback function for `--list-cat` flag.
 *
 */
static void list_categories() {
    print_categories();
}

/**
 * Callback function for `--clear` flag.
 *
 */
static void remove_transactions() {
    TransactionTable transactions;
    transactions.remove_all();
}

void setup_flags(CLI::App *app) {
    app->add_flag_callback("--list_cat", list_categories,
            "List all Categories");
    app->add_flag_callback("--clear", remove_transactions,
            "Remove all Transactions");
}

};  // namespace fundex
