// Copyright 2021 Kuznetsov Konstantin

#include <vector>
#include <string>

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

TEST_CASE_METHOD(CLIFixture, "Remove specific Transaction",
        "[Remove Transactions]") {
    // Create fake Transaction
    fundex::Transaction transaction = {-1, 0, 1, nullptr, "test"};
    auto id = transactions.add(transaction);
    REQUIRE(transactions.size() == 1);

    // Remove Transaction
    launch_app({"rm", std::to_string(id)});
    REQUIRE(transactions.size() == 0);
}

TEST_CASE_METHOD(CLIFixture, "Remove multiple Transactions",
        "[Remove Transactions]") {
    size_t num_transactions = 5;
    std::vector<int> ids;
    // Create fake Transactions
    for (size_t i = 1; i <= num_transactions; ++i) {
        fundex::Transaction transaction = {-1, 0,
            static_cast<int>(i), nullptr, "test"};
        ids.push_back(transactions.add(transaction));
    }
    REQUIRE(transactions.size() == num_transactions);

    // Args to remove all Transactions
    std::vector<std::string> args;
    args.push_back("rm");
    for (size_t i = 0; i < num_transactions; ++i) {
        auto id = std::to_string(ids[i]);
        args.push_back(id);
    }

    launch_app(args);
    REQUIRE(transactions.size() == 0);
}
