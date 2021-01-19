// Copyright 2021 Kuznetsov Konstantin

#include <db/utilities.h>

#include <fort/fort.hpp>

#include "db/category_table.h"

namespace fundex {

void print_categories(std::ostream &output) {
    fort::char_table table;
    table << fort::header << "ID" << "Category" << fort::endr;

    CategoryTable categories;
    for (const auto& cat : categories.get_all()) {
        table << cat.id << cat.cat_name << fort::endr;
    }

    output << table.to_string() << std::endl;
}

void print_transactions(const std::vector<Transaction>& transactions,
        std::ostream &output) {
    fort::char_table table;
    table << fort::header << "ID" << "Amount" << "Category ID" << fort::endr;
    for (const auto& transaction : transactions) {
        table << transaction.id << transaction.amount;
        if (transaction.cat_id.get() == nullptr) {
            table << 0;
        } else {
            table << *transaction.cat_id.get();
        }
        table << fort::endr;
    }
    output << table.to_string() << std::endl;
}

};  // namespace fundex
