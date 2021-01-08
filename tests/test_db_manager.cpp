// Copyright 2021 Kuznetsov Konstantin

#include "catch.hpp"
#include "db/db_manager.h"

TEST_CASE("Get database from db manager", "[DBManager]") {
    REQUIRE_NOTHROW(fundex::DBManager());
}
