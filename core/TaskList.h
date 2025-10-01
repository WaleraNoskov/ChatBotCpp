#pragma once
#include <vector>
#include "Task.h"


class TaskList {
private:
    int id;
    std::string name;
    std::vector<Task> tasks;

public:
    TaskList(int id, const std::string &name);
    TaskList(int id, const std::string &name, const std::vector<Task> &tasks);

    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] const std::vector<Task>& getTasks() const;

    void setId(int newId);
    void setName(const std::string &newName);
    void addTask(const Task& task);
    void removeTask(const Task& task);
};