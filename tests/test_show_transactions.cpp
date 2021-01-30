// Copyright 2021 Kuznetsov Konstantin

#include <catch2/catch.hpp>

#include "fixtures.h"

TEST_CASE_METHOD(CLIFixture, "Passing invalid sort option throws",
        "[Show Transactions]") {
    REQUIRE_THROWS(launch_app({"show", "--all", "--sort", "abcd"}));
}
