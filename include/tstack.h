// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T data[size];
    int top_;

public:
    TStack() : top_(-1) {}

    void push(const T& value) {
        if (!isFull()) {
            data[++top_] = value;
        }
    }

    T pop() {
        if (!isEmpty()) {
            return data[top_--];
        }
        return T();
    }

    T get() const {
        if (!isEmpty()) {
            return data[top_];
        }
        return T();
    }

    bool isEmpty() const {
        return top_ == -1;
    }

    bool isFull() const {
        return top_ == size - 1;
    }

    void clear() {
        top_ = -1;
    }
};

#endif
