#pragma once
#include <vector>

#include "core/TaskList.h"

struct ListsFeatureState {
    std::vector<TaskList> lists{};
    int selectedListId = -1;
    std::string lastError{};
};
