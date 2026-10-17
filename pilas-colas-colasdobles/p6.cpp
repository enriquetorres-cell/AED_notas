#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct Queue {
    struct QueueNode {
        data_type data;
        QueueNode* next;
        QueueNode() : next(nullptr) {}
        QueueNode(data_type data) : data(data), next(nullptr) {}
    };
    QueueNode* _front;
    QueueNode* _back;

    Queue() : _front(nullptr), _back(nullptr) {}

    void push(data_type value) {
        if (_front == nullptr) {
            _front = new QueueNode(value);
            _back = _front;
        } else {
            _back->next = new QueueNode(value);
            _back = _back->next;
        }
    }

    void pop() {
        if (_front != nullptr) _front = _front->next;
    }

    data_type front() {
        return _front == nullptr ? data_type() : _front->data;
    }

    bool empty() {
        return _front == nullptr;
    }
};