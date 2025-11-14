
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
    std::size_t frontt;       // index of front element
    std::size_t backk;        // index after the last element (circular)

    static constexpr std::size_t scaleFactor = 2;

public:
    // Big 5
    ABDQ()
    : capacity(1), currsize(0), array(new T[capacity]), frontt(0),backk(1){}

    explicit ABDQ(std::size_t capacity)
    : capacity(capacity), currsize(0),  array(new T[capacity]),frontt(0), backk(currsize-1){}

   ABDQ(const ABDQ& other)
   {
        capacity = other.capacity;
        currsize = other.currsize;
        frontt = other.frontt;
        backk = other.backk;
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
       frontt = rhs.frontt;
       backk = rhs.backk;
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
       other.frontt = 0;
       other.backk = 0;
   }

   ABDQ& operator=(ABDQ&& rhs) noexcept {
   if(this == &rhs){
       return *this;
   }
       delete[] array;
       array = rhs.array;
       capacity = rhs.capacity;
       currsize = rhs.currsize;
       frontt = rhs.frontt;
       backk = rhs.backk;
       rhs.array = nullptr;
       rhs.capacity = 0;
       rhs.currsize = 0;
       rhs.backk = 0;
       rhs.frontt = 0;
       return *this;
   }

   ~ABDQ() noexcept override {
   delete[] array;
   array = nullptr;
    capacity = 0;
    currsize = 0;
    frontt = 0;
    backk = 0;
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