// Copyright 2021 Kuznetsov Konstantin

#include "cli/flags.h"
#include "db/utilities.h"

namespace fundex {

/**
 * Callback function for `--list-cat` flag.
 *
 */
static void list_categories() {
    print_categories();
}

void setup_flags(CLI::App *app) {
    app->add_flag_callback("--list_cat", list_categories,
            "List all Categories");
}

};  // namespace fundex
