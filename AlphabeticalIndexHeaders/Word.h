#pragma once

#include <string>
#include <iostream>
#include "Line.h"
#include "MutableSegmentedDeque.h"
#include "SharedPtr.h"
#include "Page.h"

class Word {
friend void analyzeWord(std::string phrase, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque);
private:
    std::string value;

    // указатель на динамический массив, состоящий из указателей на Line
    SharedPtr<DynamicArray<SharedPtr<Line>>> lineArray;

    // функция добавления добавления новой линии для слова (получается, что слово где-то в этой линии встречается)
    void setLine(SharedPtr<Line> line) {
        lineArray->append(line);
    }

public:
    Word(const std::string& str): value(str), lineArray(makeShared<DynamicArray<SharedPtr<Line>>>()) {}

    Word(const SharedPtr<Word>& another): value(another->value), lineArray(another->lineArray) { } 

    Word() {}

    Word(const Word& word) = delete;

    ~Word() = default;

    const std::string& getValue() const {
        return value;
    } 

    bool operator==(const Word& another) const {
        if (another.value == value) {
            return true;
        }
        return false;
    }

    Word& operator=(const Word& another) {
        value = another.value;
        lineArray = another.lineArray;
        return *this;
    }

    SharedPtr<Line> getLastLine() const {
        //std::cout << "In getLastLine()... size = " << lineArray->getSize() << "\n";
        return (*lineArray)[lineArray->getSize() - 1];
    }

    SharedPtr<DynamicArray<int>> getPageNumbers() const {
        SharedPtr<DynamicArray<int>> numbers = makeShared<DynamicArray<int>>();
        for (int i = 0; i < lineArray->getSize(); ++i) {
            numbers->append(lineArray->get(i)->getPage()->getIndex());
        }
        return numbers;
    }

    SharedPtr<DynamicArray<int>> getLineNumbers() const {
        SharedPtr<DynamicArray<int>> numbers = makeShared<DynamicArray<int>>();
        for (int i = 0; i < lineArray->getSize(); ++i) {
            numbers->append(lineArray->get(i)->getIndex());
        }
        return numbers;
    }

    SharedPtr<DynamicArray<SharedPtr<Line>>> getLineArray() const {
        return lineArray;
    }

    SharedPtr<DynamicArray<Page*>> getPagesAddress() const {
        SharedPtr<DynamicArray<Page*>> pagesArray = makeShared<DynamicArray<Page*>>();
        for (int i = 0; i < lineArray->getSize(); ++i) {
            pagesArray->append(lineArray->get(i)->getPageAddress());
        }
        return pagesArray;
    }

    int getSize() const {
        return value.size();
    }
};