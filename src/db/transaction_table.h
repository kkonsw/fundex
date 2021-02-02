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
#include "db/transaction_filter.h"

namespace fundex {

/**
 * ORM for Transaction table.
 */
class TransactionTable : public Table<Transaction> {
 public:
    TransactionTable();
    ~TransactionTable();

    /**
     * Function to retrieve Transactions from Database.
     *
     * @param n
     *   Number of Transactions.
     * @param filter
     *   Filter to get specific Transactions.
     */
    std::vector<Transaction> get_transactions(
            const TransactionFilter &filter = TransactionFilter(),
            int n = -1) const;

 private:
    /**
     * Returns sqlite_orm::order_by clause based on SortOrder parameter.
     */
    auto get_sort_order(SortOrder order) const;
};


};  // namespace fundex

#endif  // SRC_DB_TRANSACTION_TABLE_H_
