// Copyright 2021 Kuznetsov Konstantin

/**
 * @file transaction_table.h
 * Header for Transaction table ORM.
 */

#ifndef SRC_DB_TRANSACTION_TABLE_H_
#define SRC_DB_TRANSACTION_TABLE_H_

#include <vector>

#include "db/database.h"
#include "db/table.h"

namespace fundex {

/**
 * ORM for Transaction table.
 */
class TransactionTable : public Table<Transaction> {
 public:
    TransactionTable();
    ~TransactionTable();

    /**
     * Function to get last n Transactions from Database.
     *
     * @param n
     *   Number of Transactions.
     */
    std::vector<Transaction> get_last_transactions(int n) const;
};

};  // namespace fundex

#endif  // SRC_DB_TRANSACTION_TABLE_H_
