// Copyright 2021 Kuznetsov Konstantin

#include <string>
#include <vector>

#include "db/category_table.h"

namespace fundex {

CategoryTable::CategoryTable():
    Table() {
        // Create categories
        if (size() == 0) {
            std::vector<std::string> categories = {
                "Bills", "Food", "Leisure", "Homeneeds",
                "Transport", "Healthcare", "Miscellaneous"};
            for (const auto& cat : categories) {
                Category category = {-1, cat};
                add(category);
            }
        }
}

CategoryTable::~CategoryTable() {
}

int CategoryTable::get_id_from_name(const std::string& name) const {
    auto categories = db->get_all<Category>(
            sqlite_orm::where(sqlite_orm::c(&Category::cat_name) = name));

    if (categories.empty()) {
        return invalid_id;
    }
    return categories.begin()->id;
}


}  // namespace fundex
