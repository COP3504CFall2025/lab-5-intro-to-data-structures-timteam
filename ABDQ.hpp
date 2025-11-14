#pragma once

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
    std::size_t front;       // index of front element
    std::size_t back;        // index after the last element (circular)

    static constexpr std::size_t scaleFactor = 2;

public:
    // Big 5
    ABDQ()
    : capacity(1), currsize(0), front(0), back(0), data(new T[0]){}
    explicit ABDQ(std::size_t capacity)
    : capacity(capacity), currsize(0), front(0), back(capacity-1), array(new T[capacity]{}

   ABDQ(const ABDQ& other):capacity(other.capacity), currsize(other.currsize){
   array = new T[capacity];
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
       array = new T[capacity];
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

   ~ABDQ() noexcept {
   delete[] array;
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
            capacity = newCap;
        }

        for(size_t i = 0; i < capacity; i++){
        T temp = array[i];
        array[i + 1] = array[i];
        }

        arr[0] = data;
         currsize++;
        }
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
        capacity = newCap;
    }

    arr[currsize] = data;
    currsize++;
}
    }

    // Deletion
    T popFront() override{
    if(currsize == 0){
    throw std::runtime_error("Empty array");
    }
	for(size_t i = 0; i < currsize; i++){

	}
	currsize--;

    }
    T popBack() override{
	if(currsize == 0){
    throw std::runtime_error("Empty array");
    }

	currsize--;
    }

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override{
    return currsize;
    }


};
