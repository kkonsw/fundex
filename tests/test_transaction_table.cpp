// Copyright 2021 Kuznetsov Konstantin

#include <catch2/catch.hpp>

#include "db/transaction_filter.h"
#include "db/transaction_table.h"
#include "fixtures.h"

TEST_CASE_METHOD(TransactionsFixture,
        "Get last added Transactions",
        "[Transactions Table]") {
    // Retrieve n last added Transactions from Database
    size_t n = 3;
    auto last = transactions.get_transactions(filter_last, n);
    REQUIRE(last.size() == n);

    // Check for correct amount
    for (size_t i = 0; i < n; ++i) {
        int required_amount = num_transactions - i;
        REQUIRE(last[i].amount == required_amount);
    }
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get last added Transaction",
        "[Transactions Table]") {
    // Retrieve last added Transaction from Database
    auto last = transactions.get_transactions(filter_last, 1);
    REQUIRE(last.size() == 1);
    int required_amount = num_transactions;
    REQUIRE(last[0].amount == required_amount);
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get first added Transactions",
        "[Transactions Table]") {
    // Retrieve n first added Transactions from Database
    size_t n = 3;
    auto first = transactions.get_transactions(filter_first, n);
    REQUIRE(first.size() == n);

    // Check for correct amount
    for (size_t i = 1; i <= n; ++i) {
        int required_amount = i;
        REQUIRE(first[i - 1].amount == required_amount);
    }
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get first added Transaction",
        "[Transactions Table]") {
    // Retrieve first added Transaction from Database
    auto first = transactions.get_transactions(filter_first, 1);
    REQUIRE(first.size() == 1);
    int required_amount = 1;
    REQUIRE(first[0].amount == required_amount);
}

TEST_CASE_METHOD(DatesFixture,
        "Get most recent Transaction",
        "[Transactions Table]") {
    // Retrieve most recent Transaction from Database
    auto recent = transactions.get_transactions(filter_recent, 1);
    REQUIRE(recent.size() == 1);
    int required_amount = 4;
    REQUIRE(recent[0].amount == required_amount);
}

TEST_CASE_METHOD(DatesFixture,
        "Get most recent Transactions",
        "[Transactions Table]") {
    // Retrieve most recent Transactions from Database
    size_t n = 2;
    auto recent = transactions.get_transactions(filter_recent, n);
    REQUIRE(recent.size() == n);
    REQUIRE(recent[0].amount == 4);
    REQUIRE(recent[1].amount == 3);
}

TEST_CASE_METHOD(DatesFixture,
        "Get most recent Transactions with default filter",
        "[Transactions Table]") {
    // Retrieve most recent Transactions from Database with default filter
    size_t n = 2;
    auto recent = transactions.get_transactions(fundex::TransactionFilter(), n);
    REQUIRE(recent.size() == n);
    REQUIRE(recent[0].amount == 4);
    REQUIRE(recent[1].amount == 3);
}

TEST_CASE_METHOD(DatesFixture,
        "Get oldest Transaction",
        "[Transactions Table]") {
    // Retrieve oldest Transaction from Database
    auto oldest = transactions.get_transactions(filter_oldest, 1);
    REQUIRE(oldest.size() == 1);
    int required_amount = 1;
    REQUIRE(oldest[0].amount == required_amount);
}

TEST_CASE_METHOD(DatesFixture,
        "Get oldest Transactions",
        "[Transactions Table]") {
    // Retrieve oldest Transactions from Database
    size_t n = 2;
    auto oldest = transactions.get_transactions(filter_oldest, n);
    REQUIRE(oldest.size() == n);
    REQUIRE(oldest[0].amount == 1);
    REQUIRE(oldest[1].amount == 2);
}

TEST_CASE_METHOD(ExpensesFixture,
        "Get most expensive Transaction",
        "[Transactions Table]") {
    // Retrieve most expensive Transaction from Database
    auto expensive = transactions.get_transactions(filter_expensive, 1);
    REQUIRE(expensive.size() == 1);
    int required_amount = 4;
    REQUIRE(expensive[0].amount == required_amount);
}

TEST_CASE_METHOD(ExpensesFixture,
        "Get most expensive Transactions",
        "[Transactions Table]") {
    // Retrieve most expensive Transactions from Database
    size_t n = 2;
    auto expensive = transactions.get_transactions(filter_expensive, n);
    REQUIRE(expensive.size() == n);
    REQUIRE(expensive[0].amount == 4);
    REQUIRE(expensive[1].amount == 3);
}

TEST_CASE_METHOD(ExpensesFixture,
        "Get cheapest Transaction",
        "[Transactions Table]") {
    // Retrieve cheapest Transaction from Database
    auto cheapest = transactions.get_transactions(filter_cheapest, 1);
    REQUIRE(cheapest.size() == 1);
    int required_amount = 1;
    REQUIRE(cheapest[0].amount == required_amount);
}

TEST_CASE_METHOD(ExpensesFixture,
        "Get cheapest Transactions",
        "[Transactions Table]") {
    // Retrieve cheapest Transactions from Database
    size_t n = 2;
    auto cheapest = transactions.get_transactions(filter_cheapest, n);
    REQUIRE(cheapest.size() == n);
    REQUIRE(cheapest[0].amount == 1);
    REQUIRE(cheapest[1].amount == 2);
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get all Transactions sorted by id",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(filter_first);
    size_t required_size = num_transactions;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (int i = 1; i <= num_transactions; ++i) {
        int required_amount = i;
        REQUIRE(all[i - 1].amount == required_amount);
    }
}

TEST_CASE_METHOD(TransactionsFixture,
        "Get all Transactions sorted by id in descending order",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(filter_last);
    size_t required_size = num_transactions;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (int i = 0; i < num_transactions; ++i) {
        int required_amount = num_transactions - i;
        REQUIRE(all[i].amount == required_amount);
    }
}

TEST_CASE_METHOD(DatesFixture,
        "Get all Transactions sorted by date",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(filter_oldest);
    size_t required_size = 4;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (size_t i = 1; i <= all.size(); ++i) {
        int required_amount = i;
        REQUIRE(all[i - 1].amount == required_amount);
    }
}

TEST_CASE_METHOD(DatesFixture,
        "Get all Transactions sorted by date in descending order",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(filter_recent);
    size_t required_size = 4;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (size_t i = 0; i < all.size(); ++i) {
        int required_amount = 4 - i;
        REQUIRE(all[i].amount == required_amount);
    }
}

TEST_CASE_METHOD(ExpensesFixture,
        "Get all Transactions sorted by amount",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(filter_cheapest);
    size_t required_size = 4;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (size_t i = 1; i <= all.size(); ++i) {
        int required_amount = i;
        REQUIRE(all[i - 1].amount == required_amount);
    }
}

TEST_CASE_METHOD(ExpensesFixture,
        "Get all Transactions sorted by amount in descending order",
        "[Transactions Table]") {
    // Retrieve all Transactions from Database
    auto all = transactions.get_transactions(filter_expensive);
    size_t required_size = 4;
    REQUIRE(all.size() == required_size);

    // Check for correct amount
    for (size_t i = 0; i < all.size(); ++i) {
        int required_amount = 4 - i;
        REQUIRE(all[i].amount == required_amount);
    }
}
