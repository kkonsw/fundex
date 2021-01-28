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
        case SortOrder::id:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::id),
                    sqlite_orm::limit(n));
        case SortOrder::id_desc:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::id).desc(),
                    sqlite_orm::limit(n));
        case SortOrder::date:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::date),
                    sqlite_orm::limit(n));
        case SortOrder::date_desc:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::date).desc(),
                    sqlite_orm::limit(n));
        default:
            throw std::runtime_error("Unknown sort order!");
    }
}

std::vector<Transaction> TransactionTable::get_transactions(
        SortOrder order) const {
    switch (order) {
        case SortOrder::id:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::id));
        case SortOrder::id_desc:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::id).desc());
        case SortOrder::date:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::date));
        case SortOrder::date_desc:
            return db->get_all<Transaction>(
                    sqlite_orm::order_by(&Transaction::date).desc());
        default:
            throw std::runtime_error("Unknown sort order!");
    }
}

}  // namespace fundex
