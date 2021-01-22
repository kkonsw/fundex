// Copyright 2021 Kuznetsov Konstantin

#include <catch2/catch.hpp>

#include "fixtures.h"

TEST_CASE_METHOD(CLIFixture, "Remove all Transactions",
        "[Remove Transactions]") {
    size_t num_transactions = 5;
    // Create fake Transactions
    for (size_t i = 1; i <= num_transactions; ++i) {
        fundex::Transaction transaction = {-1, 0,
            static_cast<int>(i), nullptr, "test"};
        transactions.add(transaction);
    }

    REQUIRE(transactions.size() == num_transactions);

    // Remove all Transactions
    launch_app({"rm", "--all"});
    REQUIRE(transactions.size() == 0);
}
