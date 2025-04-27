#include <iostream>
using namespace std;

typedef int data_type; // data_type을 int로 정의 (필요에 따라 변경 가능)

class node {
public:
    data_type item;
    node* link;

    node(data_type val) : item(val), link(nullptr) {}

    node* search(data_type target) {
        node* curr = this;
        while (curr != nullptr) {
            if (curr->item == target)
                return curr; // 찾음
            curr = curr->link;
        }
        return NULL; // 못 찾음
    }
};

class hnode {
public:
    node* link;

    hnode() : link(nullptr) {}

    node* search(data_type target) {
        if (link == nullptr) return nullptr;
        return link->search(target);
    }
};
