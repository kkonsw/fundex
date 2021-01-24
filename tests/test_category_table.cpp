// Copyright 2021 Kuznetsov Konstantin

#include <string>
#include <vector>

#include <catch2/catch.hpp>

#include "fixtures.h"

TEST_CASE_METHOD(DBFixture, "Get categories from Database",
        "[Category Table]") {
    std::vector<std::string> expected = {"Bills", "Food",
        "Leisure", "Homeneeds", "Transport", "Healthcare", "Miscellaneous"};

    auto from_db = categories.get_all();
    REQUIRE(from_db.size() == expected.size());

    for (size_t i = 0; i < from_db.size(); ++i) {
        auto cat = from_db[i];
        REQUIRE(cat.cat_name == expected[i]);
    }
}

TEST_CASE_METHOD(DBFixture, "Get valid Category's id from name",
        "[Category Table]") {
    int id = categories.get_id_from_name("Bills");
    REQUIRE(id > 0);
}

TEST_CASE_METHOD(DBFixture, "Get Category's id from invalid name",
        "[Category Table]") {
    int id = categories.get_id_from_name("abcd");
    REQUIRE(id == categories.invalid_id);
}
