// Copyright 2021 Kuznetsov Konstantin

#include <vector>
#include <string>

#include <CLI11/CLI11.hpp>

#include <catch2/catch.hpp>

#include "cli/utilities.h"
#include "db/db_manager.h"
#include "db/transaction_table.h"

class CLIFixture {
 public:
    CLIFixture():
        db(fundex::DBManager::get_database("test_db.sqlite")) {
            fundex::setup_all_options(&app);
        }

    ~CLIFixture() {
        transactions.remove_all();
    }

    int launch_app(std::vector<std::string> args) {
        std::vector<char*> argv;

        // First argument is an App name
        argv.push_back((char*)"test-app");
        for (const auto& arg : args) {
            argv.push_back((char*)arg.data());
        }
        argv.push_back(nullptr);
        int argc = argv.size() - 1;
        CLI11_PARSE(app, argc, argv.data());

        return 0;
    }

 protected:
    fundex::Database* db;
    fundex::TransactionTable transactions;
    CLI::App app{"Test CLI App"};
};

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
