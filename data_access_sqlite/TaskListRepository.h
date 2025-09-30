#pragma once
#include <optional>
#include <sqlite3.h>
#include <vector>

#include "SqliteService.h"
#include "../core/TaskList.h"

class TaskListRepository {
    SqliteService &sqliteService;

public:
    explicit TaskListRepository(SqliteService &service);

    [[nodiscard]] std::vector<TaskList> getAll(int pageNum, int pageSize, const std::string &nameFilter) const;

    [[nodiscard]] bool add(const TaskList& list) const;

    [[nodiscard]] bool edit(const TaskList& list) const;

    [[nodiscard]] bool remove(int id) const;

    [[nodiscard]] std::optional<TaskList> getById(int id) const;
};
