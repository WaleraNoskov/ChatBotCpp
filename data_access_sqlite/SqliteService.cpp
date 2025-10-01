#include "SqliteService.h"

#include <iostream>
#include <ostream>
#include <sqlite3.h>

void SqliteService::initialize() {
    if (auto result = sqlite3_open(":memory:", &database); result != SQLITE_OK) {
        std::cerr << "Can't open database" << std::endl;
        throw std::runtime_error("Can't open database");
    }

    const auto createTaskTable = R"(
        CREATE TABLE tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            status INTEGER NOT NULL,
            task_list_id INTEGER NOT NULL,
            FOREIGN KEY (task_list_id) REFERENCES task_list(id) ON DELETE CASCADE
        );
    )";
    if (sqlite3_exec(database, createTaskTable, nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cerr << "Error creating tasks table: " << sqlite3_errmsg(database) << std::endl;
        throw std::runtime_error("Error creating tasks table");
    }

    const auto createListTable = R"(
        CREATE TABLE task_lists (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
        );
    )";
    if (sqlite3_exec(database, createListTable, nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cerr << "Error creating taskLists table: " << sqlite3_errmsg(database) << std::endl;
        throw std::runtime_error("Error creating taskLists table");
    }
}

sqlite3 *SqliteService::getDatabase() const {
    return database;
}
