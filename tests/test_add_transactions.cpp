// Copyright 2021 Kuznetsov Konstantin

#include <string>

#include <catch2/catch.hpp>
#include <date/date.h>

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

TEST_CASE_METHOD(CLIFixture,
        "Adding Transaction throws when amount is negative",
        "[Add Transactions]") {
    // Add new Transaction with negative amount
    REQUIRE_THROWS(launch_app({"add", "-5"}));
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

TEST_CASE_METHOD(CLIFixture, "Add Transaction without date option",
        "[Add Transactions]") {
    REQUIRE(transactions.size() == 0);
    // Add new Transaction without date option
    launch_app({"add", "5"});
    REQUIRE(transactions.size() == 1);

    auto from_db = transactions.get_all();
    REQUIRE(from_db.size() == 1);
    auto& transaction = from_db[0];

    // Get today's date in seconds
    using namespace date;
    auto today_days = floor<days>(std::chrono::system_clock::now());
    auto today_secs = floor<std::chrono::seconds>(today_days);
    auto secs = today_secs.time_since_epoch().count();

    // Check that date of Transaction is equal to today
    REQUIRE(transaction.amount == 5);
    REQUIRE(transaction.date == secs);
}

TEST_CASE_METHOD(CLIFixture, "Add Transaction with invalid date",
        "[Add Transactions]") {
    REQUIRE(transactions.size() == 0);
    // Add new Transaction with invalid date
    launch_app({"add", "5", "--date", "abcd"});
    REQUIRE(transactions.size() == 1);

    auto from_db = transactions.get_all();
    REQUIRE(from_db.size() == 1);
    auto& transaction = from_db[0];

    // Get today's date in seconds
    using namespace date;
    auto today_days = floor<days>(std::chrono::system_clock::now());
    auto today_secs = floor<std::chrono::seconds>(today_days);
    auto secs = today_secs.time_since_epoch().count();

    // Check that date of Transaction is equal to today
    REQUIRE(transaction.amount == 5);
    REQUIRE(transaction.date == secs);
}

TEST_CASE_METHOD(CLIFixture, "Add Transaction with valid date",
        "[Add Transactions]") {
    REQUIRE(transactions.size() == 0);
    // Add new Transaction with valid date
    std::string date = "01/01/2000";
    launch_app({"add", "5", "--date", date});
    REQUIRE(transactions.size() == 1);

    auto from_db = transactions.get_all();
    REQUIRE(from_db.size() == 1);
    auto& transaction = from_db[0];

    // Get required date in seconds
    using namespace date;
    std::istringstream in{date};
    sys_seconds tp;
    in >> parse("%d/%m/%Y", tp);
    auto date_secs = floor<std::chrono::seconds>(tp);
    auto secs = date_secs.time_since_epoch().count();

    // Check that date of Transaction is correct
    REQUIRE(transaction.amount == 5);
    REQUIRE(transaction.date == secs);
}
