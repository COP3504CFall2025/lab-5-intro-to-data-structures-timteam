#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity;
    size_t currsize;
    T* array;
    static constexpr size_t scaleFactor = 2;
    //Sorry Link I do not like having underscores after my variables :/
public:

    // Constructors + Big 5
    ABQ() : capacity(1), currsize(0) {
    array = new T[1];
    }

    explicit ABQ(const size_t cap) : capacity(cap), currsize(0) {
    array = new T[capacity];
    }

    ABQ(const ABQ& other) : capacity(other.capacity), currsize(other.currsize) {
    array = new T[capacity];
        for(size_t i = 0; i < currsize; i++) {
            array[i] = other.array[i];
        }
    }

    ABQ& operator=(const ABQ& rhs) {
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

    ABQ(ABQ&& other) noexcept
        :capacity(other.capacity), currsize(other.currsize), array(other.array) {
        other.array = nullptr;
        other.capacity = 0;
        other.currsize = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
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

    ~ABQ() noexcept override {

    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override{
    return currsize;
    }

    [[nodiscard]] size_t getMaxCapacity() const noexcept{
    return capacity;
    }

    [[nodiscard]] T* getData() const noexcept{
    return array;
    }

    // Insertion
    void enqueue(const T& data) override {
        if(currsize >= capacity) {
            size_t newCap = capacity * scaleFactor;
            T* newArray = new T[newCap];
            for(size_t i = 0; i < currsize; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            capacity = newCap;
        }
        array[currsize] = data;
        currsize++;
    }

    // Access
    T peek() const override{
    if(currsize == 0){
    throw std::runtime_error("Empty");
    }

    return array[0];
    }

    // Deletion
    T dequeue() override {
        if (currsize == 0) throw std::runtime_error("Empty");
        T value = array[0];
        for (size_t i = 1; i < currsize; i++) {
            array[i - 1] = array[i];
        }
        currsize--;
        return value;
    }

};
