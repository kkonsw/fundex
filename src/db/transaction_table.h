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
     * To retrieve Transactions sorted by id.
     *
     * @note
     *   First added Transactions.
     */
    id,

    /**
     * To retrieve Transactions sorted by id.
     *
     * @note
     *   Last added Transactions.
     */
    id_desc,

    /**
     * To retrieve Transactions sorted by date.
     *
     * @note
     *   Oldest Transactions.
     */
    date,

    /**
     * To retrieve Transactions sorted by date.
     *
     * @note
     *   Most recent Transactions.
     */
    date_desc,

    /**
     * To retrieve Transactions sorted by amount.
     *
     * @note
     *   Cheapest Transactions.
     */
    amount,

    /**
     * To retrieve Transactions sorted by amount.
     *
     * @note
     *   Most expensive Transactions.
     */
    amount_desc,
};

/**
 * ORM for Transaction table.
 */
class TransactionTable : public Table<Transaction> {
 public:
    TransactionTable();
    ~TransactionTable();

    /**
     * Function to retrieve Transactions from Database.
     * By default, retrieves Transactions sorted by Transaction::date.
     *
     * @param n
     *   Number of Transactions.
     * @param order
     *   Sort Order for retrieved Transactions.
     */
    std::vector<Transaction> get_transactions(
            SortOrder order = SortOrder::date_desc, int n = -1) const;

 private:
    /**
     * Returns sqlite_orm::order_by clause based on SortOrder parameter.
     */
    auto get_sort_order(SortOrder order) const;
};


};  // namespace fundex

#endif  // SRC_DB_TRANSACTION_TABLE_H_
