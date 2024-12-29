#pragma once
#include "WeakPtr.h"

class Page {
private:
    static const int standartCapacity = 50;
    WeakPtr<Page> currentPage;
    int index;
    int capacity;
    int size = 0;
public:
    Page(int index): index(index) {
        if (index == 0) {
            capacity = 0.5 * standartCapacity;
        } else if (index % 10 == 0) {
            capacity = 0.75 * standartCapacity;
        } else {
            capacity = standartCapacity;
        }
    }
    
    // Плохо, знаю, но по-другому никак
    static SharedPtr<Page> createFirstPage() {
        SharedPtr<Page> page = makeShared<Page>(0);
        page->currentPage = page;
        return page;
    }

    int getIndex() const {
        return index;
    }

    SharedPtr<Page> addLine() {
        if (capacity - size > 0) {
            ++size;
            return currentPage.lock();
        }
        // если нужно создать новую страницу...
        SharedPtr<Page> newPage = makeShared<Page>(++index);
        newPage->currentPage = newPage;
        return newPage;
    }
    
    ~Page() {}
};