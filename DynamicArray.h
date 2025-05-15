#pragma once
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize(int newCapacity);

public:
    DynamicArray();
    ~DynamicArray();

    void push_back(const T& element);
    T& operator[](int index);
    int getSize() const;

    T& at(int index);
    const T& at(int index) const;


};

#include "DynamicArray.tpp" 


#endif // DYNAMIC_ARRAY_H

