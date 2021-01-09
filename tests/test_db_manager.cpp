// Copyright 2021 Kuznetsov Konstantin

#include <string>

#include "catch.hpp"
#include "db/db_manager.h"

TEST_CASE("Get Database from DBManager", "[DBManager]") {
    std::string db_name = "test_db.sqlite";
    REQUIRE_NOTHROW(fundex::DBManager::getDatabase(db_name));
}
