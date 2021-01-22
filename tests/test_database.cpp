// Copyright 2021 Kuznetsov Konstantin

#include <catch2/catch.hpp>

#include "fixtures.h"

TEST_CASE_METHOD(DBFixture, "Sync Database schema",
        "[Database]") {
    REQUIRE_NOTHROW(db->sync_schema());
}

TEST_CASE_METHOD(DBFixture, "Get table names from Database",
        "[Database]") {
    auto tables = db->table_names();
    std::sort(tables.begin(), tables.end());
    REQUIRE(tables.size() == 3);
    REQUIRE(tables[0] == "categories");
    REQUIRE(tables[1] == "sqlite_sequence");
    REQUIRE(tables[2] == "transactions");
}
