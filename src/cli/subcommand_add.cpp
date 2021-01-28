// Copyright 2021 Kuznetsov Konstantin

#include <date/date.h>

#include <ctime>
#include <chrono>
#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>

#include "cli/subcommand_add.h"
#include "db/transaction_table.h"
#include "db/category_table.h"

namespace fundex {

/**
 * This function returns number of seconds since Epoch
 * for date provided by user. By default, returns today's date.
 *
 * @param user_date
 *   Date provided by user. Current required format is %d/%m/%Y.
 * @return
 *   Date as Unix Time (number of seconds since January 1, 1970).
 */
int get_date_in_seconds(const std::string& user_date = "") {
    using namespace date;

    // Get today's date in seconds
    auto today_days = floor<days>(std::chrono::system_clock::now());
    auto today_secs = floor<std::chrono::seconds>(today_days);

    // Return today's date by default
    if (user_date.empty()) {
        return today_secs.time_since_epoch().count();
    }

    // Parse date provided by user.
    // If date parsing fails, then today's date is returned.
    std::istringstream in{user_date};
    sys_seconds tp = today_secs;
    in >> parse("%d/%m/%Y", tp);
    auto date_secs = floor<std::chrono::seconds>(tp);
    return date_secs.time_since_epoch().count();
}

/**
 * Creates new Transaction from subcommand Add options.
 *
 * @param opt
 *   Subcommand Add options values.
 * @param transaction
 *   Pointer to new Transaction.
 * @return
 *   True, if new Transaction was created successfully.
 * @note
 *   Throws exception with invalid amount (<= 0)
 */
static bool setup_new_transaction(const SubcommandAddOptions& opt,
        Transaction *transaction) {
    if (opt.amount <= 0) {
        // User did not provide valid Transaction amount
        throw std::runtime_error("Invalid Transaction amount");
    }
    transaction->amount = opt.amount;

    // Setup transaction category
    auto cat_ptr = CategoryTable().get(opt.cat_id);
    if (cat_ptr != nullptr) {
        // Category provided by user is valid
        transaction->cat_id = std::make_unique<int>(cat_ptr->id);
    }

    transaction->note = opt.note;
    transaction->date = get_date_in_seconds(opt.date);

    return true;
}

/**
 * Function that runs code after Add subcommand is issued.
 *
 * @param opt
 *   Subcommand Add options values.
 */
static void run_subcommand_add(const SubcommandAddOptions& opt) {
    // Add new transaction to database
    Transaction transaction;
    TransactionTable transactions;
    if (setup_new_transaction(opt, &transaction)) {
        transactions.add(transaction);
    }
}

void setup_subcommand_add(CLI::App *app) {
    auto opt = std::make_shared<SubcommandAddOptions>();
    auto sub = app->add_subcommand("add", "Add new Transactions");
    sub->add_option("amount", opt->amount, "Transaction amount")->required();
    sub->add_option("-c,--cat", opt->cat_id, "Category ID for new Transaction");
    sub->add_option("-n, --note", opt->note, "Note about Transaction");
    sub->add_option("-d, --date", opt->date,
            "Date of Transaction, today by default");
    sub->callback([opt]() { run_subcommand_add(*opt); });
}

};  // namespace fundex
