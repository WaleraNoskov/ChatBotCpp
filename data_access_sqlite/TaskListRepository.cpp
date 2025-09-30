#include "TaskListRepository.h"

#include <iostream>
#include <memory>
#include <ostream>

TaskListRepository::TaskListRepository(SqliteService &service)
    : sqliteService(service) {
}

std::vector<TaskList> TaskListRepository::getAll(const int pageNum,
                                                 const int pageSize,
                                                 const std::string &nameFilter) const {
    std::vector<TaskList> result;

    const auto sql = R"(
        SELECT id, name
        FROM task_lists
        WHERE name LIKE ?
        LIMIT ? OFFSET ? ;
    )";

    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(sqliteService.getDatabase(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "failed to get lists from db: "
                << sqlite3_errmsg(sqliteService.getDatabase()) << std::endl;
        return result;
    }

    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmtGuard(stmt, sqlite3_finalize);

    const auto likePattern = "%" + nameFilter + "%";
    sqlite3_bind_text(stmt, 1, likePattern.c_str(), -1, SQLITE_TRANSIENT);
    const int offset = std::max(0, pageNum) * std::max(1, pageSize);
    sqlite3_bind_int(stmt, 2, pageSize);
    sqlite3_bind_int(stmt, 3, offset);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const auto name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

        result.emplace_back(id, name ? std::string(name) : std::string());
    }

    return result;
}

bool TaskListRepository::add(const TaskList& list) const {
    const auto sql = "INSERT INTO task_lists (name) VALUES (?);";
    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(sqliteService.getDatabase(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "failed to insert task list" << std::endl;
        return false;
    }

    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmtGuard(stmt, sqlite3_finalize);

    sqlite3_bind_text(stmt, 1, list.getName().c_str(), -1, SQLITE_TRANSIENT);

    return sqlite3_step(stmt) == SQLITE_DONE;
}

bool TaskListRepository::edit(const TaskList &list) const {
    const auto sql = R"(
        update task_lists
        set name = ?
        where id = ? ;
    )";
    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(sqliteService.getDatabase(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "failed to edit task list of id " << list.getId() << std::endl;
        return false;
    }

    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmtGuard(stmt, sqlite3_finalize);

    sqlite3_bind_text(stmt, 1, list.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, list.getId());

    return sqlite3_step(stmt) == SQLITE_DONE;
}

bool TaskListRepository::remove(const int id) const {
    const auto sql = R"(
        delete from task_lists
        where id = ? ;
    )";
    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(sqliteService.getDatabase(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "failed to remove task list by id " << id << std::endl;
        return false;
    }

    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmtGuard(stmt, sqlite3_finalize);

    sqlite3_bind_int(stmt, 1, id);

    return sqlite3_step(stmt) == SQLITE_DONE;
}

std::optional<TaskList> TaskListRepository::getById(const int id) const {
    const auto sql = R"(
        select *
        from task_lists
        where id = ? ;
    )";

    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(sqliteService.getDatabase(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "failed to select task list by id:" << sqlite3_errmsg(sqliteService.getDatabase()) << std::endl;
        return std::nullopt;
    }

    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmtGuard(stmt, sqlite3_finalize);

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int gotId = sqlite3_column_int(stmt, 0);
        const auto gotName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        return TaskList(gotId, gotName);
    }

    return std::nullopt;
}

