// Copyright 2021 Kuznetsov Konstantin

#ifndef TESTS_FIXTURES_H_
#define TESTS_FIXTURES_H_

#include <vector>
#include <string>

#include <CLI11/CLI11.hpp>

#include "cli/utilities.h"
#include "db/db_manager.h"
#include "db/transaction_table.h"
#include "db/category_table.h"

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

        try {
            // First argument is an App name
            argv.push_back((char*)"test-app");
            for (const auto& arg : args) {
                argv.push_back((char*)arg.data());
            }
            argv.push_back(nullptr);
            int argc = argv.size() - 1;
            CLI11_PARSE(app, argc, argv.data());
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return -1;
        }

        return 0;
    }

 protected:
    CLI::App app{"Test CLI App"};
};

#endif  // TESTS_FIXTURES_H_
