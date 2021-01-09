// Copyright 2021 Kuznetsov Konstantin
#ifndef SRC_DB_DB_MANAGER_H_
#define SRC_DB_DB_MANAGER_H_

#include <algorithm>
#include <memory>

#include "database.h"

namespace fundex {

class DBManager {
 public:
    DBManager();

 private:
    std::unique_ptr<Database> db;
};

};  // namespace fundex

#endif  // SRC_DB_DB_MANAGER_H_
