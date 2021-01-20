// Copyright 2021 Kuznetsov Konstantin

#include <ctime>
#include <iostream>
#include <string>
#include <memory>

#include "cli/subcommand_add.h"
#include "db/transaction_table.h"
#include "db/category_table.h"

namespace fundex {

/**
 * Creates new Transaction from subcommand Add options.
 *
 * @param opt
 *   Subcommand Add options values.
 * @param transaction
 *   Pointer to new Transaction.
 * @return
 *   True, if new Transaction was created successfully,
 *   false otherwise.
 */
static bool setup_new_transaction(const SubcommandAddOptions& opt,
        Transaction *transaction) {
    if (opt.amount <= 0) {
        // User did not provide valid Transaction amount
        return false;
    }
    transaction->amount = opt.amount;

    // Setup transaction category
    auto cat_ptr = CategoryTable().get(opt.cat_id);
    if (cat_ptr != nullptr) {
        // Category provided by user is valid
        transaction->cat_id = std::make_unique<int>(cat_ptr->id);
    }

    transaction->note = opt.note;

    // Current time
    transaction->date = std::time(nullptr);

    return true;
}

/**
 * Function that runs code after Add subcommand is issued.
 *
 * @param opt
 *   Subcommand Add options values.
 */
static void run_subcommand_add(const SubcommandAddOptions& opt) {
    // Add new transaction to database
    Transaction transaction;
    TransactionTable transactions;
    if (setup_new_transaction(opt, &transaction)) {
        transactions.add(transaction);
    }
}

void setup_subcommand_add(CLI::App *app) {
    auto opt = std::make_shared<SubcommandAddOptions>();
    auto sub = app->add_subcommand("add", "Add new Transactions");
    sub->add_option("-c,--cat", opt->cat_id, "Category ID for new Transaction");
    sub->add_option("amount", opt->amount, "Transaction amount")->required();
    sub->add_option("-n, --note", opt->note, "Note about Transaction");
    sub->callback([opt]() { run_subcommand_add(*opt); });
}

};  // namespace fundex
