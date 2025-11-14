#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
private:
    size_t capacity;
    size_t currsize;
    T* arr;
    static constexpr size_t scaleFactor = 2;
public:
    // Big 5 + Parameterized Constructor
    ABS()
    :capacity(1), currsize(0){
    arr = new T[1];
    }

    explicit ABS(const size_t capacity)
    :capacity(capacity), currsize(0){
    arr = new T[capacity];

    }

    ABS(const ABS& other):capacity(other.capacity), currsize(other.currsize){
	arr = new T[capacity];
		for(size_t i = 0; i < currsize; i++){
		arr[i] = other.arr[i];
		}

	}

    ABS& operator=(const ABS& rhs){
	if(this == &rhs){
	return *this;
	}

	delete[] arr;
	capacity = rhs.capacity;
	currsize = rhs.currsize;

	arr = new T[capacity];
	for(size_t i = 0; i < currsize; i++) {
	arr[i] = rhs.arr[i];
	}
	return *this;
	//Cited from dyanmic array lab
	}

    ABS(ABS&& other) noexcept
    :capacity(other.capacity), currsize(other.currsize), arr(other.arr) {
    other.arr = nullptr;
    other.capacity = 0;
    other.currsize = 0;
	//Cited from dyanmic array lab
	}

    ABS& operator=(ABS&& rhs) noexcept{
	if (this == &rhs) {
        return *this;
    }
		delete[] arr;
        arr = rhs.arr;
        capacity = rhs.capacity;
        currsize = rhs.currsize;
        rhs.arr = nullptr;
        rhs.capacity = 0;
        rhs.currsize = 0;

		return *this;
		//Cited from Dynamic array lab
	}

    ~ABS() noexcept{
	delete[] arr;
	};

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{
    return currsize;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
    return capacity;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{
    return arr;
    }
    // Push item onto the stack
    void push(const T& data) override{

    if(currsize >= capacity){
        size_t newCap = capacity * scaleFactor;
        T* newArr = new T[newCap];

        for(size_t i = 0; i < currsize; i++){
         newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
		capacity = newCap;
    }

    arr[currsize] = data;
	 currsize++;
    }

    T peek() const override{
		if(currsize == 0){
		throw std::runtime_error("Empty");
		}

		return arr[currsize - 1];
	}

    T pop() override{
	if(currsize == 0){
    throw std::runtime_error("Empty array");
    }

	currsize--;

	T value = arr[currsize];

		if(currsize <= capacity / 4){
            size_t newCap = capacity / 2;
            if(newCap < 1){
             newCap = 1;
              }

        T* newArr = new T[newCap];

        for(size_t i = 0; i < currsize; i++){
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }

		return value;
	}



};
