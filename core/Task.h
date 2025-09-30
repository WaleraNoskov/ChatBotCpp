#pragma once
#include <string>
#include "TaskStatus.h"

class Task {
private:
    int id;
    std::string name;
    std::string description;
    TaskStatus status;

public:
    Task(int id,
         const std::string &name,
         const std::string &description,
         TaskStatus status);

    // Getters
    [[nodiscard]] int getId() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::string &getDescription() const;

    [[nodiscard]] TaskStatus getStatus() const;

    // Setters
    void setId(int newId);

    void setName(const std::string &newName);

    void setDescription(const std::string &newDescription);

    void setStatus(TaskStatus newStatus);
};
