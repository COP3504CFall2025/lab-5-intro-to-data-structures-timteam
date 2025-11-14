
/*
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* array;                 // underlying dynamic array
    std::size_t capacity;    // total allocated capacity
    std::size_t currsize;        // number of stored elements
    //std::size_t front;       // index of front element
    //std::size_t back;        // index after the last element (circular)

    static constexpr std::size_t scaleFactor = 2;

public:
    // Big 5
    ABDQ()
    : capacity(1), currsize(0), array(new T[capacity]){}

    explicit ABDQ(std::size_t capacity)
    : capacity(capacity), currsize(0),  array(new T[capacity]){}

   ABDQ(const ABDQ& other)
   {
        capacity = other.capacity;
        currsize = other.currsize;
        array = new T[other.capacity];
        for(size_t i = 0; i < currsize; i++){
        array[i] = other.array[i];
        }
   }


   ABDQ& operator=(const ABDQ& rhs) {
   if(this == &rhs){
        return *this;
       }
       delete[] array;
       capacity = rhs.capacity;
       currsize = rhs.currsize;
       array = new T[rhs.capacity];
       for(size_t i = 0; i < currsize; i++) {
           array[i] = rhs.array[i];
       }
       
       return *this;
   }

   ABDQ(ABDQ&& other) noexcept
       :capacity(other.capacity), currsize(other.currsize), array(other.array) {
       other.array = nullptr;
       other.capacity = 0;
       other.currsize = 0;
   }

   ABDQ& operator=(ABDQ&& rhs) noexcept {
   if(this == &rhs){
       return *this;
   }
       delete[] array;
       array = rhs.array;
       capacity = rhs.capacity;
       currsize = rhs.currsize;
       rhs.array = nullptr;
       rhs.capacity = 0;
       rhs.currsize = 0;
       return *this;
   }

   ~ABDQ() noexcept override {
   delete[] array;
   array = nullptr;

   }
    // Insertion
    void pushFront(const T& item) override{

        if(currsize >= capacity){
            size_t newCap = capacity * scaleFactor;
            T* newArr = new T[newCap];

            for(size_t i = 0; i < currsize; i++){
             newArr[i] = array[i];
            }

            delete[] array;
            array = newArr;
            newArr = nullptr;
            capacity = newCap;
        }
        
        if(currsize == 0){
            array[0] = item;
            return;
        }

        for(int i = currsize - 1; i >= 0; i--){
            array[i +1 ] = array[i];
        }

        

        array[0] = item;
         currsize++;
        }
    

    void pushBack(const T& item) override{
    if(currsize >= capacity){
        size_t newCap = capacity * scaleFactor;
        T* newArr = new T[newCap];

        for(size_t i = 0; i < currsize; i++){
            newArr[i] = array[i];
        }

        delete[] array;
        array = newArr;
        newArr = nullptr;
        capacity = newCap;
    }

    array[currsize] = item;
    currsize++;
}
    
    // Deletion
    T popFront() override{

        if(currsize == 0){
            throw std::runtime_error("Empty array");
        }
        T temp = array[0];

	    for(size_t i = 1; i < currsize; i++){
            array[i-1] = array[i];
	    }
	    currsize--;

         if(currsize <= capacity / 4){
            capacity /= 2;
        }

        return temp;

        }

    T popBack() override{
	    if(currsize == 0){
            throw std::runtime_error("Empty array");
        }

	    T value = array[currsize - 1];

         currsize--;

	    if(currsize <= capacity / 4){
            capacity /= 2;
        }

	    return value;
    }

    // Access
    const T& front() const override{
        if(currsize ==0){
            throw std::runtime_error("Empty");
        }
        return array[0];
    }
    const T& back() const override{
        if(currsize ==0){
            throw std::runtime_error("Empty");
        }
        return array[currsize - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override{
    return currsize;
    }

    
};
*/
//#pragma once

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
        capacity_ = 1;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[other.capacity_];
        front_ = other.front_;
        back_ = other.back_;
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = other.data_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        delete[] data_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        delete[] data_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        front_ = 0;
        back_ = 0;
        capacity_ = 0;
        size_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* temp = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[i];
            }
            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }
        for (int i = size_-1; i >= 0; i--) {
            data_[i+1] = data_[i];
        }
        data_[0] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* temp = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[i];
            }
            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }
        data_[size_] = item;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("ABS dequeue fail");
        }
        T returnVal = data_[0];
        for (size_t i = 1; i < size_; i++) {
            data_[i-1] = data_[i];
        }
        size_--;
        if (size_ <= capacity_ / 4) {
            capacity_ /= 2;
        }
        return returnVal;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("ABS pop fail");
        }
        T temp = data_[size_ - 1];
        size_--;

        if (size_ <= capacity_ / 4) {
            capacity_ /= 2;
        }
        return temp;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("ABS peek fail");
        }
        return data_[0];
    }
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("ABS peek fail");
        }
        return data_[size_ - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};