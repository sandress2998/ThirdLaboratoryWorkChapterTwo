#pragma once

#include "DynamicArray.h"
#include <stdexcept>

template <typename T>
class HashTable {
private:
    int length;
    int (*hashFunction) (const std::string& str, int hashTableLength);
    DynamicArray<DynamicArray<T>*>* array;

public:
    HashTable(int length, int (*hashFunction) (const std::string& str, int hashTableLength)): length(length)
    , hashFunction(hashFunction) {
        array = new DynamicArray<DynamicArray<T>*>(length);
        for (int i = 0; i < length; ++i) {
            (*array)[i] = new DynamicArray<T>(0);
        }
    }

    ~HashTable() {
        for (int i = 0; i < length; ++i) {
            delete array->get(i);
        }
        delete array;
    }

    int getLength() const {
        return length;
    }

// МОЖЕТ БЫТЬ, СТОИТ ДОБАВИТЬ КОНЦЕПТЫ? 
    void append(const std::string& item) {
        int index = hashFunction(item, length);
        (*(this->array))[index]->append(T(item)); // ВОТ ЗДЕСЬ ЭТО МОЖЕТ ПОТРЕБОВАТЬСЯ
    }

    T& find(const std::string& item) {
        T newElem(item);
        int index = hashFunction(item, length);
        DynamicArray<T>* arrayOfIndex = (*(this->array))[index];
        for (int i = 0; i < arrayOfIndex->getSize(); ++i) {
            if (newElem == arrayOfIndex->get(i)) {
                return (*arrayOfIndex)[i];
            }
        }
        throw std::invalid_argument("Element wasn't found");
    }

    void remove(const std::string item) {

    }
};