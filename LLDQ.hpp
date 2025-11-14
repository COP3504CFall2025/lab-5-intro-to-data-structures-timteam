#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override{
        list.addHead(item);
    }

    void pushBack(const T& item) override{
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override{
        if(list.getHead() == nullptr){
            throw std::runtime_error("Empty");
        }
        
        T value = list.getHead()->data;
        list.removeHead();
        return value;
    }
    T popBack() override{
        if(list.getHead() == nullptr){
            throw std::runtime_error("Empty");
        }
        
        T value = list.getTail()->data;
        list.removeTail();
        return value;
    }

    // Element Accessors
    const T& front() const override{
        return list.getHead()->data;
    }
    const T& back() const override{
        return list.getTalk()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }
};






