#pragma once
#include "WeakPtr.h"

class Page {
private:
    static const int standartCapacity = 5;
    WeakPtr<Page> currentPage;
    int index;
    int capacity;
    int size = 1;
public:
    Page(int index): index(index) {
        if (index == 1) {
            capacity = 0.5 * standartCapacity;
        } else if (index % 10 == 0) {
            capacity = 0.75 * standartCapacity;
        } else {
            capacity = standartCapacity;
        }
    }
    
    // Плохо, знаю, но по-другому никак
    static SharedPtr<Page> createFirstPage() {
        SharedPtr<Page> page = makeShared<Page>(1);
        page->currentPage = page;
        std::cout << "creating a new page... index = " << page->getIndex() << "\n";
        return page;
    }

    int getIndex() const {
        return index;
    }

    int getCapacity() const {
        return capacity;
    }

    SharedPtr<Page> addLine() {
        if (capacity - size > 0) {
            ++size;
            //std::cout << "capacity = " << capacity << " size = " << size << "\n";
            return currentPage.lock();
        }
        // если нужно создать новую страницу...
        SharedPtr<Page> newPage = makeShared<Page>(index + 1);
        newPage->currentPage = newPage;
        //std::cout << "creating a new page... index = " << index + 1 << "\n";
        return newPage;
    }
    
    ~Page() {}
};