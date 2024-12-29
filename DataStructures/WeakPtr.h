#pragma once
#include "SharedPtr.h"
#include <stdexcept>
#include <type_traits>

template <typename T>
class WeakPtr {
private:
    T* ptr;
    ControlBlock* controlBlock;
public:
    WeakPtr(): ptr(nullptr), controlBlock(new ControlBlock(0, 0)) {}
    WeakPtr(const SharedPtr<T>& other): ptr(other.ptr), controlBlock(other.controlBlock) {
        ++(controlBlock->weakCount);
    }
    WeakPtr(const WeakPtr<T>& other): ptr(other.ptr), controlBlock(other.controlBlock) {
        ++(controlBlock->weakCount);
    }

    template <typename U>
    WeakPtr(const WeakPtr<U>& other) {
        if (std::is_base_of<T, U>::value) {
            ptr = other.ptr;
            controlBlock = other.controlBlock;
        }
        ++(controlBlock->weakCount);
    }

    ~WeakPtr() {
        --(controlBlock->weakCount);
        if (controlBlock->weakCount <= 0 && controlBlock->sharedCount <= 0) {
            // значит, что ptr == nullptr уже
            delete controlBlock;
        }
    }

    template <typename U>
    WeakPtr<T>& operator=(const WeakPtr<U>& other) {
        if (std::is_base_of<T, U>::value) {
            --(controlBlock->weakCount);

            if (controlBlock->weakCount <= 0 && controlBlock->sharedCount <= 0) {
                delete controlBlock;
            }
            ptr = other.ptr;
            controlBlock = other.controlBlock;
            ++(controlBlock->weakCount);
            return *this;
        } else {
            throw std::invalid_argument();
        }
    }

    WeakPtr<T>& operator=(const WeakPtr<T>& other) {
        --(controlBlock->weakCount);
        if (controlBlock->weakCount <= 0 && controlBlock->sharedCount <= 0) {
            delete controlBlock;
        }
        ptr = other.ptr;
        controlBlock = other.controlBlock;
        ++(controlBlock->weakCount);
        return *this;
    }

    // BETA
    WeakPtr<T>& operator=(const SharedPtr<T>& other) {
        --(controlBlock->weakCount);
        if (controlBlock->weakCount <= 0 && controlBlock->sharedCount <= 0) {
            delete controlBlock;
        }
        ptr = other.ptr;
        controlBlock = other.controlBlock;
        ++(controlBlock->weakCount);
        return *this;
    }

    bool expired() const { // checks if an object is nullptr
        if (ptr == nullptr) return true;
        return false; 
    }

    SharedPtr<T> lock() const {
        if (ptr) return SharedPtr(controlBlock, ptr);
        return nullptr;
    }

    T* operator->() {
        return ptr;
    }

    T& operator*() {
        return *ptr;
    }

};

// кажется, эта функция никогда не используется
/*
    template <typename U>
    WeakPtr<T>& operator=(const SharedPtr<U>& other) {
        if (std::is_base_of<T, U>::value) {
            --(controlBlock->weakCount);
            if (controlBlock->weakCount <= 0 && controlBlock->sharedCount <= 0) {
                delete controlBlock;
            }
            ptr = other.ptr;
            controlBlock = other.controlBlock;
            ++(controlBlock->weakCount);
            return *this;
        } else {
            throw std::invalid_argument("");
        }
    }
*/