// Copyright 2021 Kuznetsov Konstantin

#include <sqlite_orm/sqlite_orm.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "db/transaction_table.h"

namespace fundex {

TransactionTable::TransactionTable():
    Table() {
}

TransactionTable::~TransactionTable() {
}

auto TransactionTable::get_sort_order(SortOrder order) const {
    switch (order) {
        case SortOrder::id:
            return sqlite_orm::order_by(&Transaction::id);
        case SortOrder::id_desc:
            return sqlite_orm::order_by(&Transaction::id).desc();
        case SortOrder::date:
            return sqlite_orm::order_by(&Transaction::date);
        case SortOrder::date_desc:
            return sqlite_orm::order_by(&Transaction::date).desc();
        case SortOrder::amount:
            return sqlite_orm::order_by(&Transaction::amount);
        case SortOrder::amount_desc:
            return sqlite_orm::order_by(&Transaction::amount).desc();
        default:
            throw std::runtime_error("Unknown sort order!");
    }
}

std::vector<Transaction> TransactionTable::get_transactions(
        SortOrder order, int n) const {
    auto order_by = get_sort_order(order);
    if (n != -1) {
        return db->get_all<Transaction>(order_by, sqlite_orm::limit(n));
    }

    // Return all Transactions
    return db->get_all<Transaction>(order_by);
}

}  // namespace fundex
