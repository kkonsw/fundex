// Copyright 2021 Kuznetsov Konstantin

#include <iostream>

#include <fort/fort.hpp>

#include "cli/flags.h"
#include "db/db_manager.h"
#include "db/database.h"

namespace fundex {

void setup_flags(CLI::App *app) {
    app->add_flag_callback("--list_cat", list_categories,
            "List all Categories");
}

void list_categories() {
    auto db = DBManager::get_database();
    fort::char_table table;
    table << fort::header << "ID" << "Category" << fort::endr;

    auto categories = db->get_all<Category>();
    for (const Category& cat : categories) {
        table << cat.id << cat.cat_name << fort::endr;
    }

    std::cout << table.to_string() << std::endl;
}

};  // namespace fundex
