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
    static const int capacity = 20;
    int size = 0;
    int index;

    // Наверное, ошибка здесь!!!
    SharedPtr<Line> defineNextLine() {
        //std::cout << "Defining a new line... " << "\n";
        SharedPtr<Page> nextPage = page->addLine();
        SharedPtr<Line> nextLine = makeShared<Line>(nextPage); // создаем новую строку через умный указатель
        nextLine->currentLine = nextLine; // в новую строку в поле line записываем умный указатель на новую строку
        nextLine->index = ++index % (page->getCapacity());
        assert(nextLine.getSharedPointersQuantity() == 1 && nextLine.getWeakPointersQuantity() == 1);
        return nextLine;
    }

public:
    ~Line() = default;

    // используем такую функцию только для самого первого слова в тексте
    static SharedPtr<Line> createFirstLine() {
        SharedPtr<Line> firstLine = makeShared<Line>(Page::createFirstPage());
        firstLine->currentLine = firstLine;
        firstLine->index = 0;
        return firstLine;
    }

    //Line(const Line& prev): page(prev.page) {}
    Line(const Line& prev) = delete;
    
    Line(const SharedPtr<Page>& page): page(page) {}

    SharedPtr<Page> getPage() const {
        return page;
    }

    Page* getPageAddress() const {
        return &(*page);
    }

    Line& operator=(const Line& another) {
        size = another.size;
        page = another.page;
        currentLine = another.currentLine;
        return *this;
    }

    // добавляем новое слово в строку и возвращаем указатель на строку, в которой мы прибавили это слово
    SharedPtr<Line> addWord(const std::string& str) {
        //std::cout << "In addWord(...) before if-else... " << "word = " << str << "\n";
        //std::cout << "capacity = " << capacity << "; size = " << size << "; str.size = " << str.size() << "\n";
        if (capacity - size < str.size()) {
            //std::cout << "In addWord(...)...\n";
            SharedPtr<Line> newLine = defineNextLine(); // создаем новую строку, учитывая заполненность текущей страницы
            newLine->addWord(str);
            return newLine;
        } else {
            size += str.size();
            if (size + 1 <= capacity) {
                ++size;
            }
            //std::cout << "In addWord(...) in else block..." << " size = " << size << "\n";
            //std::cout << currentLine.lock()->size << "\n";
            return currentLine.lock(); // просто копируем наш умный указатель на текущую строку
        }
    }

    int getIndex() const {
        return index;
    }
};