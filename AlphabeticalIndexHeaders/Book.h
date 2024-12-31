#pragma once

#include "D:\VSCodeProjects\ThirdLaboratoryWorkChapterTwo\HashFunction.h"
#include "HashTable.h"
#include "Word.h"
#include "MutableSegmentedDeque.h"
#include "DynamicArray.h"


class Book {
private:
    SharedPtr<HashTable<Word>> hashTable;
    SharedPtr<MutableSegmentedDeque<SharedPtr<Word>>> wordsDeque;

public:
    Book(const SharedPtr<HashTable<Word>>& hashTable, const SharedPtr<MutableSegmentedDeque<SharedPtr<Word>>>& wordsDeque)
    : hashTable(hashTable), wordsDeque(wordsDeque) { }

    SharedPtr<DynamicArray<int>> getPageNumbers(const std::string& word) const {
        return hashTable->find(word)->getPageNumbers();
    }

    SharedPtr<Word> getWord(int index) const {
        return wordsDeque->get(index);
    }   

    int getWordsQuantity() const {
        return wordsDeque->getLength();
    }
};
