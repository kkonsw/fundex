// Copyright 2021 Kuznetsov Konstantin

#include <iostream>
#include <memory>

#include "cli/subcommand_add.h"
#include "db/db_manager.h"

namespace fundex {

void setup_subcommand_add(CLI::App *app) {
    auto opt = std::make_shared<SubcommandAddOptions>();
    auto sub = app->add_subcommand("add", "Add new Transactions");
    sub->add_option("-c,--cat", opt->cat_id, "Category ID for new Transaction");
    sub->callback([opt]() { run_subcommand_add(*opt); });
}

void run_subcommand_add(const SubcommandAddOptions& opt) {
    auto db = DBManager::get_database();
    auto category = db->get_all<Category>(sqlite_orm::where(
                sqlite_orm::c(&Category::id) = opt.cat_id));
    if (!category.empty()) {
        auto cat = *category.begin();
        std::cout << "Selected Category: " << cat.cat_name << std::endl;
    }
}

};  // namespace fundex
