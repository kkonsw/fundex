// Copyright 2021 Kuznetsov Konstantin

#include <ctime>
#include <iomanip>

#include <fort/fort.hpp>

#include "db/category_table.h"
#include "db/utilities.h"

namespace fundex {

void print_categories(std::ostream &output) {
    fort::char_table table;
    table << fort::header << "ID" << "Category" << fort::endr;

    for (const auto& cat : CategoryTable().get_all()) {
        table << cat.id << cat.cat_name << fort::endr;
    }

    output << table.to_string() << std::endl;
}

void print_transactions(const std::vector<Transaction>& transactions,
        std::ostream &output) {
    fort::char_table table;
    table << fort::header << "ID" << "Category" << "Date"
        << "Note" << "Amount" << fort::endr;

    int total = 0;
    for (const auto& transaction : transactions) {
        table << transaction.id;

        // print transaction category
        if (transaction.cat_id.get() == nullptr) {
            table << "-";
        } else {
            auto id = *transaction.cat_id.get();
            auto cat = CategoryTable().get(id);
            if (cat != nullptr) {
                table << cat->cat_name;
            }
        }

        // print transaction date
        std::time_t curr_date = transaction.date;
        table << std::put_time(std::localtime(&curr_date),
                "%d %b %Y");

        table << transaction.note;
        total += transaction.amount;
        table << transaction.amount;
        table << fort::endr;
    }
    table << fort::separator;

    // total sum of transactions
    table << "Total" << "" << "" << "" << total << fort::endr;
    int last_row = transactions.size();
    table[last_row + 1][0].set_cell_span(4);
    table[last_row + 1][0].set_cell_text_align(fort::text_align::right);

    output << table.to_string() << std::endl;
}

};  // namespace fundex
