// Copyright 2021 Kuznetsov Konstantin

#include <string>

#include <catch2/catch.hpp>
#include "db/db_manager.h"

class DBManagerFixture {
 public:
    DBManagerFixture():
        db_name("test_db.sqlite"),
        db(fundex::DBManager::get_database(db_name)) {
        }

 protected:
    std::string db_name;
    fundex::Database* db;
};

TEST_CASE_METHOD(DBManagerFixture, "Sync Database schema",
        "[DBManager]") {
    REQUIRE_NOTHROW(db->sync_schema());
}

TEST_CASE_METHOD(DBManagerFixture, "Get table names from Database",
        "[DBManager]") {
    auto tables = db->table_names();
    std::sort(tables.begin(), tables.end());
    REQUIRE(tables.size() == 4);
    REQUIRE(tables[0] == "categories");
    REQUIRE(tables[1] == "sqlite_sequence");
    REQUIRE(tables[2] == "subcategories");
    REQUIRE(tables[3] == "transactions");
}
