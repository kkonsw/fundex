// Copyright 2021 Kuznetsov Konstantin
/**
 * @file db_data.h
 * This file has functions to add test data to Database.
 */
#ifndef SRC_DB_DB_DATA_H_
#define SRC_DB_DB_DATA_H_

#include <vector>
#include <string>

#include "db/category_table.h"

namespace fundex {

/** Adds categories to Database for testing purposes.
  *
  */
inline void add_categories() {
    CategoryTable table;
    std::vector<std::string> categories = {"Bills", "Food",
        "Leisure", "Homeneeds", "Transport", "Healthcare", "Miscellaneous"};
    for (const auto& cat : categories) {
        Category category = {-1, cat};
        table.add(category);
    }
}

};  // namespace fundex

#endif  // SRC_DB_DB_DATA_H_
