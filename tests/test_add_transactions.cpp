// Copyright 2021 Kuznetsov Konstantin

#include <string>

#include <catch2/catch.hpp>

#include "fixtures.h"

TEST_CASE_METHOD(CLIFixture, "Add Transaction",
        "[Add Transactions]") {
    REQUIRE(transactions.size() == 0);
    // Add new Transaction
    launch_app({"add", "5"});
    REQUIRE(transactions.size() == 1);

    auto from_db = transactions.get_all();
    REQUIRE(from_db.size() == 1);
    auto& transaction = from_db[0];

    // Check Transaction details
    REQUIRE(transaction.amount == 5);
    REQUIRE(transaction.note == "");
    REQUIRE(transaction.cat_id == nullptr);
}

TEST_CASE_METHOD(CLIFixture, "Add Transaction with note",
        "[Add Transactions]") {
    REQUIRE(transactions.size() == 0);
    // Add new Transaction with note
    launch_app({"add", "5", "--note", "test note"});
    REQUIRE(transactions.size() == 1);

    auto from_db = transactions.get_all();
    REQUIRE(from_db.size() == 1);
    auto& transaction = from_db[0];

    // Check Transaction details
    REQUIRE(transaction.amount == 5);
    REQUIRE(transaction.note == "test note");
    REQUIRE(transaction.cat_id == nullptr);
}

TEST_CASE_METHOD(CLIFixture, "Add Transaction with Category",
        "[Add Transactions]") {
    REQUIRE(transactions.size() == 0);
    // Get id for Bills Category
    int bills_id = categories.get_id_from_name("Bills");

    // Add new Transaction to Bills Category
    std::vector<std::string> args = {"add", "5", "--cat",
        std::to_string(bills_id)};
    launch_app(args);
    REQUIRE(transactions.size() == 1);

    auto from_db = transactions.get_all();
    REQUIRE(from_db.size() == 1);
    auto& transaction = from_db[0];

    // Check Transaction details
    REQUIRE(transaction.amount == 5);
    REQUIRE(transaction.note == "");
    REQUIRE(transaction.cat_id != nullptr);

    // Check correct Category
    auto id = *transaction.cat_id.get();
    auto cat = categories.get(id);
    REQUIRE(cat != nullptr);
    REQUIRE(cat->cat_name == "Bills");
}
