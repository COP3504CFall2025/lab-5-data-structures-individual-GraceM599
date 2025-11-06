#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() {
        curr_size_ =0;
        capacity_ =1;
        array_ = nullptr;
    }
    explicit ABQ(const size_t capacity) {
        curr_size_ =0;
        capacity_ = capacity;
        array_ = new T[capacity_];
    }
    ABQ(const ABQ& other) {
        curr_size_ = other.getSize();
        capacity_ = other.getMaxCapacity();
        array_ = new T[capacity_];
        for (int i=0; i<curr_size_; ++i) {
            array_[i] = other.getData()[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }
        curr_size_ = rhs.getSize();
        capacity_ = rhs.getMaxCapacity();
        delete[] array_;
        array_ = new T[capacity_];
        for (int i=0; i<curr_size_; ++i) {
            array_[i] = rhs.getData()[i];
        }
        return *this;
    }
    ABQ(ABQ&& other) noexcept {
        curr_size_ = other.getSize();
        capacity_ = other.getMaxCapacity();
        array_ = other.getData();
        other.data_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_= 0;

    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        else {
            capacity_ = rhs.getMaxCapacity();
            curr_size_= rhs.getSize();
            delete[] array_;
            array_ = rhs.getData();
            rhs.array_ = nullptr;
            rhs.curr_size_ = 0;
            rhs.capacity_ = 0;
        }
        return *this;
    }

    ~ABQ() noexcept override {
        curr_size_ = 0;
        capacity_ = 0;
        delete[] array_;
        array_ = nullptr;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return curr_size_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override
    {
        if (capacity_ <= curr_size_) {
            T* temp = new T[capacity_*scale_factor_];
            for (int i=0; i<curr_size_; ++i) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;

        }
        array_[curr_size_] = data;
        curr_size_ +=1;
    }

    // Access
    T peek() const override {
        return array_[curr_size_];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty ABS");
        }
        T temp = array_[0];
        for (int i=1; i<curr_size_; ++i) {
            array_[i-1] = array_[i];
        }
        curr_size_ -=1;
        return temp;
    }

};
