// Copyright 2021 Kuznetsov Konstantin

#include <catch2/catch.hpp>

#include "db/transaction_table.h"
#include "fixtures.h"

TEST_CASE_METHOD(DBFixture, "Get last Transactions from Database",
        "[Transactions Table]") {
    int num_transactions = 10;
    // Create fake Transactions
    for (int i = 1; i <= num_transactions; ++i) {
        fundex::Transaction transaction = {-1, 0, i, nullptr, "test"};
        transactions.add(transaction);
    }

    // Retrieve n last Transactions from Database
    size_t n = 5;
    auto last = transactions.get_transactions(n);
    REQUIRE(last.size() == n);

    // Check for correct amount
    for (size_t i = 0; i < n; ++i) {
        int required_amount = num_transactions - i;
        REQUIRE(last[i].amount == required_amount);
    }
}

TEST_CASE_METHOD(DBFixture, "Get last Transaction from Database",
        "[Transactions Table]") {
    int num_transactions = 10;
    // Create fake Transactions
    for (int i = 1; i <= num_transactions; ++i) {
        fundex::Transaction transaction = {-1, 0, i, nullptr, "test"};
        transactions.add(transaction);
    }

    // Retrieve last Transaction from Database
    auto last = transactions.get_transactions(1);
    REQUIRE(last.size() == 1);
    int required_amount = num_transactions;
    REQUIRE(last[0].amount == required_amount);
}

TEST_CASE_METHOD(DBFixture, "Get all Transactions from Database",
        "[Transactions Table]") {
    size_t num_transactions = 10;
    // Create fake Transactions
    for (size_t i = 1; i <= num_transactions; ++i) {
        fundex::Transaction transaction = {-1, 0,
            static_cast<int>(i), nullptr, "test"};
        transactions.add(transaction);
    }

    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions();
    REQUIRE(all.size() == num_transactions);

    // Check for correct amount
    for (size_t i = 0; i < num_transactions; ++i) {
        int required_amount = num_transactions - i;
        REQUIRE(all[i].amount == required_amount);
    }
}

TEST_CASE_METHOD(DBFixture,
        "Getting Transactions with unsupported Sort Order throws",
        "[Transactions Table]") {
    size_t num_transactions = 3;
    // Create fake Transactions
    for (size_t i = 1; i <= num_transactions; ++i) {
        fundex::Transaction transaction = {-1, 0,
            static_cast<int>(i), nullptr, "test"};
        transactions.add(transaction);
    }

    // Supported Sort Order
    REQUIRE_NOTHROW(transactions.get_transactions(fundex::SortOrder::id_desc));

    // Unsupported Sort Order
    REQUIRE_THROWS(transactions.get_transactions(fundex::SortOrder::id));
    REQUIRE_THROWS(transactions.get_transactions(fundex::SortOrder::date));
    REQUIRE_THROWS(transactions.get_transactions(fundex::SortOrder::date_desc));
}
