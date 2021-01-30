// Copyright 2021 Kuznetsov Konstantin

/**
 * @file database.h
 * This file defines structs that represent Database records.
 */

#ifndef SRC_DB_DATABASE_H_
#define SRC_DB_DATABASE_H_

#include <sqlite_orm/sqlite_orm.h>

#include <memory>
#include <string>

namespace fundex {

/**
 * Represents Transaction's Category in Database.
 */
struct Category {
    /**
     * Category ID in Database.
     */
    int id;

    /**
     * Category name.
     */
    std::string cat_name;
};

/**
 * Represents Transaction in Database.
 */
struct Transaction {
    /**
     * Transaction ID in Database.
     */
    int id;

    /**
     * Date of Transaction as Unix Time.
     */
    int date;

    /**
     * Transaction amount.
     */
    int amount;

    /**
     * Transaction's Category.
     */
    std::unique_ptr<int> cat_id;

    /**
     * Notes about Transaction.
     */
    std::string note;
};

/**
 * Represents database schema.
 */
inline auto init_storage(const std::string &path = "db.sqlite") {
    return sqlite_orm::make_storage(path,

            sqlite_orm::make_table("categories",
                sqlite_orm::make_column("id", &Category::id,
                    sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                sqlite_orm::make_column("cat_name", &Category::cat_name)),

            sqlite_orm::make_table("transactions",
                sqlite_orm::make_column("id", &Transaction::id,
                    sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                sqlite_orm::make_column("date", &Transaction::date),
                sqlite_orm::make_column("amount", &Transaction::amount),
                sqlite_orm::make_column("cat_id", &Transaction::cat_id),
                sqlite_orm::make_column("note", &Transaction::note),
                sqlite_orm::foreign_key(&Transaction::cat_id).references(
                    &Category::id)));
}

/**
 * Typedef for sqlite_orm storage.
 */
using Database = decltype(init_storage());

};  // namespace fundex

#endif  // SRC_DB_DATABASE_H_
