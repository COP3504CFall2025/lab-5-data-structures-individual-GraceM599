#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;

    }
    explicit ABDQ(std::size_t capacity) {
        data_ = nullptr;
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }
    ABDQ(const ABDQ& other) {
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        data_ = new T[capacity_];
        front_ = other.getFront();
        back_ = size_;
        for (int i=0; i<size_; ++i ) {
            data_[(front_ + i) % size_] = other.front();
            front_ = (front_ +1)%size_;
            other.setFront(front_);
        }

    }
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        data_ = other.getData();
        front_ = other.getFront();
        back_ = other.getBack();
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this== &other) {
            return *this;
        }
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        data_ = new T[capacity_];
        front_ = other.getFront();
        back_ = size_;
        for (int i=0; i<size_; ++i ) {
            data_[(front_ + i) % size_] = other.front();
            front_ = (front_ +1)%size_;
            other.setFront(front_);
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (&other==this) {
            return *this;
        }
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        data_ = other.getData();
        front_ = other.getFront();
        back_ = other.getBack();
        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;

    }

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;
    std::size_t getCapacity() const noexcept;
    T* getData() const noexcept {
        return data_;
    }
    std::size_t getFront() const noexcept {
        return front_;
    }
    std::size_t getBack() const noexcept {
        return back_;
    }

    void setFront(std::size_t index) {
        front_ = index;
    }


};
