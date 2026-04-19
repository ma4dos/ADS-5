// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int priority(char op) {
    switch (op) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default:  return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string output;
    int len = inf.length();

    for (int i = 0; i < len; ++i) {
        char c = inf[i];

        if (std::isdigit(c)) {
            std::string num;
            while (i < len && std::isdigit(inf[i])) {
                num += inf[i];
                ++i;
            }
            --i;
            output += num + " ";
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                output += stack.pop();
                output += " ";
            }
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && priority(stack.top()) >= priority(c)) {
                output += stack.pop();
                output += " ";
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        output += stack.pop();
        output += " ";
    }

    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }

    return output;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (token.size() == 1 && (token[0] == '+' || token[0] == '-' ||
                                  token[0] == '*' || token[0] == '/')) {
            int b = stack.pop();
            int a = stack.pop();
            int res = 0;
            switch (token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            stack.push(res);
        } else {
            stack.push(std::stoi(token));
        }
    }

    return stack.pop();
}
