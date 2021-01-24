// Copyright 2021 Kuznetsov Konstantin

/**
 * @file category_table.h
 * Header for Category table ORM.
 */

#ifndef SRC_DB_CATEGORY_TABLE_H_
#define SRC_DB_CATEGORY_TABLE_H_

#include <string>

#include "db/database.h"
#include "db/table.h"

namespace fundex {

/**
 * ORM for Category table.
 */
class CategoryTable : public Table<Category> {
 public:
    CategoryTable();
    ~CategoryTable();

    /**
     * This functions returns Category's id from name.
     *
     * @param name
     *   Category's name.
     *
     * @return
     *   Category's id. If Category with requested name
     *   is not found, returns invalid id.
     */
    int get_id_from_name(const std::string& name) const;
};

};  // namespace fundex

#endif  // SRC_DB_CATEGORY_TABLE_H_
