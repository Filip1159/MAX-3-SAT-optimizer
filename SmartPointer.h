#pragma once
#include "RefCounter.h"

template<typename T> class SmartPointer {
public:
    explicit SmartPointer(T* pointer);
    SmartPointer(const SmartPointer &other);
    ~SmartPointer();
    T* getValue() const;
    T& operator*();
    T* operator->();
    SmartPointer<T>& operator=(const SmartPointer<T> &other);
private:
    T* pointer;
    RefCounter* counter;
};

template<typename T> SmartPointer<T>::SmartPointer(T* pointer) {
    this->pointer = pointer;
    counter = new RefCounter();
    counter->add();
}

template<typename T> SmartPointer<T>::SmartPointer(const SmartPointer &other) {
    pointer = other.pointer;
    counter = other.counter;
    counter->add();
}

template<typename T> SmartPointer<T>::~SmartPointer() {
    if (counter->dec() == 0) {
        delete pointer;
        delete counter;
    }
}

template<typename T> T* SmartPointer<T>::getValue() const {
    return pointer;
}

template<typename T> T& SmartPointer<T>::operator*() {
    return *pointer;
}

template<typename T> T* SmartPointer<T>::operator->() {
    return pointer;
}

template<typename T> SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T> &other) {
    if (counter->dec() == 0) {
        delete pointer;
        delete counter;
    }
    pointer = other.pointer;
    counter = other.counter;
    counter->add();
    return *this;
}
