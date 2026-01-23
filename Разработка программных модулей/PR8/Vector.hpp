#pragma once
#include <cstddef>

template<typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(size_t n, const T& value) : size_(n), capacity_(n) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    Vector(std::initializer_list<T> init) : size_(init.size()), capacity_(init.size()) {
        data_ = new T[capacity_];
        size_t i = 0;
        for (const auto& val : init) {
            data_[i++] = val;
        }
    }

    ~Vector() {
        delete[] data_;
    }

    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;

    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            resize(new_cap);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }
};