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
 * Various ways to retrieve sorted Transactions from Database.
 */
enum class SortOrder {
    /**
     * Retrieve Transactions by id.
     *
     * @note
     *   first added Transactions
     */
    id,

    /**
     * Retrieve Transactions by id.
     *
     * @note
     *   last added Transactions
     */
    id_desc,

    /**
     * Retrieve Transactions by date.
     *
     * @note
     *   most recent Transactions
     */
    date,

    /**
     * Retrieve Transactions by date.
     *
     * @note
     *   oldest Transactions
     */
    date_desc,
};

/**
 * ORM for Transaction table.
 */
class TransactionTable : public Table<Transaction> {
 public:
    TransactionTable();
    ~TransactionTable();

    /**
     * Function to retrieve n Transactions from Database.
     * By default, retrieves n last added Transactions.
     *
     * @param n
     *   Number of Transactions.
     * @param order
     *   Sort Order for retrieved Transactions.
     */
    std::vector<Transaction> get_transactions(int n,
            SortOrder order = SortOrder::id_desc) const;

    /**
     * Function to retrieve all Transactions from Database.
     * By default, retrieves Transactions sorted by Transaction::id.
     *
     * @param order
     *   Sort Order for retrieved Transactions.
     */
    std::vector<Transaction> get_transactions(
            SortOrder order = SortOrder::id_desc) const;
};

};  // namespace fundex

#endif  // SRC_DB_TRANSACTION_TABLE_H_
