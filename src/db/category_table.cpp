// Copyright 2021 Kuznetsov Konstantin

#include <string>
#include <vector>

#include "db/category_table.h"

namespace fundex {

CategoryTable::CategoryTable():
    Table() {
        // Create test data
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

}  // namespace fundex
