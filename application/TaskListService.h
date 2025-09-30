#pragma once
#include "data_access_sqlite/TaskListRepository.h"

class TaskListService {
    TaskListRepository _taskListRepository;

public:
    explicit TaskListService(const TaskListRepository &repository);

    [[nodiscard]] std::vector<TaskList> getAll(int pageNum,
                                               int pageSize,
                                               const std::string &NameFilter,
                                               std::optional<TaskStatus> status) const;

    [[nodiscard]] std::optional<TaskList> getById(int id) const;

    [[nodiscard]] bool remove(int id) const;

    [[nodiscard]] bool edit(const TaskList &list) const;

    [[nodiscard]] bool add(const TaskList &list) const;
};
