#include "DynamicArray.h"
#include <iostream>
template <typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), capacity(0), size(0) {}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
void DynamicArray<T>::push_back(const T& element) {
    if (size == capacity) {
        resize((capacity == 0) ? 1 : capacity * 2);
    }
    data[size++] = element;
}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
void DynamicArray<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
T& DynamicArray<T>::at(int index) {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::at(int index) const {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}
