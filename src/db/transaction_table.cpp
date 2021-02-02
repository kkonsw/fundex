// Copyright 2021 Kuznetsov Konstantin

#include <sqlite_orm/sqlite_orm.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "db/transaction_table.h"
#include "db/transaction_filter.h"

namespace fundex {

TransactionTable::TransactionTable():
    Table() {
}

TransactionTable::~TransactionTable() {
}

auto TransactionTable::get_sort_order(SortOrder order) const {
    switch (order) {
        case SortOrder::First:
            return sqlite_orm::order_by(&Transaction::id);
        case SortOrder::Last:
            return sqlite_orm::order_by(&Transaction::id).desc();
        case SortOrder::Oldest:
            return sqlite_orm::order_by(&Transaction::date);
        case SortOrder::Recent:
            return sqlite_orm::order_by(&Transaction::date).desc();
        case SortOrder::Cheap:
            return sqlite_orm::order_by(&Transaction::amount);
        case SortOrder::Expensive:
            return sqlite_orm::order_by(&Transaction::amount).desc();
        default:
            throw std::runtime_error("Unknown sort order!");
    }
}

std::vector<Transaction> TransactionTable::get_transactions(
        const TransactionFilter &filter, int n) const {
    auto order_by = get_sort_order(filter.order);
    if (n != -1) {
        return db->get_all<Transaction>(order_by, sqlite_orm::limit(n));
    }

    // Return all Transactions
    return db->get_all<Transaction>(order_by);
}

}  // namespace fundex
