// Copyright 2021 Kuznetsov Konstantin

#include <catch2/catch.hpp>

#include "db/transaction_table.h"
#include "fixtures.h"

TEST_CASE_METHOD(TransactionsFixture,
        "Get last added Transactions from Database",
        "[Transactions Table]") {
    // Retrieve n last added Transactions from Database
    size_t n = 3;
    auto last = transactions.get_transactions(n, fundex::SortOrder::id_desc);
    REQUIRE(last.size() == n);

    // Check for correct amount
    for (size_t i = 0; i < n; ++i) {
        int required_amount = num_transactions - i;
        REQUIRE(last[i].amount == required_amount);
    }
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get last added Transaction from Database",
        "[Transactions Table]") {
    // Retrieve last added Transaction from Database
    auto last = transactions.get_transactions(1, fundex::SortOrder::id_desc);
    REQUIRE(last.size() == 1);
    int required_amount = num_transactions;
    REQUIRE(last[0].amount == required_amount);
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get first added Transactions from Database",
        "[Transactions Table]") {
    // Retrieve n first added Transactions from Database
    size_t n = 3;
    auto last = transactions.get_transactions(n, fundex::SortOrder::id);
    REQUIRE(last.size() == n);

    // Check for correct amount
    for (size_t i = 1; i <= n; ++i) {
        int required_amount = i;
        REQUIRE(last[i - 1].amount == required_amount);
    }
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get first added Transaction from Database",
        "[Transactions Table]") {
    // Retrieve first added Transaction from Database
    auto last = transactions.get_transactions(1, fundex::SortOrder::id);
    REQUIRE(last.size() == 1);
    int required_amount = 1;
    REQUIRE(last[0].amount == required_amount);
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get all Transactions from Database sorted by id",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(fundex::SortOrder::id);
    size_t required_size = num_transactions;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (int i = 1; i <= num_transactions; ++i) {
        int required_amount = i;
        REQUIRE(all[i - 1].amount == required_amount);
    }
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get all Transactions from Database sorted by id in descending order",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(fundex::SortOrder::id_desc);
    size_t required_size = num_transactions;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (int i = 0; i < num_transactions; ++i) {
        int required_amount = num_transactions - i;
        REQUIRE(all[i].amount == required_amount);
    }
}

TEST_CASE_METHOD(CLIFixture,
        "Get all Transactions from Database sorted by date",
        "[Transactions Table]") {
    // Add Transactions with different dates
    launch_app({"add", "4", "--date", "21/01/2021"});
    launch_app({"add", "1", "--date", "01/01/2020"});
    launch_app({"add", "2", "--date", "01/06/2020"});
    launch_app({"add", "3", "--date", "31/12/2020"});

    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(fundex::SortOrder::date);
    size_t required_size = 4;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (size_t i = 1; i <= all.size(); ++i) {
        int required_amount = i;
        REQUIRE(all[i - 1].amount == required_amount);
    }
}

TEST_CASE_METHOD(CLIFixture,
        "Get all Transactions from Database sorted by date in descending order",
        "[Transactions Table]") {
    // Add Transactions with different dates
    launch_app({"add", "1", "--date", "21/01/2021"});
    launch_app({"add", "4", "--date", "01/01/2020"});
    launch_app({"add", "3", "--date", "01/06/2020"});
    launch_app({"add", "2", "--date", "31/12/2020"});

    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(fundex::SortOrder::date_desc);
    size_t required_size = 4;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (size_t i = 1; i <= all.size(); ++i) {
        int required_amount = i;
        REQUIRE(all[i - 1].amount == required_amount);
    }
}
