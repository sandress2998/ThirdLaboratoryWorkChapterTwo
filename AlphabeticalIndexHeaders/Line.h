#pragma once

#include "Page.h"
#include "Word.h"

class Line {
private:
    Page* page = nullptr;
    int capacity = 50;
    int size = 0;

public:
    ~Line() {
        //delete page;
    }

/* не работает
    void deletePage() {
        delete page;
        page = nullptr;
    }
*/

    // используем такой конструктор только для самого первого слова в тексте
    Line() {
        page = new Page(0);
    }

    Line(const Line& prev) {
        page = prev.getPage()->addLine();
    }

    Page* getPage() const {
        return page;
    }

    Line& operator=(const Line& another) {
        capacity = another.capacity;
        size = another.size;
        page = another.page;
        return *this;
    }

    // добавляем новое слово в строку и возвращаем указатель на строку, в которой мы прибавили это слово
    Line* addWord(const std::string& str) {
        if (capacity - size < str.size()) {
            Line* newLine = new Line(*this);
            newLine->addWord(str);
            return newLine;
        } else {
            size += str.size();
            ++size;
            return this;
        }
    }
};