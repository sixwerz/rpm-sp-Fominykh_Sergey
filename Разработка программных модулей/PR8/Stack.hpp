#pragma once
#include "Vector.hpp"

template<typename T>
class Stack {
private:
    Vector<T> data_;

public:
    void push(const T& value) {
        data_.push_back(value);
    }

    T& top() {
        return data_[data_.size() - 1];
    }

    const T& top() const {
        return data_[data_.size() - 1];
    }

    void pop() {
        data_.pop_back();
    }

    size_t size() const {
        return data_.size();
    }

    bool empty() const {
        return data_.empty();
    }
};