#pragma once

#include <string>
#include "Line.h"
#include "MutableSegmentedDeque.h"

// TEST
#include <iostream>

class Word {
friend void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<Word*>& wordsDeque);
private:
    std::string value;
    DynamicArray<Line*>* lineArray = nullptr;

    // функция добавления добавления новой линии для слова (получается, что слово где-то в этой линии встречается)
    void setLine(Line* line) {
        // TEST 8
        std::cout << "test 8\n";
        std::cout << "lineArray size after test 8: " << lineArray->getSize() << "\n";
        lineArray->append(line);
        // TEST 9
        std::cout << "test 9\n";
    }
public:
    Word(const std::string& str): value(str), lineArray(new DynamicArray<Line*>()) {
        std::cout << "lineArray initial size = " << lineArray->getSize() << "\n";
    }

    Word(const Word& another): value(another.value), lineArray(another.lineArray) { } 

    Word(): lineArray(new DynamicArray<Line*>()) {
        // TEST
        std::cout << "default constructor in Word\n";
        std::cout << "lineArray initial size = " << lineArray->getSize() << "\n";
    }

    ~Word() {
        for (int i = 0; i < lineArray->getSize(); ++i) {
            delete lineArray->get(i);
        }
        delete lineArray;
    }

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
        std::cout << "Мб здесь ошибка?\n";
        value = another.value;
        lineArray = another.lineArray;
        return *this;
    }

    Line* getLastLine() const {
        return (*lineArray)[lineArray->getSize() - 1];
    }

    int getSize() const {
        return value.size();
    }
};