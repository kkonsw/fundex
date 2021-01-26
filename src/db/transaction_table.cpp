// Copyright 2021 Kuznetsov Konstantin

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

std::vector<Transaction> TransactionTable::get_transactions(int n,
        SortOrder order) const {
    switch (order) {
        case SortOrder::id_desc:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::id).desc(),
                    sqlite_orm::limit(n));
        case SortOrder::id:
        case SortOrder::date:
        case SortOrder::date_desc:
            throw std::runtime_error(
                    "Passed sort order value is not supported!");
        default:
            throw std::runtime_error("Unknown sort order!");
    }
}

std::vector<Transaction> TransactionTable::get_transactions(
        SortOrder order) const {
    switch (order) {
        case SortOrder::id_desc:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::id).desc());
        case SortOrder::id:
        case SortOrder::date:
        case SortOrder::date_desc:
            throw std::runtime_error(
                    "Passed sort order value is not supported!");
        default:
            throw std::runtime_error("Unknown sort order!");
    }
}

}  // namespace fundex
