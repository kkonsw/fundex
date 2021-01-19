// Copyright 2021 Kuznetsov Konstantin

#include <string>
#include <vector>

#include "db/transaction_table.h"

namespace fundex {

TransactionTable::TransactionTable():
    Table() {
}

TransactionTable::~TransactionTable() {
}

std::vector<Transaction> TransactionTable::get_last_transactions(int n) const {
    return db->get_all<Transaction>(
            sqlite_orm::order_by(&Transaction::id).desc(),
            sqlite_orm::limit(n));
}


}  // namespace fundex
