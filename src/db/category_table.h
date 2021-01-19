// Copyright 2021 Kuznetsov Konstantin

/**
 * @file category_table.h
 * Header for Category table ORM.
 */

#ifndef SRC_DB_CATEGORY_TABLE_H_
#define SRC_DB_CATEGORY_TABLE_H_

#include "db/database.h"
#include "db/table.h"

namespace fundex {

/** ORM for Category table.
  *
  */
class CategoryTable : public Table<Category> {
 public:
    CategoryTable();
    ~CategoryTable();
};

};  // namespace fundex

#endif  // SRC_DB_CATEGORY_TABLE_H_
