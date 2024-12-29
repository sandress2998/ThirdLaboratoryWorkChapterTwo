#pragma once
#include <stddef.h>
#include <type_traits>
#include <stdexcept>

struct ControlBlock {
    ControlBlock(size_t sharedCount, size_t weakCount): sharedCount(sharedCount), weakCount(weakCount) {}
    size_t sharedCount;
    size_t weakCount;
};

template <typename T>
class SharedPtr {
     // будем удалять controlBlock только тогда, когда не осталось ни weakCount, ни sharedCount
    template <typename U>
    friend class WeakPtr;

    template <typename U, typename... Args>
    friend SharedPtr<U> makeShared(const Args&... args);

    template <typename U>
    friend class SharedPtr;
private:

    T* ptr;
    ControlBlock* controlBlock;

    SharedPtr(ControlBlock* controlBlock, T* ptr): ptr(ptr), controlBlock(controlBlock) {
        ++(controlBlock->sharedCount);
    }

public:

    SharedPtr(): ptr(nullptr), controlBlock(new ControlBlock(0, 0)) {}

    SharedPtr(T* ptr): ptr(ptr), controlBlock(new ControlBlock(1, 0)) { }

    SharedPtr(const SharedPtr<T>& other): ptr(other.ptr), controlBlock(other.controlBlock) {
        ++(controlBlock->sharedCount);
    }

    template <typename U>
    SharedPtr(const SharedPtr<U>& other) {
        if (std::is_base_of<T, U>::value) {
            ptr = other.ptr;
            controlBlock = other.controlBlock;
        } else {
            throw std::invalid_argument("");
        }
        ++(controlBlock->sharedCount);
    }

    ~SharedPtr() {
        --(controlBlock->sharedCount);
        if (controlBlock->sharedCount <= 0 && controlBlock->weakCount <= 0) {
            if (ptr) {
                delete ptr;
                ptr = nullptr;
            }
            delete controlBlock;
            controlBlock = nullptr; // наверное, это лишнее
        }
    }
    
    template <typename U>
    operator SharedPtr<U>() const {
        if (std::is_base_of<U, T>::value) {
            --(controlBlock->sharedCount); // заранее уменьшаем, затем сразу же увеличиваем на 1, чтобы не увеличивать sharedCount почем зря
            return SharedPtr<U>(*this);
        } else {
            throw std::invalid_argument("");
        }
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        if (ptr == other.ptr) return *this;
        // уменьшаем счетчик текущего ptr на 1
        --(controlBlock->sharedCount);

        if (controlBlock->sharedCount <= 0) {
            delete ptr;
            ptr = nullptr;
        }

        if (controlBlock->sharedCount <= 0 && controlBlock->weakCount <= 0) {
            delete controlBlock;
            controlBlock = nullptr;
        }

        ptr = other.ptr;
        controlBlock = other.controlBlock;
        ++(controlBlock->sharedCount);
        return *this;
    }

    template <typename U>
    SharedPtr<T>& operator=(const SharedPtr<U>& other) {
        if (std::is_base_of<T, U>::value) {
            if (std::is_same<T, U>::value && (T*)(&(other.ptr)) == this->ptr) return *this;
            // уменьшаем счетчик текущего ptr на 1
            --(controlBlock->sharedCount);

            if (controlBlock->sharedCount <= 0) {
                delete ptr;
                ptr = nullptr;
            }

            if (controlBlock->sharedCount <= 0 && controlBlock->weakCount <= 0) {
                delete controlBlock;
            }

            ptr = other.ptr;
            controlBlock = other.controlBlock;
            ++(controlBlock->sharedCount);
            return *this;
        } else {
            throw std::invalid_argument("");
        }
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() {
        return ptr;
    }

    size_t getSharedPointersQuantity() const {
        return controlBlock->sharedCount; 
    }

    size_t getWeakPointersQuantity() const { 
        return controlBlock->weakCount; 
    }
};

template <typename T, typename... Args>
SharedPtr<T> makeShared(const Args&... args) {
    ControlBlock* controlBlock = new ControlBlock(0, 0); 
    return SharedPtr<T>(controlBlock, new T(args...));
}
