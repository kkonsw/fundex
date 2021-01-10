// Copyright 2021 Kuznetsov Konstantin

#include <string>

#include <catch2/catch.hpp>

#include "db/db_data.h"
#include "db/db_manager.h"

class DatabaseFixture {
 public:
    DatabaseFixture():
        db_name("test_db.sqlite"),
        db(fundex::DBManager::get_database(db_name)) {
        }

    ~DatabaseFixture() {
        // Clear Database
        db->remove_all<fundex::Category>();
    }

 protected:
    std::string db_name;
    fundex::Database* db;
};

TEST_CASE_METHOD(DatabaseFixture, "Sync Database schema",
        "[Database]") {
    REQUIRE_NOTHROW(db->sync_schema());
}

TEST_CASE_METHOD(DatabaseFixture, "Get table names from Database",
        "[Database]") {
    auto tables = db->table_names();
    std::sort(tables.begin(), tables.end());
    REQUIRE(tables.size() == 4);
    REQUIRE(tables[0] == "categories");
    REQUIRE(tables[1] == "sqlite_sequence");
    REQUIRE(tables[2] == "subcategories");
    REQUIRE(tables[3] == "transactions");
}

TEST_CASE_METHOD(DatabaseFixture, "Add categories to Database",
        "[Database]") {
    fundex::add_categories();
    std::vector<std::string> expected = {"Bills", "Food",
        "Leisure", "Homeneeds", "Transport", "Healthcare", "Miscellaneous"};

    auto categories = db->get_all<fundex::Category>();
    REQUIRE(categories.size() == expected.size());

    for (size_t i = 0; i < categories.size(); ++i) {
        auto cat = categories[i];
        REQUIRE(cat.cat_name == expected[i]);
    }
}
