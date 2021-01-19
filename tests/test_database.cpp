// Copyright 2021 Kuznetsov Konstantin

#include <string>

#include <catch2/catch.hpp>

#include "db/db_manager.h"

class DatabaseFixture {
 public:
    DatabaseFixture():
        db_name("test_db.sqlite"),
        db(fundex::DBManager::get_database(db_name)) {
        }

    ~DatabaseFixture() {
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
