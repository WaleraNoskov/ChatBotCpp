#pragma once
#include "ListsFeatureAcions.h"
#include "ListsFeatureState.h"
#include "application/TaskListService.h"

ListsFeatureState ListsFeatureReducer(const ListsFeatureState &state,
                                      const ListsFeatureAction &action,
                                      const TaskListService &service);
