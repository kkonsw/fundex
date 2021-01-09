// Copyright 2021 Kuznetsov Konstantin

#include "catch.hpp"
#include "db/db_manager.h"

TEST_CASE("Create DB manager", "[DBManager]") {
    REQUIRE_NOTHROW(fundex::DBManager());
}
