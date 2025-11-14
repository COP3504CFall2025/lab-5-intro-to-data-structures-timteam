#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ()= default;

    // Insertion
    void enqueue(const T& item) override{
        list.addTail();
    }

    // Deletion
    T dequeue() override{
        list.removeTail();
        return list;
    }

    // Access
    T peek() const override{
        return list.getTail();
        
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return list.count;
    }

};