// Copyright 2021 Kuznetsov Konstantin

#include <iostream>
#include <string>
#include <memory>

#include "cli/subcommand_add.h"
#include "db/db_manager.h"

namespace fundex {

void setup_subcommand_add(CLI::App *app) {
    auto opt = std::make_shared<SubcommandAddOptions>();
    auto sub = app->add_subcommand("add", "Add new Transactions");
    sub->add_option("-c,--cat", opt->cat_id, "Category ID for new Transaction");
    sub->add_option("amount", opt->amount, "Transaction amount")->required();
    sub->callback([opt]() { run_subcommand_add(*opt); });
}

void run_subcommand_add(const SubcommandAddOptions& opt) {
    // add new transaction to database
    auto db = DBManager::get_database();
    Transaction transaction;
    if (setup_new_transaction(opt, &transaction)) {
        db->insert(transaction);
        // TODO(fundex): nice message about new transaction
        std::cout << "Created New Transaction" << std::endl;
    }
}

bool setup_new_transaction(const SubcommandAddOptions& opt,
        Transaction *transaction) {
    if (opt.amount <= 0) {
        // user did not provide valid Transaction amount
        return false;
    }
    transaction->amount = opt.amount;

    // setup transaction category
    auto db = DBManager::get_database();
    auto category = db->get_all<Category>(sqlite_orm::where(
                sqlite_orm::c(&Category::id) = opt.cat_id));
    if (!category.empty()) {
        // category provided by user
        auto cat = *category.begin();
        transaction->cat_id = std::make_unique<int>(cat.id);
    }

    return true;
}

};  // namespace fundex
