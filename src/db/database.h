// Copyright 2021 Kuznetsov Konstantin
#ifndef SRC_DB_DATABASE_H_
#define SRC_DB_DATABASE_H_

#include <memory>
#include <string>

#include "sqlite_orm.h"

namespace fundex {

/** Represents transaction's category in database.
  *
  */
struct Category {
    int id;  ///< Category ID in database
    std::string cat_name;  ///< Category name
};

/** Represents transaction's subcategory in database.
  *
  */
struct Subcategory {
    int id;  ///< Subcategory ID in database
    std::unique_ptr<int> cat_id;
    ///< Category ID that this Subcategory belongs to
    std::string subcat_name;  ///< Subcategory name
};

/** Represents database schema.
  *
  */
inline auto init_storage(const std::string &path = "db.sqlite") {
    return sqlite_orm::make_storage(path,

            sqlite_orm::make_table("categories",
                sqlite_orm::make_column("id", &Category::id,
                    sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                sqlite_orm::make_column("cat_name", &Category::cat_name)),

            sqlite_orm::make_table("subcategories",
                sqlite_orm::make_column("id", &Subcategory::id,
                    sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                sqlite_orm::make_column("cat_id", &Subcategory::cat_id),
                sqlite_orm::make_column("subcat_name",
                    &Subcategory::subcat_name),
                sqlite_orm::foreign_key(&Subcategory::cat_id).references(
                    &Category::id)));
}

using Database = decltype(init_storage());

};  // namespace fundex

#endif  // SRC_DB_DATABASE_H_
