#pragma once

#include <string>
#include <iostream>
#include "Line.h"
#include "MutableSegmentedDeque.h"
#include "SharedPtr.h"


class Word {
friend void analyzeWord(std::string phrase, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque);
private:
    std::string value;
    SharedPtr<DynamicArray<SharedPtr<Line>>> lineArray = makeShared<DynamicArray<SharedPtr<Line>>>();

    // функция добавления добавления новой линии для слова (получается, что слово где-то в этой линии встречается)
    void setLine(SharedPtr<Line> line) {
        lineArray->append(line);
    }

public:
    Word(const std::string& str): value(str) {}

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

    SharedPtr<Line>& getLastLine() const {
        return (*lineArray)[lineArray->getSize() - 1];
    }

    int getSize() const {
        return value.size();
    }
};