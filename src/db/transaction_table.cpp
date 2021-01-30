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

std::vector<Transaction> TransactionTable::get_transactions(
        SortOrder order, int n) const {
    auto order_by = sqlite_orm::order_by(&Transaction::id);
    switch (order) {
        case SortOrder::id:
            order_by = sqlite_orm::order_by(&Transaction::id);
            break;
        case SortOrder::id_desc:
            order_by = sqlite_orm::order_by(&Transaction::id).desc();
            break;
        case SortOrder::date:
            order_by = sqlite_orm::order_by(&Transaction::date);
            break;
        case SortOrder::date_desc:
            order_by = sqlite_orm::order_by(&Transaction::date).desc();
            break;
        default:
            throw std::runtime_error("Unknown sort order!");
    }

    if (n != -1) {
        return db->get_all<Transaction>(order_by, sqlite_orm::limit(n));
    }

    // Return all Transactions
    return db->get_all<Transaction>(order_by);
}

}  // namespace fundex
