#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = nullptr;
    }
    explicit ABS(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity];
    }
    ABS(const ABS& other) {
        //copy constructor
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = new T[capacity_];
        for (int i=0; i<curr_size_; ++i) {
            array_[i] = other.getData()[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        //copy assignment operator
        if (this == &rhs) {
            return *this;
        }
        capacity_ = rhs.getMaxCapacity();
        curr_size_ = rhs.getSize();
        delete[] array_;
        array_ = new T[capacity_];
        for (int i=0; i<curr_size_; ++i) {
            // [] dereferences the pointer and gives a value not pointer
            array_[i] = rhs.getData()[i];
        }
        return *this;
    }
    ABS(ABS&& other) noexcept {
        //move constructor
        capacity_ = other.getMaxCapacity();
        curr_size_= other.getSize();
        array_ = other.getData();
        other.setData(nullptr);
        other.curr_size_ = 0;
        other.capacity_= 0;
        //do i not have to set things to nullptr??? no setters...

    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        capacity_ = rhs.getMaxCapacity();
        curr_size_= rhs.getSize();
        delete[] array_;
        array_ = rhs.getData();
        rhs.setData(nullptr);
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;

        //do i return the pointer or the object?
        return *this;
    }
    ~ABS() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }
    void setData(T* t) {
        array_  =t;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (capacity_ ==0 || array_ ==nullptr) {
            array_ = new T[1];
            capacity_ =1;
        }
        else if (curr_size_ >= capacity_) {
            capacity_ *= scale_factor_;
            T* temp = array_;
            array_ = new T[capacity_];
            for (int i=0; i<curr_size_; ++i) {
                array_[i] = temp[i];
            }
            delete[] temp;

        }
        array_[curr_size_] = data;
        curr_size_ +=1;
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty ABS");
        }
        return array_[curr_size_-1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty ABS");
        }

        T temp = array_[curr_size_-1];
        curr_size_ -=1;
        if (2* curr_size_ < capacity_) {
            capacity_ = std::max<int>(1, capacity_ / 2);
            T* sec = new T[capacity_];

            for (int i = 0; i < curr_size_; ++i) {
                sec[i] = array_[i];
            }

            delete[] array_;
            array_ = sec;
        }

        return temp;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
