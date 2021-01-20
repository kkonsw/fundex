// Copyright 2021 Kuznetsov Konstantin

/**
 * @file utilities.h
 * This file contains utility functions.
 */

#ifndef SRC_DB_UTILITIES_H_
#define SRC_DB_UTILITIES_H_

#include <iostream>
#include <vector>

#include "db/database.h"

namespace fundex {

/** Prints all categories from database using libfort.
  * \param output Output stream, cout by default.
  */
void print_categories(std::ostream &output = std::cout);

/** Prints transactions using libfort.
  * \param transactions Transactions to print.
  * \param output Output stream, cout by default.
  */
void print_transactions(const std::vector<Transaction>& transactions,
        std::ostream &output = std::cout);

};  // namespace fundex

#endif  // SRC_DB_UTILITIES_H_
