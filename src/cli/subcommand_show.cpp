// Copyright 2021 Kuznetsov Konstantin

#include <iostream>
#include <memory>

#include <fort/fort.hpp>

#include "db/db_manager.h"
#include "db/database.h"
#include "cli/subcommand_show.h"

namespace fundex {

void setup_subcommand_show(CLI::App *app) {
    auto opt = std::make_shared<SubcommandShowOptions>();
    auto sub = app->add_subcommand("show", "Show Transactions");
    sub->add_option("-n", opt->num_records, "Number of records to show");
    sub->callback([opt]() { run_subcommand_show(*opt); });
}

void run_subcommand_show(const SubcommandShowOptions& opt) {
    // get last transactions
    int n = opt.num_records;
    auto db = DBManager::get_database();
    auto last_transactions = db->get_all<Transaction>(
            sqlite_orm::order_by(&Transaction::id).desc(),
            sqlite_orm::limit(n));

    // print last transactions
    // TODO(fundex): move to separate function
    fort::char_table table;
    table << fort::header << "ID" << "Amount" << "Category ID" << fort::endr;
    for (const auto& transaction : last_transactions) {
        table << transaction.id << transaction.amount;
        if (transaction.cat_id.get() == nullptr) {
            table << 0;
        } else {
            table << *transaction.cat_id.get();
        }
        table << fort::endr;
    }
    std::cout << table.to_string() << std::endl;
}

};  // namespace fundex
