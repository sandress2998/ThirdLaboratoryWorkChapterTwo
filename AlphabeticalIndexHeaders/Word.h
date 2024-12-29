#pragma once

#include <string>
#include "Line.h"
#include "MutableSegmentedDeque.h"


class Word {
friend void analyzeWord(std::string phrase, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<Word*>& wordsDeque);
private:
    std::string value;
    DynamicArray<Line*>* lineArray = new DynamicArray<Line*>();

    // функция добавления добавления новой линии для слова (получается, что слово где-то в этой линии встречается)
    void setLine(Line* line) {
        lineArray->append(line);
    }
public:
    Word(const std::string& str): value(str) {}

    Word(const Word& another): value(another.value), lineArray(another.lineArray) { } 

    Word() {}

// ЛУЧШЕ СДЕЛАТЬ ОТДЕЛЬНУЮ ФУНКЦИЮ deleteLinesAndPages, которая будет вызываться сознательно, а не когда как
    ~Word() {
        for (int i = 0; i < lineArray->getSize(); ++i) {
            //delete lineArray->get(i);
        }
        // Хотя стойте... может быть здесь ошибка? Да, наверняка здесь
        //delete lineArray;
    }

/* не работает
    void deleteLinesAndPages() {
        for (int i = 0; i < lineArray->getSize(); ++i) {
            if (lineArray->get(i) != nullptr) {
                lineArray->get(i)->deletePage();
                delete lineArray->get(i);
                (*lineArray)[i] = nullptr;
            }
        }
    }
*/

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

    Line* getLastLine() const {
        return (*lineArray)[lineArray->getSize() - 1];
    }

    int getSize() const {
        return value.size();
    }
};