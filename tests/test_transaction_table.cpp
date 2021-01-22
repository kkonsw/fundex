// Copyright 2021 Kuznetsov Konstantin

#include <catch2/catch.hpp>

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
    auto last = transactions.get_last_transactions(n);
    REQUIRE(last.size() == n);

    // Check for correct amount
    for (size_t i = 0; i < n; ++i) {
        int required_amount = num_transactions - i;
        REQUIRE(last[i].amount == required_amount);
    }
}
