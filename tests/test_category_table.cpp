// Copyright 2021 Kuznetsov Konstantin

#include <string>

#include <catch2/catch.hpp>

#include "db/db_data.h"
#include "db/category_table.h"
#include "db/db_manager.h"

class DatabaseFixture {
 public:
    DatabaseFixture():
        db_name("test_db.sqlite"),
        db(fundex::DBManager::get_database(db_name)) {
        }

    ~DatabaseFixture() {
        table.remove_all();
    }

 protected:
    std::string db_name;
    fundex::Database* db;
    fundex::CategoryTable table;
};

TEST_CASE_METHOD(DatabaseFixture, "Add categories to Database",
        "[Database]") {
    fundex::add_categories();
    std::vector<std::string> expected = {"Bills", "Food",
        "Leisure", "Homeneeds", "Transport", "Healthcare", "Miscellaneous"};

    auto categories = table.get_all();
    REQUIRE(categories.size() == expected.size());

    for (size_t i = 0; i < categories.size(); ++i) {
        auto cat = categories[i];
        REQUIRE(cat.cat_name == expected[i]);
    }
}
