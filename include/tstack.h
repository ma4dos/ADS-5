// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T arr_[size];
  int top_;

 public:
  TStack() : top_(-1) {}

  void push(T value) {
    if (top_ < size - 1) {
      arr_[++top_] = value;
    }
  }

  T pop() {
    if (top_ >= 0) {
      return arr_[top_--];
    }
    return T();
  }

  T get() const {
    if (top_ >= 0) {
      return arr_[top_];
    }
    return T();
  }

  bool isEmpty() const {
    return top_ == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
