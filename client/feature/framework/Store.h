#pragma once
#include <functional>
#include <vector>
#include <variant>

template <typename State, typename Action>
class Store {
private:
    State state_;
    std::function<State(const State&, const Action&)> reducer_;
    std::vector<std::function<void()>> subscribers_;

public:
    Store(State initial, std::function<State(const State&, const Action&)> reducer)
        : state_(std::move(initial)), reducer_(std::move(reducer)) {}

    State GetState() const { return state_; }

    void Dispatch(const Action& action) {
        state_ = reducer_(state_, action);
        for (auto& sub : subscribers_) sub();
    }

    void Subscribe(std::function<void()> callback) {
        subscribers_.push_back(std::move(callback));
    }
};