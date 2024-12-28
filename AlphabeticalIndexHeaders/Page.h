#pragma once

class Page {
private:
    static const int standartCapacity = 50;
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

    int getIndex() const {
        return index;
    }

    Page* addLine() {
        if (capacity - size > 0) {
            ++size;
            return this;
        }
        return new Page(++index);
    }
};