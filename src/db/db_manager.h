// Copyright 2021 Kuznetsov Konstantin
#ifndef SRC_DB_DB_MANAGER_H_
#define SRC_DB_DB_MANAGER_H_

#include <memory>
#include <string>

#include "database.h"

namespace fundex {

/** DBManager is a singleton that provides access to
  * Database Storage from sqlite_orm.
  */
class DBManager {
 public:
     /** Get Database Storage from static instance of DB Manager.
       * \param db_name Database name.
       * \warning Static instance of DB Manager is created
       * when this function is called the first time.
       * \returns Pointer to Database Storage.
       */
     static Database* getDatabase(const std::string& db_name = "db.sqlite");

 private:
    explicit DBManager(const std::string& db_name = "db.sqlite");
    std::unique_ptr<Database> db;
    Database* getDB();
};

};  // namespace fundex

#endif  // SRC_DB_DB_MANAGER_H_
