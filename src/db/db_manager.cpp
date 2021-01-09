// Copyright 2021 Kuznetsov Konstantin

#include "db_manager.h"

#include <iostream>

namespace fundex {

DBManager::DBManager(const std::string& db_name):
    db(std::make_unique<Database>(init_storage(db_name))) {
    db->sync_schema();
}

Database * DBManager::getDatabase(const std::string& db_name) {
    static DBManager manager(db_name);
    return manager.getDB();
}

Database *DBManager::getDB() {
    return db.get();
}

};  // namespace fundex
