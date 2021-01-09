// Copyright 2021 Kuznetsov Konstantin

#include "db/db_manager.h"

#include <iostream>

namespace fundex {

DBManager::DBManager():
    db(std::make_unique<Database>(init_storage())) {
    db->sync_schema();
}

};
