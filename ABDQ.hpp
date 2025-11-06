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
        data_ = new T[1];
        capacity_ = 1;
        size_ = 0;
        front_ = 0;
        back_ = 0;

    }
    explicit ABDQ(std::size_t capacity) {
        data_ = new T[capacity];
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
            data_[(front_ + i) % capacity_] = other.data_[(front_ + i) % capacity_];
        }

    }
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        data_ = other.getData();
        front_ = other.getFront();
        back_ = other.getBack();
        other.data_ = nullptr;
        other.size_=0;
        other.front_ = 0;
        other.back_ = 0;
        other.capacity_ =0;
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
            data_[(front_ + i) % capacity_] = other.getData()[(front_ + i) % capacity_];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (&other==this) {
            return *this;
        }
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        delete[] data_;
        data_ = other.getData();
        front_ = other.getFront();
        back_ = other.getBack();

        other.data_ = nullptr;
        other.size_=0;
        other.front_ = 0;
        other.back_ = 0;
        other.capacity_ =0;
        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;

    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ >= capacity_) {
            ensureCapacity();
            pushFront(item);
        }
        else {
            front_ = (front_ - 1 + capacity_) % capacity_;
            data_[front_] = item;
            size_++;
        }
    }
    void pushBack(const T& item) override {
        if (size_ >= capacity_) {
            ensureCapacity();
            pushBack(item);
        }
        else {
            data_[back_] = item;
            back_ = (back_+1) % capacity_;

            size_++;
        }
    }

    // Deletion
    T popFront() override {
        int t = front_;
        front_ = (front_ + 1) % capacity_;
        size_--;

        return data_[t];
    }
    T popBack() override {
        int t = back_;
        back_ = (back_-1 + capacity_) % capacity_;
        size_--;
        return data_[t];
    }
    void ensureCapacity() {

        T* temp = new T[capacity_*2];
        for (int i=0; i<size_; i++) {
            temp[i] = data_[(front_ + i) % capacity_];
        }
        capacity_ *=2;
        front_ = 0;
        back_ = size_;
        delete[] data_;
        data_ = temp;
    }
    // Access
    const T& front() const override {
        return data_[front_];
    }
    const T& back() const override {
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }
    std::size_t getCapacity() const noexcept {
        return capacity_;
    }
    T* getData() const noexcept {
        return data_;
    }
    std::size_t getFront() const noexcept {
        return front_;
    }
    std::size_t getBack() const noexcept {
        return back_;
    }




};
