// Copyright 2025 NNTU-CS
#include "tstack.h"
#include <string>
#include <sstream>
#include <cctype>

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string result;
    size_t i = 0;
    while (i < inf.size()) {
        char c = inf[i];
        if (std::isspace(c)) {
            ++i;
            continue;
        }
        if (std::isdigit(c)) {
            std::string num;
            while (i < inf.size() && std::isdigit(inf[i])) {
                num += inf[i];
                ++i;
            }
            result += num + ' ';
            continue;
        }
        if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.isEmpty() && st.get() != '(') {
                result += st.pop();
                result += ' ';
            }
            if (!st.isEmpty() && st.get() == '(') {
                st.pop();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!st.isEmpty() && st.get() != '(' && priority(st.get()) >= priority(c)) {
                result += st.pop();
                result += ' ';
            }
            st.push(c);
        }
        ++i;
    }
    while (!st.isEmpty()) {
        result += st.pop();
        result += ' ';
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int eval(const std::string& post) {
    std::istringstream iss(post);
    std::string token;
    TStack<int, 100> st;
    while (iss >> token) {
        if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
            st.push(std::stoi(token));
        } else {
            int right = st.pop();
            int left = st.pop();
            int res;
            if (token == "+") {
                res = left + right;
            } else if (token == "-") {
                res = left - right;
            } else if (token == "*") {
                res = left * right;
            } else if (token == "/") {
                res = left / right;
            } else {
                res = 0;
            }
            st.push(res);
        }
    }
    return st.pop();
}
