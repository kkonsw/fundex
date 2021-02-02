// Copyright 2021 Kuznetsov Konstantin

#ifndef TESTS_FIXTURES_H_
#define TESTS_FIXTURES_H_

#include <vector>
#include <string>

#include <CLI11/CLI11.hpp>

#include "cli/utilities.h"
#include "db/db_manager.h"
#include "db/transaction_filter.h"
#include "db/transaction_table.h"
#include "db/category_table.h"

/**
 * Creates database, provides access to tables.
 */
class DBFixture {
 public:
    DBFixture():
        db(fundex::DBManager::get_database("test_db.sqlite")) {
        }

    ~DBFixture() {
        transactions.remove_all();
        categories.remove_all();
    }

 protected:
    fundex::Database* db;
    fundex::CategoryTable categories;
    fundex::TransactionTable transactions;
};

/**
 * Adds few simple Transactions to Database.
 */
class TransactionsFixture : public DBFixture {
 public:
    TransactionsFixture():
        DBFixture(),
        num_transactions(5) {
            // Create fake Transactions
            for (int i = 1; i <= num_transactions; ++i) {
                fundex::Transaction transaction = {-1, 0, i, nullptr, "test"};
                transactions.add(transaction);
            }

            // Set up filters
            filter_first.order = fundex::SortOrder::First;
            filter_last.order = fundex::SortOrder::Last;
        }

    ~TransactionsFixture() {
    }

 protected:
    /**
     * Number of Transactions to add to Database.
     */
    int num_transactions;

    /**
     * Filter to retrieve first added Transactions.
     */
    fundex::TransactionFilter filter_first;

    /**
     * Filter to retrieve last Transactions.
     */
    fundex::TransactionFilter filter_last;
};


/**
 * Provides launch_app function to simulate user actions.
 */
class CLIFixture : public DBFixture {
 public:
    CLIFixture():
        DBFixture() {
            fundex::setup_all_options(&app);
        }

    ~CLIFixture() {
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
    CLI::App app{"Test CLI App"};
};

/**
 * Adds Transactions with different dates to Database.
 */
class DatesFixture : public CLIFixture {
 public:
     DatesFixture() {
         launch_app({"add", "4", "--date", "21/01/2021"});
         launch_app({"add", "2", "--date", "01/06/2020"});
         launch_app({"add", "1", "--date", "01/01/2020"});
         launch_app({"add", "3", "--date", "31/12/2020"});

         // Set up filters
         filter_recent.order = fundex::SortOrder::Recent;
         filter_oldest.order = fundex::SortOrder::Oldest;
     }

     ~DatesFixture() {
     }

 protected:
     /**
      * Filter to retrieve most recent Transactions.
      */
     fundex::TransactionFilter filter_recent;

     /**
      * Filter to retrieve oldest Transactions.
      */
     fundex::TransactionFilter filter_oldest;
};

/**
 * Adds Transactions with different expenses to Database.
 */
class ExpensesFixture : public CLIFixture {
 public:
     ExpensesFixture() {
         launch_app({"add", "4"});
         launch_app({"add", "2"});
         launch_app({"add", "1"});
         launch_app({"add", "3"});

         // Set up filters
         filter_cheapest.order = fundex::SortOrder::Cheap;
         filter_expensive.order = fundex::SortOrder::Expensive;
     }

     ~ExpensesFixture() {
     }

 protected:
     /**
      * Filter to retrieve cheapest Transactions.
      */
     fundex::TransactionFilter filter_cheapest;

     /**
      * Filter to retrieve expensive Transactions.
      */
     fundex::TransactionFilter filter_expensive;
};


#endif  // TESTS_FIXTURES_H_
