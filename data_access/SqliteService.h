#pragma once
#include <sqlite3.h>

class SqliteService {
    sqlite3 *database{};

public:
    void initialize();
    sqlite3* getDatabase() const;
};
