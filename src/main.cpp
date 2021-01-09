// Copyright 2021 Kuznetsov Konstantin

#include <iostream>

#include "db/db_manager.h"

int main(int argc, char *argv[]) {
    auto db = fundex::DBManager::getDatabase();
    return 0;
}
