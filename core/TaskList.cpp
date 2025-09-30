#include "TaskList.h"

#include <algorithm>
#include <stdexcept>

void TaskList::addTask(const Task &task) {
    tasks.push_back(task);
}

void TaskList::removeTask(const Task &task) {
    const auto iterator = std::ranges::find_if(tasks, [&](const Task &t) {
        return task.getId() == t.getId();
    });

    tasks.erase(iterator);
}

TaskList::TaskList(const int id, const std::string &name) {
    this->id = id;
    this->name = name;
}

int TaskList::getId() const {
    return id;
}

const std::string &TaskList::getName() const {
    return name;
}

const std::vector<Task> &TaskList::getTasks() const {
    return tasks;
}

void TaskList::setId(int newId) {
    if (newId < 0)
        throw std::invalid_argument("Invalid Id");

    this->id = newId;
}

void TaskList::setName(const std::string &newName) {
    if (newName.empty())
        throw std::invalid_argument("Name cannot be empty");

    this->name = newName;
}
