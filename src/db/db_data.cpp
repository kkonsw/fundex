// Copyright 2021 Kuznetsov Konstantin

#include <vector>
#include <string>

#include "db/db_data.h"
#include "db/db_manager.h"

namespace fundex {

void add_categories() {
    auto db = DBManager::get_database();
    std::vector<std::string> categories = {"Bills", "Food",
        "Leisure", "Homeneeds", "Transport", "Healthcare", "Miscellaneous"};
    for (const auto& cat : categories) {
        db->insert<Category>({-1, cat});
    }
}

};  // namespace fundex
