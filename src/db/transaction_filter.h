// Copyright 2021 Kuznetsov Konstantin

/**
 * @file transaction_filter.h
 * Header with filter for Transactions.
 */

#ifndef SRC_DB_TRANSACTION_FILTER_H_
#define SRC_DB_TRANSACTION_FILTER_H_

#include <vector>

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
    First,

    /**
     * To retrieve Transactions sorted by id.
     *
     * @note
     *   Last added Transactions.
     */
    Last,

    /**
     * To retrieve Transactions sorted by date.
     *
     * @note
     *   Oldest Transactions.
     */
    Oldest,

    /**
     * To retrieve Transactions sorted by date.
     *
     * @note
     *   Most recent Transactions.
     */
    Recent,

    /**
     * To retrieve Transactions sorted by amount.
     *
     * @note
     *   Cheapest Transactions.
     */
    Cheap,

    /**
     * To retrieve Transactions sorted by amount.
     *
     * @note
     *   Most expensive Transactions.
     */
    Expensive,
};

/**
 * Filter to retrieve specific Transactions from Database.
 * Can be used to retrieve Transactions from required time period
 * and from selected categories.
 * Also contains sort order for retrieved Transactions.
 */
struct TransactionFilter {
    /**
     * Sort Order for retrieved Transactions.
     * By default, sort by dates (most recent Transactions first).
     */
    SortOrder order = SortOrder::Recent;

    /**
     * Date in seconds. Provide first and last dates
     * to retrieve Transactions from specific time period.
     */
    int first_date;

    /**
     * Date in seconds. Provide first and last dates
     * to retrieve Transactions from specific time period.
     */
    int last_date;

    /**
     * Provide Categories's ids to retrieve Transactions
     * from specific Categories.
     */
    std::vector<int> categories;
};

};  // namespace fundex

#endif  // SRC_DB_TRANSACTION_FILTER_H_
