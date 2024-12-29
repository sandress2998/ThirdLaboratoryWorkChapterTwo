#pragma once

#include <stdexcept>
#include "DynamicArray.h"
#include "SharedPtr.h"

template <typename T>
class HashTable {
private:
    int length;
    int (*hashFunction) (const std::string& str, int hashTableLength);
    SharedPtr<DynamicArray<SharedPtr<DynamicArray<SharedPtr<T>>>>> array;

public:
    HashTable(int length, int (*hashFunction) (const std::string& str, int hashTableLength)): length(length)
    , hashFunction(hashFunction) {
        array = makeShared<DynamicArray<SharedPtr<DynamicArray<SharedPtr<T>>>>>(length);
        for (int i = 0; i < length; ++i) {
            (*array)[i] = makeShared<DynamicArray<SharedPtr<T>>>(0);
        }
    }

    ~HashTable() = default;

    int getLength() const {
        return length;
    }

// МОЖЕТ БЫТЬ, СТОИТ ДОБАВИТЬ КОНЦЕПТЫ? 
    void append(const std::string& item) {
        int index = hashFunction(item, length);
        (*(this->array))[index]->append(makeShared<T>(item)); // ВОТ ЗДЕСЬ ЭТО МОЖЕТ ПОТРЕБОВАТЬСЯ
    }

    SharedPtr<T> find(const std::string& item) {
        T newElem(item);
        int index = hashFunction(item, length);
        SharedPtr<DynamicArray<SharedPtr<T>>> arrayOfIndex = (*(this->array))[index];
        for (int i = 0; i < arrayOfIndex->getSize(); ++i) {
            if (newElem == *(arrayOfIndex->get(i))) {
                return arrayOfIndex->get(i);
            }
        }
        throw std::invalid_argument("Element wasn't found");
    }

    void remove(const std::string item) {

    }
};