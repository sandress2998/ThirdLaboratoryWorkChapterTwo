#pragma once

#include <iostream>
#include <stdexcept>
#include "Sequence.h"

/// Functionally complements ArraySequence

template <typename T>
class DynamicArray {
protected:
    int size;
    T* array = nullptr;
public:
    // конструктор для копирования массива
    DynamicArray(const T* arrayToCopy, int size): size(size) {
        std::cout << "THIS IS CREATING OF ARRAY OF SIZE = " << size << "\n";
        if (size < 0) throw std::out_of_range("Entered invalid size.\n");
        array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = arrayToCopy[i];
        }
    }
    // конструктор создания массива определенной длины
    DynamicArray(int size): size(size) {
        std::cout << "THIS IS CREATING OF ARRAY OF SIZE = " << size << "\n";
        if (size < 0) throw std::out_of_range("Entered invalid size.\n");
        std::cout << "size = " << size << "\n";
        array = new T[size];
    }

    // конструктор создания массива определенной длины
    DynamicArray(): size(0) {
        std::cout << "THIS IS CREATING OF ARRAY OF SIZE = " << size << "\n";
    }

    // конструктор копирования
    DynamicArray(const DynamicArray<T>& other): size(other.getSize()), array(new T[other.getSize()]) {
        std::cout << "THIS IS CREATING OF ARRAY OF SIZE = " << size << "\n";
        for (int i = 0; i < size; ++i) {
            set(i, other.get(i));
        }
    }

    DynamicArray(const Sequence<T>& other): size(other.getLength()), array(new T[other.getLength()]) {
        std::cout << "THIS IS CREATING OF ARRAY OF SIZE = " << size << "\n";
        for (int i = 0; i < size; ++i) {
            set(i, other.get(i));
        }
    }

    ~DynamicArray() {
        delete[] array;
    }

    T& operator[](int index) {
        if (index >= size || index < 0) throw std::out_of_range("The entered index is out of range.\n");
        return array[index];
    }

    const T& operator[](int index) const {
        if (index >= size || index < 0) throw std::out_of_range("The entered index is out of range.\n");
        return const_cast<T&>(array[index]);
    }

    // Переделано
    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        delete array;
        array = new T[other.getSize()];
        for (int i = 0; i < other.getSize(); ++i) {
            array[i] = other.get(i);
        }
        size = other.size;
        std::cout << "THIS IS CREATING OF ARRAY OF SIZE = " << size << "\n";
        return *this; // возвращаем обновленный *this как rvalue;
    }

    const T& get(int index) const { // возвращает rvalue
        if (index >= size || index < 0) throw std::out_of_range("The entered index is out of range.\n");
        return array[index];
    }

    int getSize() const {
        return size;
    }

    void set(int index, const T& value) {
        // исключение выбросит конструкция (*this)[index]
        (*this)[index] = value; // здесь все нормально, происходит стандартное присваивание. Т.е. value копируется в array[index]
    }

    void resize(int newSize) {
        if (newSize < 0) throw std::out_of_range("Entered invalid size.\n");
        T* helpArray = new T[newSize];
        int minSize = newSize < size ? newSize : size;
        for (int i = 0; i < minSize; ++i) {
            // TEST 13
            std::cout << "minSize = " << minSize << "\n";
            helpArray[i] = array[i];
        }
        if (size != 0) {
            delete[] array;
        }
        array = helpArray;
        size = newSize;
        if (size == 0) {
            delete[] array;
            array = nullptr;
        }
    }

    void append(const T& item) {
        // TEST 14
        std::cout << "test 14 " << size << '\n';
        resize(size + 1);
        array[size - 1] = item;
    }

    void prepend(const T& item) {
        T* helpArray = new T[size + 1];
        helpArray[0] = item;
        for (int i = 0; i < size; ++i) {
            helpArray[i + 1] = array[i];
        }
        delete[] array;
        array = helpArray;
        size = size + 1;
    }

    void insertAt(int index, const T& item) {
        if (index < 0 || index > size) throw std::out_of_range("Entered indices are out of range.\n");
        T* helpArray = new T[size + 1];
        int i = 0;
        for (; i < index; ++i) {
            helpArray[i] = array[i];
        }
        helpArray[i++] = item;
        for (; i < size + 1; ++i) {
            helpArray[i] = array[i - 1];
        }
        delete[] array;
        array = helpArray;
        size = size + 1;
    }

    int findIndex(const T& item) const {
        for (int i = 0; i < getSize(); ++i) {
            if (item == get(i)) {
                return i;
            }
        } 
        throw std::invalid_argument("Item wasn't found");
    }

    friend std::ostream& operator << (std::ostream& os, const DynamicArray<T>& value) {
        int i = 0;
        for (; i < value.getSize() - 1; ++i) {
            os << value[i] << " ";
        }
        os << value[i] << "\n";
        return os;
    }
};