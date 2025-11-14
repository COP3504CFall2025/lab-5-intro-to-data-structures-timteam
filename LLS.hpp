#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override{
        list.addHead(item);
    }

    // Deletion
    T pop() override{
    if(list.getHead() == nullptr){
            throw std::runtime_error("Empty");
        }
        
        T value = list.getTail()->data;
        list.removeTail();
        return value;
    }

    // Access
    T peek() const override{
         if(list.getHead() == nullptr){
            throw std::runtime_error("Empty");
        }

        return list.getTail()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }
};