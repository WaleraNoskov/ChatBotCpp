#pragma once
#include <string>
#include <variant>

#include "client/feature/framework/Action.h"

struct Refresh final : Action {
    int pageNum;
    int pageSize;
    std::string nameFilter;

    explicit Refresh(const int pageNum, const int pageSize, const std::string &nameFilter)
        : pageNum(pageNum),
          pageSize(pageSize),
          nameFilter(std::move(nameFilter)) {
    }
};

struct Add final : Action {
    std::string name;

    explicit Add(const std::string &name) : name(name) {
    }
};

struct Edit final : Action {
    int id;
    std::string name;

    explicit Edit(const int id, const std::string &name) : id(id), name(std::move(name)) {
    }
};

struct Remove final : Action {
    int id;

    explicit Remove(const int id) : id(id) {
    }
};

using ListsFeatureAction = std::variant<Refresh, Add, Edit, Remove>;
