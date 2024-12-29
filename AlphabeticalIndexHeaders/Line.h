#pragma once

#include "Page.h"
#include "Word.h"
#include "SharedPtr.h"
#include "WeakPtr.h"
#include <iostream>
#include <cassert>

class Line {
private:
    SharedPtr<Page> page;
    WeakPtr<Line> currentLine;
    int capacity = 50;
    int size = 0;

    SharedPtr<Line> defineNextLine(const Line& prev) {
        page = prev.getPage()->addLine();
        SharedPtr<Line> nextLine = makeShared<Line>(page); // создаем новую строку через умный указатель
        nextLine->currentLine = nextLine; // в новую строку в поле line записываем умный указатель на новую строку
        assert(nextLine.getSharedPointersQuantity() == 1 && nextLine.getWeakPointersQuantity() == 1);
        return nextLine;
    }

public:
    ~Line() = default;

    // используем такую функцию только для самого первого слова в тексте
    static SharedPtr<Line> createFirstLine() {
        SharedPtr<Line> firstLine = makeShared<Line>(Page::createFirstPage());
        firstLine->currentLine = firstLine;
        return firstLine;
    }

    //Line(const Line& prev): page(prev.page) {}
    Line(const Line& prev) = delete;
    
    Line(const SharedPtr<Page>& page): page(page) {}

    SharedPtr<Page> getPage() const {
        return page;
    }

    Line& operator=(const Line& another) {
        capacity = another.capacity;
        size = another.size;
        page = another.page;
        currentLine = another.currentLine;
        return *this;
    }

    // добавляем новое слово в строку и возвращаем указатель на строку, в которой мы прибавили это слово
    SharedPtr<Line> addWord(const std::string& str) {
        if (capacity - size < str.size()) {
            SharedPtr<Line> newLine = defineNextLine(*this); // создаем новую строку, учитывая заполненность текущей страницы
            newLine->addWord(str);
            return newLine;
        } else {
            size += str.size();
            ++size;
            return currentLine.lock(); // просто копируем наш умный указатель на текущую строку
        }
    }
};