// Copyright 2021 Kuznetsov Konstantin

#include <string>
#include <vector>

#include <catch2/catch.hpp>

#include "db/category_table.h"
#include "db/db_manager.h"

class DatabaseFixture {
 public:
    DatabaseFixture():
        db(fundex::DBManager::get_database("test_db.sqlite")) {
        }

    ~DatabaseFixture() {
        table.remove_all();
    }

 protected:
    fundex::Database* db;
    fundex::CategoryTable table;
};

TEST_CASE_METHOD(DatabaseFixture, "Get categories from Database",
        "[Database]") {
    std::vector<std::string> expected = {"Bills", "Food",
        "Leisure", "Homeneeds", "Transport", "Healthcare", "Miscellaneous"};

    auto categories = table.get_all();
    REQUIRE(categories.size() == expected.size());

    for (size_t i = 0; i < categories.size(); ++i) {
        auto cat = categories[i];
        REQUIRE(cat.cat_name == expected[i]);
    }
}
