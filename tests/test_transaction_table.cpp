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

TEST_CASE_METHOD(DateTransactionsFixture,
        "Get most recent Transaction from Database",
        "[Transactions Table]") {
    // Retrieve most recent Transaction from Database
    auto recent = transactions.get_transactions(1,
            fundex::SortOrder::date_desc);
    REQUIRE(recent.size() == 1);
    int required_amount = 4;
    REQUIRE(recent[0].amount == required_amount);
}

TEST_CASE_METHOD(DateTransactionsFixture,
        "Get most recent Transactions from Database",
        "[Transactions Table]") {
    // Retrieve most recent Transactions from Database
    size_t n = 2;
    auto recent = transactions.get_transactions(n,
            fundex::SortOrder::date_desc);
    REQUIRE(recent.size() == n);
    REQUIRE(recent[0].amount == 4);
    REQUIRE(recent[1].amount == 3);
}

TEST_CASE_METHOD(DateTransactionsFixture,
        "Get oldest Transaction from Database",
        "[Transactions Table]") {
    // Retrieve oldest Transaction from Database
    auto recent = transactions.get_transactions(1,
            fundex::SortOrder::date);
    REQUIRE(recent.size() == 1);
    int required_amount = 1;
    REQUIRE(recent[0].amount == required_amount);
}

TEST_CASE_METHOD(DateTransactionsFixture,
        "Get oldest Transactions from Database",
        "[Transactions Table]") {
    // Retrieve oldest Transactions from Database
    size_t n = 2;
    auto recent = transactions.get_transactions(n,
            fundex::SortOrder::date);
    REQUIRE(recent.size() == n);
    REQUIRE(recent[0].amount == 1);
    REQUIRE(recent[1].amount == 2);
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

TEST_CASE_METHOD(DateTransactionsFixture,
        "Get all Transactions from Database sorted by date",
        "[Transactions Table]") {
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

TEST_CASE_METHOD(DateTransactionsFixture,
        "Get all Transactions from Database sorted by date in descending order",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(fundex::SortOrder::date_desc);
    size_t required_size = 4;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (size_t i = 0; i < all.size(); ++i) {
        int required_amount = 4 - i;
        REQUIRE(all[i].amount == required_amount);
    }
}
