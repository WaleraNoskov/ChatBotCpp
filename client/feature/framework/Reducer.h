#pragma once
#include <functional>

template<typename State, typename Action>
using Reducer = std::function<State(const State &, const Action &)>;
