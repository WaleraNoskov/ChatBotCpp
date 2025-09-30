#include "TaskListService.h"

TaskListService::TaskListService(const TaskListRepository &repository) : _taskListRepository(repository) {
}

std::vector<TaskList> TaskListService::getAll(const int pageNum,
                                              const int pageSize,
                                              const std::string &NameFilter,
                                              std::optional<TaskStatus> status) const {
    return _taskListRepository.getAll(pageNum, pageSize, NameFilter);
}

std::optional<TaskList> TaskListService::getById(const int id) const {
    return _taskListRepository.getById(id);
}

bool TaskListService::add(const TaskList &list) const {
    return _taskListRepository.add(list);
}

bool TaskListService::edit(const TaskList &list) const {
    return _taskListRepository.edit(list);
}

bool TaskListService::remove(const int id) const {
    return _taskListRepository.remove(id);
}
