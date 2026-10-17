#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct Stack {
    struct StackNode {
        data_type data;
        StackNode* next;
        StackNode(data_type data) : data(data), next(nullptr) {}
    };
    StackNode* _top;

    Stack() : _top(nullptr) {}

    void push(data_type value) {
        StackNode* new_node = new StackNode(value);
        new_node->next = _top;
        _top = new_node;
    }

    void pop() {
        if (_top != nullptr) _top = _top->next;
    }

    data_type top() {
        return _top == nullptr ? data_type() : _top->data;
    }

    bool empty() {
        return _top == nullptr;
    }
};
