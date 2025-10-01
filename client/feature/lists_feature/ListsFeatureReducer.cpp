#include "ListsFeatureReducer.h"

#pragma once
#include "ListsFeatureAcions.h"
#include "ListsFeatureState.h"
#include "application/TaskListService.h"

ListsFeatureState ListsFeatureReducer(const ListsFeatureState &state,
                                      const ListsFeatureAction &action,
                                      const TaskListService &service) {
    return std::visit([&](auto &&concreteAction) -> ListsFeatureState {
        using T = std::decay_t<decltype(concreteAction)>;
        auto newState = state;
        newState.lastError.clear();

        if constexpr (std::is_same_v<T, Refresh>) {
            const auto newLists = service.getAll(concreteAction.pageNum,
                                                 concreteAction.pageSize,
                                                 concreteAction.nameFilter,
                                                 std::nullopt);
            newState.lists = std::move(newLists);
            return newState;
        } else if constexpr (std::is_same_v<T, Add>) {
            auto result = service.add({0, concreteAction.name});
            if (!result)
                newState.lastError += "Failed to add list '" + concreteAction.name + "'";

            return newState;
        } else if constexpr (std::is_same_v<T, Edit>) {
            auto result = service.edit({concreteAction.id, concreteAction.name});
            if (!result)
                newState.lastError += "Failed to edit list with id " + std::to_string(concreteAction.id);

            return newState;
        } else if constexpr (std::is_same_v<T, Remove>) {
            auto result = service.remove(concreteAction.id);
            if (!result)
                newState.lastError += "Failed to remove list with id " + std::to_string(concreteAction.id);

            return newState;
        }
    }, action);
}