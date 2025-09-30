#include "Task.h"

#include <stdexcept>

Task::Task(int id, const std::string &name, const std::string &description, TaskStatus status)
    : id(id), name(name), description(description), status(status) {
    if (name.empty())
        throw std::invalid_argument("Name cannot be empty");
}

int Task::getId() const {
    return id;
}

const std::string& Task::getName() const {
    return name;
}

const std::string& Task::getDescription() const {
    return description;
}

TaskStatus Task::getStatus() const {
    return status;
}

void Task::setId(const int newId) {
    this->id = newId;
}


void Task::setName(const std::string& newName) {
    if (newName.empty())
        throw std::invalid_argument("Name cannot be empty");

    this->name = newName;
}

void Task::setDescription(const std::string& newDescription) {
    this->description = newDescription;
}

void Task::setStatus(TaskStatus newStatus) {
    this->status = newStatus;
}
