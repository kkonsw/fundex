// Copyright 2021 Kuznetsov Konstantin
#ifndef SRC_DB_DB_MANAGER_H_
#define SRC_DB_DB_MANAGER_H_

#include <memory>
#include <string>

#include "database.h"

namespace fundex {

/** DBManager is a singleton that provides access to
  * database storage from sqlite_orm.
  */
class DBManager {
 public:
     static Database* getDatabase(const std::string& db_name = "db.sqlite");

 private:
    explicit DBManager(const std::string& db_name = "db.sqlite");
    std::unique_ptr<Database> db;
    Database* getDB();
};

};  // namespace fundex

#endif  // SRC_DB_DB_MANAGER_H_
